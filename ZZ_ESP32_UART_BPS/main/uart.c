/*
 * uart.c
 *
 *  Created on: Jan 7, 2025
 *      Author: shamir.s
 */


#include "main.h"
#include "uart.h"
static const char *TAG = "MCU UART";

void uart_init() {
    // Configure UART parameters
    uart_config_t uart_config = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_0, &uart_config);
    uart_set_pin(UART_NUM_0, TXD0_PIN, RXD0_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}




void uart_main() {
    uart_init();

    static const char *RX_TASK_TAG = "RX_TASK";
	esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
	uint8_t* data = (uint8_t*)malloc(BUF_SIZE+1);
    //int bytes_read;
    unsigned long last_time = xTaskGetTickCount();
    unsigned long bytes_received = 0;

    while (1)
    {
        // Read data from PC

    	int rxBytes = uart_read_bytes(UART_NUM_0, data, BUF_SIZE, 1000 / portTICK_RATE_MS);
        if (rxBytes > 0)
        {
            data[rxBytes] = '\0';
//          ESP_LOGI(TAG, "Read %d bytes: '%s'", rxBytes, data);
//			ESP_LOG_BUFFER_HEXDUMP("receive data", data, rxBytes, ESP_LOG_INFO);
            bytes_received += rxBytes;


            uart_write_bytes(UART_NUM, (const char*)data, rxBytes);


        }

        // Calculate and print transmission speed every second
        if ((xTaskGetTickCount() - last_time) * portTICK_PERIOD_MS >= 1000)
        {
            unsigned long bits_per_second = ((bytes_received*8)/portTICK_PERIOD_MS); // Calculate bits
            ESP_LOGI(TAG, "Transmission Speed: %lu bps", bits_per_second);

            last_time = xTaskGetTickCount();
            bytes_received = 0; // Reset for next measurement
        }
        sleep(1);
    }
}


