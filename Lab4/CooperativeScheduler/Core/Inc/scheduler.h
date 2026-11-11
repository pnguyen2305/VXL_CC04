/*
 * scheduler.h
 *
 *  Created on: Nov 4, 2026
 *      Author: DELL
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdint.h"

typedef struct {
    void (*pTask)(void);
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
    uint32_t TaskID;
    uint32_t Target_Time;
} sTask;

#define SCH_MAX_TASKS 40
extern uint8_t current_index_task;
extern uint32_t system_time;

void SCH_Init(void);
void SCH_Update(void);
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t TASK_INDEX);

#endif /* INC_SCHEDULER_H_ */
