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

typedef struct {
    char ID[2];
    int val;
} btn_t;


void btn_callback(uint gpio, uint32_t events) {
    btn_t btn;
    if (events == 0x4)  btn.val=1;
    else if (events == 0x8) btn.val=0; 

    if (gpio==BTN_TEST) {
        btn.ID[0]='b';
        btn.ID[1]='t';
    }

    if (gpio==BTN_R_1) {
        btn.ID[0]='r';
        btn.ID[1]='1';
    }
    if (gpio==BTN_R_2) {
        btn.ID[0]='r';
        btn.ID[1]='2';
    }
    if (gpio==BTN_G_1) {
        btn.ID[0]='g';
        btn.ID[1]='1';
    }
    if (gpio==BTN_G_2) {
        btn.ID[0]='g';
        btn.ID[1]='2';
    }
    if (gpio==BTN_B_1) {
        btn.ID[0]='b';
        btn.ID[1]='1';
    }
    if (gpio==BTN_B_2) {
        btn.ID[0]='b';
        btn.ID[1]='2';
    }

    if (gpio==JS_1) {
        btn.ID[0]='j';
        btn.ID[1]='r';
    }
    if (gpio==JS_2) {
        btn.ID[0]='j';
        btn.ID[1]='l';
    }
    if (gpio==JS_3) {
        btn.ID[0]='j';
        btn.ID[1]='u';
    }
    if (gpio==JS_4) {
        btn.ID[0]='j';
        btn.ID[1]='d';
    }
    
    xQueueSendFromISR(xQueueBTN, &btn, 0);
}   

void pot1_task(void *p) {
    btn_t pot;
    pot.ID[0] = 'P';
    pot.ID[1] = '1';

    adc_init();
    adc_gpio_init(POT_1);
    //printf("ADC INICIADO \n");
    int result, mean;
    int last_mean = 0;
    int values[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    while (true) {
        adc_select_input(0);
        result = adc_read();
        result = result/35;
        values[(i++)%10] = result;
        mean = (values[0] + values[1] + values[2] + values[3] + values[4] + values[5] + values[6] + values[7] + values[8] + values[9])/10;
        if (mean > 95) mean = 100;
        else if (mean < 5) mean = 0;
        if ((mean > last_mean + 2) || (mean < last_mean - 2)) {
            last_mean = mean;
            pot.val = last_mean;
            write_package(pot); 
            //printf("VOL: %d\n", mean);
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void pot2_task(void *p) {
    btn_t pot;
    pot.ID[0] = 'P';
    pot.ID[1] = '2';

    adc_init();
    adc_gpio_init(POT_2);
    printf("ADC INICIADO \n");
    int result;
    int values[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    while (true) {
        adc_select_input(1);
        result = adc_read();
        result = result/41;
        values[(i++)%10] = result;
        int mean = (values[0] + values[1] + values[2] + values[3] + values[4] + values[5] + values[6] + values[7] + values[8] + values[9])/10;
        printf("VOL: %d\n", mean);
        //xQueueSend(xQueueADC, &mean, 0);
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void write_package(btn_t data) {
    uart_putc_raw(HC06_UART_ID, data.val);
    uart_putc_raw(HC06_UART_ID, data.ID[0]);
    uart_putc_raw(HC06_UART_ID, data.ID[1]);
    uart_putc_raw(HC06_UART_ID, -1);
}

void btn_task(void *p){
    btn_init();
    printf("BTN_INIT");

    uart_init(HC06_UART_ID, HC06_BAUD_RATE);
    gpio_set_function(HC06_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(HC06_RX_PIN, GPIO_FUNC_UART);
    hc06_init("LUCAS_FEDE", "1234");

    btn_t btn;
    while (1){
        if (xQueueReceive(xQueueBTN, &btn,pdMS_TO_TICKS(100))) {
            //printf("btn: %d %d\n",btn.val, btn.ID);
            write_package(btn); 
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


    //xTaskCreate(btn_task, "btn", 4095, NULL, 1, NULL);
    xTaskCreate(pot1_task, "ADC", 4095, NULL, 1, NULL);
    //xTaskCreate(adc_filter_task, "adc_filter_task", 4096, NULL, 1, NULL);


    vTaskStartScheduler();



    while (true)
        ;
}
