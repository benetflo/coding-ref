#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <string.h>

// Pin definitions
#define BTN_PIN 16
#define UART0_TX_PIN 0
#define UART0_RX_PIN 1
#define UART1_TX_PIN 4
#define UART1_RX_PIN 5

// Configuration
#define UART_BAUD_RATE 115200
#define DEBOUNCE_MS 50
#define UART_RX_TIMEOUT_MS 10
#define UART_RX_BUFFER_SIZE 128

// Button state
volatile bool g_send_requested = false;
volatile uint64_t g_last_press_time = 0;

// UART receive buffer
static char g_rx_buffer[UART_RX_BUFFER_SIZE];

/**
 * @brief GPIO interrupt callback for button press
 * @param gpio GPIO pin number that triggered the interrupt
 * @param events Event mask (edge rise/fall)
 */
void gpio_callback(uint gpio, uint32_t events)
{
    uint64_t now = to_us_since_boot(get_absolute_time()) / 1000;

    if (now - g_last_press_time > DEBOUNCE_MS)
    {
        g_send_requested = true;
        g_last_press_time = now;
    }
}

/**
 * @brief Initialize UART0 (transmit)
 */
static void uart0_init_config(void)
{
    gpio_set_function(UART0_TX_PIN, UART_FUNCSEL_NUM(uart0, UART0_TX_PIN));
    gpio_set_function(UART0_RX_PIN, UART_FUNCSEL_NUM(uart0, UART0_RX_PIN));
    uart_init(uart0, UART_BAUD_RATE);
    uart_set_format(uart0, 8, 1, UART_PARITY_NONE);
}

/**
 * @brief Initialize UART1 (receive)
 */
static void uart1_init_config(void)
{
    gpio_set_function(UART1_TX_PIN, UART_FUNCSEL_NUM(uart1, UART1_TX_PIN));
    gpio_set_function(UART1_RX_PIN, UART_FUNCSEL_NUM(uart1, UART1_RX_PIN));
    uart_init(uart1, UART_BAUD_RATE);
    uart_set_format(uart1, 8, 1, UART_PARITY_NONE);

    // Enable FIFO for better buffering
    uart_set_fifo_enabled(uart1, true);
}

/**
 * @brief Initialize button GPIO with interrupt
 */
static void button_init_config(void)
{
    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);
    gpio_set_irq_enabled_with_callback(BTN_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
}

/**
 * @brief Send message via UART0
 * @param message Null-terminated string to send
 */
static void uart0_send_message(const char* message)
{
    if (uart_is_writable(uart0))
    {
        uart_puts(uart0, message);
    }
}

/**
\\wsl.localhost\Ubuntu\home\benji\PicoEnv-share\sensor.uf2 * @brief Receive complete message from UART1 with timeout
 * @param buffer Buffer to store received message
 * @param buffer_size Size of the buffer
 * @return Number of bytes received, or 0 if no data
 */
static size_t uart1_receive_message(char* buffer, size_t buffer_size)
{
    if (!uart_is_readable(uart1))
    {
        return 0;
    }

    size_t bytes_read = 0;
    uint64_t start_time = to_us_since_boot(get_absolute_time()) / 1000;

    // Read bytes with timeout
    while (bytes_read < buffer_size - 1)
    {
        if (uart_is_readable(uart1))
        {
            buffer[bytes_read++] = uart_getc(uart1);
            start_time = to_us_since_boot(get_absolute_time()) / 1000; // Reset timeout
        }
        else
        {
            uint64_t now = to_us_since_boot(get_absolute_time()) / 1000;
            if (now - start_time > UART_RX_TIMEOUT_MS)
            {
                break; // Timeout - no more data coming
            }
            sleep_us(100); // Small delay to avoid busy-waiting
        }
    }

    buffer[bytes_read] = '\0'; // Null-terminate
    return bytes_read;
}

/**
 * @brief Main program loop
 */
int main(void)
{
    // Initialize standard I/O (USB serial)
    stdio_init_all();

    // Initialize peripherals
    uart0_init_config();
    uart1_init_config();
    button_init_config();

    printf("=== Pico UART Communication System ===\n");
    printf("UART0 TX: GP%d, RX: GP%d\n", UART0_TX_PIN, UART0_RX_PIN);
    printf("UART1 TX: GP%d, RX: GP%d\n", UART1_TX_PIN, UART1_RX_PIN);
    printf("Button: GP%d\n", BTN_PIN);
    printf("Baud rate: %d\n", UART_BAUD_RATE);
    printf("System ready.\n\n");

    // Main loop
    while (true)
    {
        // Handle button press - send message
        if (g_send_requested)
        {
            uart0_send_message("Hello World!\n");
            printf("[TX] Message sent: Hello World!\n");
            g_send_requested = false;
        }

        // Handle UART1 reception
        size_t bytes_received = uart1_receive_message(g_rx_buffer, UART_RX_BUFFER_SIZE);
        if (bytes_received > 0)
        {
            printf("[RX] UART1: %s", g_rx_buffer);

            // Add newline if message doesn't end with one
            if (g_rx_buffer[bytes_received - 1] != '\n')
            {
                printf("\n");
            }
        }

        // Small delay to prevent CPU spinning
        sleep_ms(1);
    }
    return 0;
}
