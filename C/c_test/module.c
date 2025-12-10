#include "module.h"
#include "unistd.h"

void LED_Toggle(uint8_t * led_pin)
{
	if (*led_pin == 0)
	{
		*led_pin = 1;
	}
	else
	{
		*led_pin = 0;
	}
}

int max_in_array(int arr[], int len)
{
	int max = arr[0];

	for(int i = 0; i < len; i++)
	{
		if(arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}

bool is_even(int num)
{
	if(num % 2 == 0)
	{
		return true;
	}
	return false;
}


void UART_SendString(const char * str, size_t len, uint8_t * mock_uart_tx)
{

	for(int i = 0; i < len; i++)
	{
		mock_uart_tx[i] = (uint8_t)str[i];
	}
}

void delay_ms(uint32_t ms)
{
	usleep(ms * 1000);
}

int find_index(int arr[], int len, int value)
{
	for(int i = 0; i < len; i++)
	{
		if (arr[i] == value)
		{
			return i;
		}
	}
	return -1;
}
