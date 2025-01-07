/*
 * main.h
 *
 *  Created on: Jan 7, 2025
 *      Author: shamir.s
 */
#ifndef UART_UART_H_
#define UART_UART_H_

#define UART_NUM UART_NUM_0
#define BUF_SIZE (2048)
#define BAUD_RATE 2400

#define TXD0_PIN GPIO_NUM_43
#define RXD0_PIN GPIO_NUM_44

void uart_init();
void uart_main();
#endif
