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
    gpio_init(JU);
    gpio_set_dir(JU, GPIO_IN);
    gpio_pull_up(JU);
    gpio_init(JD);
    gpio_set_dir(JD, GPIO_IN);
    gpio_pull_up(JD);
    gpio_init(JL);
    gpio_set_dir(JL, GPIO_IN);
    gpio_pull_up(JL);
    gpio_init(JR);
    gpio_set_dir(JR, GPIO_IN);
    gpio_pull_up(JR);
    gpio_init(BTN_TEST);
    gpio_set_dir(BTN_TEST, GPIO_IN);
    gpio_pull_up(BTN_TEST);
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
}