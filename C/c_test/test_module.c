#include "module.h"
#include "Unity/src/unity.h"
#include <stdlib.h>
#include <string.h>


void setUp(void) {}
void tearDown(void) {}

void test_LED_Toggle(void)
{
	uint8_t led = 0;
	LED_Toggle(&led);

	// test if led toggles
	TEST_ASSERT_TRUE(led != 0);
}

void test_max_in_array(void)
{
	int nums[5] = {1,5,6,10,7};

	// Expect 10 to be largest
	TEST_ASSERT_EQUAL_INT(10, max_in_array(nums, 5));
}

void test_is_even(void)
{
	TEST_ASSERT_TRUE(is_even(2));
}

void test_UART_SendString(void)
{
	const char *test_str = "HELLO";
	size_t len = strlen(test_str);

	uint8_t mock_uart_tx[5] = {0};

	UART_SendString(test_str, len, mock_uart_tx);

	for(size_t i = 0; i < len; i++)
	{
		TEST_ASSERT_EQUAL(test_str[i], mock_uart_tx[i]);
	}
}

void test_delay_ms(void)
{
	;
}

void test_find_index(void)
{
	int nums[7] = {1,2,3,4,5,6,7};

	TEST_ASSERT_NOT_EQUAL(-1, find_index(nums, 7, 2));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_LED_Toggle);
	RUN_TEST(test_max_in_array);
	RUN_TEST(test_is_even);
	RUN_TEST(test_find_index);
	RUN_TEST(test_UART_SendString);
	return UNITY_END();
}
