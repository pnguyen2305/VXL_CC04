/*
 * timer.h
 *
 *  Created on: Oct 20, 2026
 *      Author: DELL
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

extern int timer_flag[4]; // Cờ báo hiệu cho 4 bộ đếm

void setTimer(int index, int duration);
void timerRun();

#endif /* INC_TIMER_H_ */
