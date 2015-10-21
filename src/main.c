#include <stdio.h>

#include "miht.h"

int main()
{
	struct miht *miht = miht_create(4, 4); 

	struct ip_prefix p = (struct ip_prefix){
		.prefix   = 1,
		.suffix   = 0,
		.len      = 5,
		.next_hop = 'A'
	};

	miht_insert(miht, miht->root0, miht->root1, p);

	return 0;
}

