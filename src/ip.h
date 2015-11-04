#ifndef IP_H
#define IP_H

#include <stdbool.h>
#include <stdint.h>

/* TEMPORARY TEST STRUCTURE. */
struct ip_prefix {
	int prefix;
	int suffix;
	int len;  /* Length of prefix + suffix. */
	char next_hop;
};

//struct ip_prefix *ip_prefix(uint8_t a, uint8_t b, uint8_t c, uint8_t d,
//		int len, char next_hop);

//struct ip_prefix *ip_prefix(int k, int m, uint8_t a, uint8_t b, uint8_t c,
//		uint8_t d, int prefix_len, char next_hop);

/*
struct ipv4_prefix {
	uint32_t next_hop;
	uint32_t prefix;
	uint8_t netmask;
};

struct ipv4_prefix *new_ipv4_prefix(uint8_t a, uint8_t b, uint8_t c, uint8_t d,
		uint8_t netmask, uint32_t next_hop);

extern inline uint32_t new_ipv4_addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	return (uint32_t)a << 24 | b << 16 | c << 8 | d;
}

extern inline bool is_prefix_valid(const struct ipv4_prefix *pfx)
{
	return pfx != NULL && pfx->netmask >= 0 && pfx->netmask <= 32;
}
*/

#endif

