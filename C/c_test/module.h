#ifndef MODULE_H
#define MODULE_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void LED_Toggle(uint8_t * led_pin);
int max_in_array(int arr[], int len);
bool is_even(int num);

void UART_SendString(const char* str, size_t len, uint8_t * mock_uart_tx);
void delay_ms(uint32_t ms);
int find_index(int arr[], int len, int value);

#endif
