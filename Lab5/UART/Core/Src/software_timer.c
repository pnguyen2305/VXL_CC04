#include "software_timer.h"

static int timer0_counter = 0;
static int timer1_counter = 0;

int timer0_flag = 0;
int timer1_flag = 0;

// Set timer0 (duration * 10ms)
void setTimer0(int duration) {
    timer0_counter = duration;
    timer0_flag = 0;
}

// Set timer1 (duration * 10ms)
void setTimer1(int duration) {
    timer1_counter = duration;
    timer1_flag = 0;
}

// Update timers every 10ms
void timerRun(void) {
    if (timer0_counter > 0) {
        timer0_counter--;
        if (timer0_counter == 0) {
            timer0_flag = 1;
        }
    }
    if (timer1_counter > 0) {
        timer1_counter--;
        if (timer1_counter == 0) {
            timer1_flag = 1;
        }
    }
}
