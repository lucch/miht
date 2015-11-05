#ifndef MIHT_H
#define MIHT_H

#include <stdbool.h>

#include "ip.h"

struct ptrie_node {
	bool is_priority;
	int suffix;
	int len;  /* Suffix length. */
	int next_hop;
	struct ptrie_node *left;
	struct ptrie_node *right;
};

struct bplus_node {
	bool is_leaf;
	int num_indices;  /* t(u) */
	int *indices;  /* 1 <= i <= m - 1 */
	union {
		struct bplus_node **children;  /* 0 <= i <= m - 1 */
		struct ptrie_node **data;  /* 1 <= i <= m - 1 */
	};
};

struct miht {
	int k;
	int m;
	struct ptrie_node *root0;
	struct bplus_node *root1;
};

/*
 * \brief Recommended value for both \c k and \c m is 16 for IPv4.
 * \param k Length of prefix keys.
 * \param m Order of B+ tree.
 */
struct miht *miht_create(int k, int m);

void miht_insert(struct miht *miht, struct ptrie_node *ptminusone,
		struct bplus_node *bplus, struct ip_prefix prefix);

char miht_lookup(const struct miht *miht, const struct ptrie_node *ptminusone,
		const struct bplus_node *bplus, int addr);

void miht_print(const struct miht *miht);

#endif

