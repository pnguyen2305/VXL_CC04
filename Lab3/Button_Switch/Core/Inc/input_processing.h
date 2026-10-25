/*
 * input_processing.h
 *
 *  Created on: Oct 20, 2026
 *      Author: DELL
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

extern int system_mode;
extern int red_duration;
extern int amber_duration;
extern int green_duration;
extern int temp_red;
extern int temp_amber;
extern int temp_green;

void fsm_for_input_processing(void);

#endif /* INC_INPUT_PROCESSING_H_ */
