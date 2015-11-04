#include <stdlib.h>

#include "ip.h"

//struct ip_prefix {
//	int prefix;
//	int suffix;
//	int len;
//	char next_hop;
//};


//struct ip_prefix *ip_prefix(int k, int m, uint8_t a, uint8_t b, uint8_t c,
//		uint8_t d, int prefix_len, char next_hop)
//{
//	struct ip_prefix *pfx = malloc(sizeof(struct ip_prefix));
//	assert(pfx != NULL);
//
//	pfx->prefix = (a << 24 | b << 16 | c << 8 | d) &
//		(0xffffffff << (32 - prefix_len));
//	pfx->len = prefix_len;
//	pfx->next_hop = next_hop;
//
//	if (!is_prefix_valid(pfx)) {
//		free(pfx);
//		pfx = NULL;
//	}
//
//	return pfx;
//
//}


/*
struct ipv4_prefix *new_ipv4_prefix(uint8_t a, uint8_t b, uint8_t c, uint8_t d,
		uint8_t netmask, char next_hop)
{
	struct ipv4_prefix *pfx = malloc(sizeof(struct ipv4_prefix));
	assert(pfx != NULL);

	pfx->prefix = (a << 24 | b << 16 | c << 8 | d) &
		(0xffffffff << (32 - netmask));
	pfx->netmask = netmask;
	pfx->next_hop = next_hop;

	if (!is_prefix_valid(pfx)) {
		free(pfx);
		pfx = NULL;
	}

	return pfx;
}
*/

