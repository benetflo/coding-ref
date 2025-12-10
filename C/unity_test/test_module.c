#include "module.h"
#include "Unity/src/unity.h"



void setUp(void) {}
void tearDown(void) {}

void test_add(void)
{
	TEST_ASSERT_EQUAL_INT(5, add(2, 2));
}


int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_add);
	return UNITY_END();
}
