
#include "main.h"
#include "uart.h"

TaskHandle_t xuart_task_Handle;

void app_main(void)
{
	printf("*****Application code Ver0.1 R0*******");
	sleep(1);
	xTaskCreatePinnedToCore(uart_main, "UART_TASK", configMINIMAL_STACK_SIZE*4, NULL, 1024, &xuart_task_Handle,1);

}






