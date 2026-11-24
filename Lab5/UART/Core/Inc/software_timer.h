#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer0_flag; // LED blinky flag
extern int timer1_flag; // 3s timeout flag

void setTimer0(int duration);
void setTimer1(int duration);
void timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
