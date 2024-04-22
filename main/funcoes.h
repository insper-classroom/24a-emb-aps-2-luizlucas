#ifndef FUNC
#define FUNC

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include <string.h>

#include "pico/stdlib.h"
#include <stdio.h>

#define BTN_R_1 1
#define BTN_R_2 1
#define BTN_B_1 1
#define BTN_B_2 1
#define BTN_G_1 1
#define BTN_G_2 1
#define BTN_TEST 17
#define JS_1 18
#define JS_2 19
#define JS_3 20
#define JS_4 21
#define ADC_GP 26

void btn_init();

#endif // FUNC
