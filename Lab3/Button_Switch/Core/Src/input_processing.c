/*
 * input_processing.c
 *
 *  Created on: Oct 20, 2026
 *      Author: DELL
 */

#include "input_processing.h"
#include "input_reading.h"

int system_mode = 1;

int red_duration = 5;
int amber_duration = 2;
int green_duration = 3;
int temp_red = 5;
int temp_amber = 2;
int temp_green = 3;

int btn1_flag = 0;
int btn2_flag = 0;
int btn3_flag = 0;

void fsm_for_input_processing(void) {
    if (is_button_pressed(0)) {
        if (btn1_flag == 0) {
            btn1_flag = 1;

            system_mode++;
            if (system_mode > 4) system_mode = 1;

            temp_red = red_duration;
            temp_amber = amber_duration;
            temp_green = green_duration;
        }
    } else {
        btn1_flag = 0;
    }

    if (is_button_pressed(1)) {
        if (btn2_flag == 0) {
            btn2_flag = 1;

            if (system_mode == 2) {
                temp_red++;
                temp_green++;
                if (temp_red > 99) {
                    temp_green = 1;
                    temp_red = temp_amber + temp_green;
                }
            }
            else if (system_mode == 3) {
                temp_amber++;
                temp_red++;
                if (temp_red > 99) {
                    temp_amber = 1;
                    temp_red = temp_amber + temp_green;
                }
            }
            else if (system_mode == 4) {
                temp_green++;
                temp_red++;
                if (temp_red > 99) {
                    temp_green = 1;
                    temp_red = temp_amber + temp_green;
                }
            }
        }
    } else {
        btn2_flag = 0;
    }

    if (is_button_pressed(2)) {
        if (btn3_flag == 0) {
            btn3_flag = 1;
            if (system_mode == 2 || system_mode == 3 || system_mode == 4) {
                red_duration = temp_red;
                amber_duration = temp_amber;
                green_duration = temp_green;
            }
        }
    } else {
        btn3_flag = 0;
    }
}
