#include "minunit.h"

#include "ip.h"
#include "miht.h"

int prefixes_len = 15;

struct ip_prefix prefixes[] = {
	{  /* P1 */
		.prefix   = 1,
		.suffix   = 0,
		.len      = 5,
		.next_hop = 'A'
	},
	{  /* P2 */
		.prefix   = 1,
		.suffix   = 1,
		.len      = 5,
		.next_hop = 'B'
	},
	{  /* P3 */
		.prefix   = 3,
		.suffix   = 1,
		.len      = 5,
		.next_hop = 'C'
	},
	{  /* P4 */
		.prefix   = 3,
		.suffix   = 6,
		.len      = 7,
		.next_hop = 'D'
	},
	{  /* P5 */
		.prefix   = 5,
		.suffix   = 2,
		.len      = 6,
		.next_hop = 'E'
	},
	{  /* P6 */
		.prefix   = 7,
		.suffix   = 0,
		.len      = 6,
		.next_hop = 'F'
	},
	{  /* P7 */
		.prefix   = 1,
		.suffix   = 0,  /* Unused. */
		.len      = 2,
		.next_hop = 'G'
	},
	{  /* P8 */
		.prefix   = 9,
		.suffix   = 1,
		.len      = 6,
		.next_hop = 'H'
	},
	{  /* P9 */
		.prefix   = 8,
		.suffix   = 7,
		.len      = 7,
		.next_hop = 'I'
	},
	{  /* P10 */
		.prefix   = 9,
		.suffix   = 0,
		.len      = 5,
		.next_hop = 'J'
	},
	{  /* P11 */
		.prefix   = 2,
		.suffix   = 0,  /* Unused. */
		.len      = 3,
		.next_hop = 'K'
	},
	{  /* P12 */
		.prefix   = 6,
		.suffix   = 4,
		.len      = 7,
		.next_hop = 'L'
	},
	{  /* P13 */
		.prefix   = 8,
		.suffix   = 0,
		.len      = 6,
		.next_hop = 'M'
	},
	{  /* P14 */
		.prefix   = 2,
		.suffix   = 3,
		.len      = 6,
		.next_hop = 'N'
	},
	{  /* P15 */
		.prefix   = 8,
		.suffix   = 1,
		.len      = 5,
		.next_hop = 'O'
	},
};

MU_TEST(insert)
{
	struct miht *miht = miht_create(4, 4); 

	for (int i = 0; i < prefixes_len; i++) {
		miht_insert(miht, miht->root0, miht->root1, prefixes[i]);
	}
}

MU_TEST_SUITE(test_suite) {
	/* Correctness tests. */
	printf("Running correctness-check tests...\n");
	MU_RUN_TEST(insert);

	/* Performance tests. */
	/* TODO: Create a macro `RUN_BENCH(...)`. */
	/*
	printf("\n\nRunning benchmarks...\n");
	MU_RUN_TEST(bench_1);
	*/
}

void test_setup()
{

}

void test_teardown()
{

}

int main(int argc, char *argv[]) {
#ifdef __MIC__
	printf("__MIC__ is defined!\n");
#endif
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_SUITE(test_suite);
	MU_REPORT();

	return 0;
}


