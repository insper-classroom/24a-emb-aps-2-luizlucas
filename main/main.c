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
#include "hardware/adc.h"


QueueHandle_t xQueueBTN;
QueueHandle_t xQueueADC;


typedef struct {
    int status;
    char val[2];
} btn_t;


void btn_callback(uint gpio, uint32_t events) {
    btn_t str;
    if (events == 0x4) str.status=1;
    else if (events == 0x8) str.status=0; 

    if (gpio==BTN_TEST) {
        str.val[0]='b';
        str.val[1]='t';
    }

    if (gpio==BTN_R_1) {
        str.val[0]='r';
        str.val[1]='1';
    }
    if (gpio==BTN_R_2) {
        str.val[0]='r';
        str.val[1]='2';
    }
    if (gpio==BTN_G_1) {
        str.val[0]='g';
        str.val[1]='1';
    }
    if (gpio==BTN_G_2) {
        str.val[0]='g';
        str.val[1]='2';
    }
    if (gpio==BTN_B_1) {
        str.val[0]='b';
        str.val[1]='1';
    }
    if (gpio==BTN_B_2) {
        str.val[0]='b';
        str.val[1]='2';
    }

    if (gpio==JS_1) {
        str.val[0]='j';
        str.val[1]='r';
    }
    if (gpio==JS_2) {
        str.val[0]='j';
        str.val[1]='l';
    }
    if (gpio==JS_3) {
        str.val[0]='j';
        str.val[1]='u';
    }
    if (gpio==JS_4) {
        str.val[0]='j';
        str.val[1]='d';
    }
    
    xQueueSendFromISR(xQueueBTN, &str, 0);
}   

void adc_task(void *p) {
    adc_init();
    adc_gpio_init(ADC_GP);

    uint16_t adc_value;
    printf("oi \n");
    uint16_t vol=0;
    while (true) {
        adc_select_input(0);
        uint16_t result = adc_read();
        vol=result/40;
        printf("VOLUME: %d\n",result);
        
    }
}

void write_package(btn_t data) {
    uart_putc_raw(HC06_UART_ID, data.status);
    uart_putc_raw(HC06_UART_ID, data.val[0]);
    uart_putc_raw(HC06_UART_ID, data.val[1]);
    uart_putc_raw(HC06_UART_ID, -1);
}

void btn_task(void *p){
    btn_init();
    printf("BTN_INIT");

    uart_init(HC06_UART_ID, HC06_BAUD_RATE);
    gpio_set_function(HC06_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(HC06_RX_PIN, GPIO_FUNC_UART);
    hc06_init("LUCAS_FEDE", "1234");

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
    xQueueADC = xQueueCreate(32, sizeof(uint16_t));

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


    //xTaskCreate(btn_task, "btn", 4095, NULL, 1, NULL);
    xTaskCreate(adc_task, "adc", 4095, NULL, 1, NULL);


    vTaskStartScheduler();



    while (true)
        ;
}
