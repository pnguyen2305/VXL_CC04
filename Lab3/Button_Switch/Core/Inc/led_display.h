/*
 * led_display.h
 *
 *  Created on: Oct 20, 2026
 *      Author: DELL
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

extern int led_buffer[4];

void display7SEG(int num);
void update7SEG(int index);
void clearAllTrafficLights(void);
void toggleRedTrafficLights(void);
void toggleAmberTrafficLights(void);
void toggleGreenTrafficLights(void);

#endif /* INC_LED_DISPLAY_H_ */
