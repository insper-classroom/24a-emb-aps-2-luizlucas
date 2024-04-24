#ifndef FUNC
#define FUNC

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include <string.h>

#include "pico/stdlib.h"
#include <stdio.h>

#define BTN_R_1 18
#define BTN_R_2 19
#define BTN_B_1 2
#define BTN_B_2 3
#define BTN_G_1 20
#define BTN_G_2 21
#define BTN_TEST 17
#define JU 15
#define JD 14
#define JL 13
#define JR 12
#define POT_1 26
#define POT_2 27

void btn_init();

#endif // FUNC
