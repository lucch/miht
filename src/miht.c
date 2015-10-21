/*
 * This module defines a B+ tree.
 */

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "miht.h"

enum miht_node_type {
	MIHT_INTERNAL, MIHT_EXTERNAL
};

struct ptrie_node *ptrie_node()
{
	struct ptrie_node *ptrie_node = malloc(sizeof(struct ptrie_node));
	assert(ptrie_node != NULL);
	ptrie_node->is_priority = true;
	ptrie_node->suffix = 0;
	ptrie_node->next_hop = 0;
	ptrie_node->left = NULL;
	ptrie_node->right = NULL;

	return ptrie_node;
}

struct bplus_node *bplus_node(int m, enum miht_node_type type)
{
	struct bplus_node *bplus_node = malloc(sizeof(struct bplus_node));
	assert(bplus_node != NULL);
	bplus_node->num_indices = 0;
	/* Allocate extra node to ease implementation: `indices[0]` won't be
	 * used.
	 */
	bplus_node->indices = malloc(m * sizeof(int));
	memset(bplus_node->indices, INT_MAX, m * sizeof(int));
	assert(bplus_node->indices != NULL);
	if (type == MIHT_INTERNAL) {
		bplus_node->is_leaf = false;
		bplus_node->children = calloc(m, sizeof(struct bplus_node *));
		assert(bplus_node->children != NULL);
	} else {  /* type == MIHT_EXTERNAL */
		bplus_node->is_leaf = true;
		/* Allocate extra node to ease implementation: `data[0]` won't be
		 * used.
		 */
		bplus_node->data = calloc(m, sizeof(struct ptrie_node *));
		assert(bplus_node->data != NULL);
	}

	return bplus_node;
}

struct miht *miht_create(int k, int m)
{
	struct miht *miht = malloc(sizeof(struct miht));
	assert(miht != NULL);
	miht->k = k;
	miht->m = m;
	miht->root0 = ptrie_node();
	miht->root1 = bplus_node(m, MIHT_EXTERNAL);

	return miht;
}

int prefix_key(int k, struct ip_prefix prefix)
{
	// TODO: Extract first k bits of prefix.
	return prefix.prefix;
}

int suffix(int k, struct ip_prefix prefix)
{
	// TODO: Extract last len(prefix) - k bits of prefix.
	return prefix.suffix;
}

void miht_node_split(int m, struct bplus_node *x, int y_pos, struct bplus_node *y,
		int pkey)
{
	struct bplus_node *z = y->is_leaf ? bplus_node(m, MIHT_EXTERNAL) :
		bplus_node(m, MIHT_INTERNAL);

	int count = x->num_indices - y_pos;
	if (count > 0) {  /* x is always an internal node. */
		memmove(&x->indices[y_pos + 1],
			&x->indices[y_pos + 2],
			count * sizeof(int));
		memmove(&x->children[y_pos + 1],
			&x->children[y_pos + 2],
			count * sizeof(struct ptrie_node *));
	}
	x->children[y_pos + 1] = z;
	x->num_indices += 1;
	int g = ceil(m / 2.0);
	if (y->is_leaf) {
		if (pkey >= y->indices[g]) {
			memmove(&y->indices[g + 1],
				&z->indices[1],
				(m - g - 1) * sizeof(int));
			memmove(&y->data[g + 1],
				&z->data[1],
				(m - g - 1) * sizeof(struct ptrie_node *));
			z->indices[m - g] = pkey;
		} else {
			memmove(&y->indices[g],
				&z->indices[1],
				(m - g) * sizeof(int));
			memmove(&y->data[g],
				&z->data[1],
				(m - g) * sizeof(struct ptrie_node *));
			y->indices[g] = pkey;
		}
		y->num_indices = g;
		z->num_indices = m - g;
		x->indices[y_pos + 1] = z->indices[1];
	} else {
		z->children[0] = y->children[g];
		memmove(&y->indices[g + 1],
			&z->indices[1],
			(m - g - 1) * sizeof(int));
		memmove(&y->children[g + 1],
			&z->children[1],
			(m - g - 1) * sizeof(struct ptrie_node *));
		y->num_indices = g - 1;
		z->num_indices = m - g - 1;
		x->indices[y_pos + 1] = y->indices[g];
	}
}

const char *byte_to_binary(int x)
{
	static char b[9];
	b[0] = '\0';

	int z;
	for (z = 128; z > 0; z >>= 1)
	{
		strcat(b, ((x & z) == z) ? "1" : "0");
	}

	return b;
}

void ptrie_insert(struct ptrie_node **ptrie, int value, char next_hop)
{
	if (*ptrie == NULL) {
		*ptrie = ptrie_node();
	}

	/* TODO: Implement logic to insert into PT. */

	printf("(%s*, %c)\n", byte_to_binary(value), next_hop);
}

void miht_insert(struct miht *miht, struct ptrie_node *ptminusone,
		struct bplus_node *bplus, struct ip_prefix prefix)
{
	int k = miht->k;
	int m = miht->m;

	if (prefix.len >= k) {
		if (miht->root1->num_indices == m - 1) {
			struct bplus_node *new_root = bplus_node(m, MIHT_INTERNAL);
			new_root->children[0] = miht->root1;
			miht->root1 =new_root;
			miht_node_split(miht->m, miht->root1, 0,
				miht->root1->children[0], prefix_key(k, prefix));
		}

		int p = prefix_key(k, prefix);
		/* Find the index i in B+ tree node. */
		int i = 0;
		for (; i < bplus->num_indices && p >= bplus->indices[i + 1]; i++);

		if (bplus->is_leaf) {  /* External node. */
			if (i == 0 || p != bplus->indices[i]) {
				int count = bplus->num_indices - i;
				i = i + 1;
				if (count > 0) {
					memmove(&bplus->indices[i],
						&bplus->indices[i + 1],
						count * sizeof(int));
					memmove(&bplus->data[i],
						&bplus->data[i + 1],
						count * sizeof(struct ptrie_node *));
				}
				bplus->indices[i] = p;
				bplus->data[i] = NULL;
				bplus->num_indices = bplus->num_indices + 1;
			}
			ptrie_insert(&bplus->data[i], suffix(k, prefix),
					prefix.next_hop);
		} else {  /* Internal node. */
			struct bplus_node *child = bplus->children[i];
			if (child->num_indices == m - 1) {
				bool prefix_exists = false;
				for (int j = 1; j <= child->num_indices; j++) {
					if (child->indices[j] == p) {
						prefix_exists = true;
						break;
					}
				}
				if ((child->is_leaf && !prefix_exists) ||
						!child->is_leaf) {
					miht_node_split(miht->m, bplus, i, child, p);
					if (p >= bplus->indices[i + 1])
						i = i + 1;
				}
			}
			miht_insert(miht, ptminusone, bplus->children[i], prefix);
		}
	} else {
		/* Insert into PT[-1]. */
		ptrie_insert(&ptminusone, prefix.prefix, prefix.next_hop);
	}
}

