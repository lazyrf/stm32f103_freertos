#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "bsp_rcc.h"
#include "bsp_led.h"
#include "bsp_dbg_uart.h"
#include "delay.h"
#include "FreeRTOS.h"
#include "task.h"

void task1(void *arg)
{
	while (1) {
		printf("Hello world\r\n");
		vTaskDelay(1000);
	}
}

void task2(void *arg)
{
	while (1) {
		LED_TOGGLE(CONFIG_LED_1_GPIO_PORT, CONFIG_LED_1_GPIO_PIN);
		vTaskDelay(500);
	}
}

void init_task(void *arg)
{
	printf("Create task1...\r\n");
	xTaskCreate(task1, "Task1", 64, NULL, 2, NULL);

	printf("Create task2...\r\n");
	xTaskCreate(task2, "Task2", 64, NULL, 2, NULL);

	vTaskDelete(NULL);
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	bsp_rcc_init();
	bsp_led_init();
	bsp_dbg_uart_init();

	xTaskCreate(init_task, "Init Task", 64, NULL, 3, NULL);
	vTaskStartScheduler();
}
