/*
 * LED blink with FreeRTOS
 */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include <string.h>

#include "pico/stdlib.h"
#include <stdio.h>

#include "hc06.h"
#include "funcoes.h"

QueueHandle_t xQueueBTN;

typedef struct {
    int status;
    int val;
} btn_t;


void btn_callback(uint gpio, uint32_t events) {
    btn_t str;
    if (events == 0x4) str.status=0;
    else if (events == 0x8) str.status=1; 
    str.val=gpio;
    xQueueSendFromISR(xQueueBTN, &str, 0);
}   


void hc06_task(void *p) {
    uart_init(HC06_UART_ID, HC06_BAUD_RATE);
    gpio_set_function(HC06_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(HC06_RX_PIN, GPIO_FUNC_UART);
    hc06_init("LUCAS_FEDE", "1234");

    while (true) {
        uart_puts(HC06_UART_ID, "OLAAA ");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void write_package(btn_t data) {
    uart_putc_raw(uart0, data.status);
    uart_putc_raw(uart0, data.val);
    uart_putc_raw(uart0, -1);
}

void btn_task(void *p){
    btn_init();
    printf("BTN_INIT");

    btn_t data;
    while (1){
        if (xQueueReceive(xQueueBTN, &data,pdMS_TO_TICKS(100))) {
            //printf("data: %d %d\n",data.status, data.val);
            write_package(data); 
            vTaskDelay(pdMS_TO_TICKS(1));
        }
    }
}

int main() {
    stdio_init_all();

    printf("Start bluetooth task\n");
    xQueueBTN = xQueueCreate(32, sizeof(btn_t));

    gpio_set_irq_enabled_with_callback(BTN_R_1, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &btn_callback);
    gpio_set_irq_enabled(BTN_R_2, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(BTN_G_1, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(BTN_G_2, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(BTN_B_1, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(BTN_B_2, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(JS_1, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(JS_2, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(JS_3, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(JS_4, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(BTN_TEST, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);


    xTaskCreate(hc06_task, "UART_Task 1", 4096, NULL, 1, NULL);
    xTaskCreate(btn_task, "btn", 4095, NULL, 1, NULL);


    vTaskStartScheduler();



    while (true)
        ;
}
