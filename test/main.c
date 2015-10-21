#include <minunit.h>

MU_TEST(test_1)
{
	mu_check(1 == 1);
}

MU_TEST_SUITE(test_suite) {
	/* Correctness tests. */
	printf("Running correctness-check tests...\n");
	MU_RUN_TEST(test_1);

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


