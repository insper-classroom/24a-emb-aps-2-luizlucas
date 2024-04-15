#include "funcoes.h"

void btn_init(){
    gpio_init(BTN_R_1);
    gpio_set_dir(BTN_R_1, GPIO_IN);
    gpio_pull_up(BTN_R_1);
    gpio_init(BTN_R_2);
    gpio_set_dir(BTN_R_2, GPIO_IN);
    gpio_pull_up(BTN_R_2);
    gpio_init(BTN_B_1);
    gpio_set_dir(BTN_B_1, GPIO_IN);
    gpio_pull_up(BTN_B_1);
    gpio_init(BTN_B_2);
    gpio_set_dir(BTN_B_2, GPIO_IN);
    gpio_pull_up(BTN_B_2);
    gpio_init(BTN_G_1);
    gpio_set_dir(BTN_G_1, GPIO_IN);
    gpio_pull_up(BTN_G_1);
    gpio_init(BTN_G_2);
    gpio_set_dir(BTN_G_2, GPIO_IN);
    gpio_pull_up(BTN_G_2);
    gpio_init(JS_1);
    gpio_set_dir(JS_1, GPIO_IN);
    gpio_pull_up(JS_1);
    gpio_init(JS_2);
    gpio_set_dir(JS_2, GPIO_IN);
    gpio_pull_up(JS_2);
    gpio_init(JS_3);
    gpio_set_dir(JS_3, GPIO_IN);
    gpio_pull_up(JS_3);
    gpio_init(JS_4);
    gpio_set_dir(JS_4, GPIO_IN);
    gpio_pull_up(JS_4);
    gpio_init(BTN_TEST);
    gpio_set_dir(BTN_TEST, GPIO_IN);
    gpio_pull_up(BTN_TEST);


    
}