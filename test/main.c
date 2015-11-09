#include "minunit.h"

#include "ip.h"
#include "miht.h"

int prefixes_len = 15;

struct ip_prefix prefixes[] = {
	{  /* P1 */
		.prefix   = 0b00010,
		.len      = 5,
		.next_hop = 'A'
	},
	{  /* P2 */
		.prefix   = 0b00011,
		.len      = 5,
		.next_hop = 'B'
	},
	{  /* P3 */
		.prefix   = 0b00111,
		.len      = 5,
		.next_hop = 'C'
	},
	{  /* P4 */
		.prefix   = 0b0011110,
		.len      = 7,
		.next_hop = 'D'
	},
	{  /* P5 */
		.prefix   = 0b010110,
		.len      = 6,
		.next_hop = 'E'
	},
	{  /* P6 */
		.prefix   = 0b011100,
		.len      = 6,
		.next_hop = 'F'
	},
	{  /* P7 */
		.prefix   = 0b01,
		.len      = 2,
		.next_hop = 'G'
	},
	{  /* P8 */
		.prefix   = 0b100101,
		.len      = 6,
		.next_hop = 'H'
	},
	{  /* P9 */
		.prefix   = 0b1000111,
		.len      = 7,
		.next_hop = 'I'
	},
	{  /* P10 */
		.prefix   = 0b10010,
		.len      = 5,
		.next_hop = 'J'
	},
	{  /* P11 */
		.prefix   = 0b010,
		.len      = 3,
		.next_hop = 'K'
	},
	{  /* P12 */
		.prefix   = 0b0110100,
		.len      = 7,
		.next_hop = 'L'
	},
	{  /* P13 */
		.prefix   = 0b100000,
		.len      = 6,
		.next_hop = 'M'
	},
	{  /* P14 */
		.prefix   = 0b001011,
		.len      = 6,
		.next_hop = 'N'
	},
	{  /* P15 */
		.prefix   = 0b10001,
		.len      = 5,
		.next_hop = 'O'
	},
};

MU_TEST(insert)
{
	struct miht *miht = miht_create(4, 4); 

	for (int i = 0; i < prefixes_len; i++) {
		miht_insert(miht, miht->root1, prefixes[i]);
	}

//	miht_print(miht);

	int next_hop;
	miht_lookup(miht, 0b10001000, 8, &next_hop);
//	printf("next_hop = %c\n", next_hop);
	mu_check(next_hop == 'O');
	miht_lookup(miht, 0b10001111, 8, &next_hop);
//	printf("next_hop = %c\n", next_hop);
	mu_check(next_hop == 'I');
	miht_lookup(miht, 0b10001101, 8, &next_hop);
//	printf("next_hop = %c\n", next_hop);
	mu_check(next_hop == 'O');
	miht_lookup(miht, 0b01111111, 8, &next_hop);
//	printf("next_hop = %c\n", next_hop);
	mu_check(next_hop == 'G');
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


