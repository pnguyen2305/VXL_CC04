#include "scheduler.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

void SCH_Init(void) {
    current_index_task = 0;
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = 0;
    }
}

void SCH_Update(void) {
    if (current_index_task == 0) return;

    // Cập nhật O(1): Chỉ tìm thằng ĐẦU TIÊN đang chờ (Delay > 0) để trừ thời gian
    for (int i = 0; i < current_index_task; i++) {
        if (SCH_tasks_G[i].Delay > 0) {
            SCH_tasks_G[i].Delay -= 1;

            if (SCH_tasks_G[i].Delay == 0) {
                SCH_tasks_G[i].RunMe = 1;
                // Nếu các task đứng ngay sau cũng có Delta = 0 (cùng thời điểm), bật cờ luôn
                int j = i + 1;
                while (j < current_index_task && SCH_tasks_G[j].Delay == 0) {
                    SCH_tasks_G[j].RunMe = 1;
                    j++;
                }
            }
            break; // Tìm thấy và trừ xong thì thoát ngay để đảm bảo O(1)
        }
    }
}

uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    if (current_index_task >= SCH_MAX_TASKS) return SCH_MAX_TASKS;

    uint8_t newIndex = 0;
    uint32_t accumulated_delay = 0;

    // Tìm vị trí chèn để đảm bảo tính tuần tự của Delta Queue
    while (newIndex < current_index_task) {
        if (accumulated_delay + SCH_tasks_G[newIndex].Delay > DELAY) {
            break;
        }
        accumulated_delay += SCH_tasks_G[newIndex].Delay;
        newIndex++;
    }

    uint32_t deltaDelay = DELAY - accumulated_delay;

    // Dịch các task phía sau xuống 1 ô để lấy chỗ trống
    for (int i = current_index_task; i > newIndex; i--) {
        SCH_tasks_G[i] = SCH_tasks_G[i - 1];
    }

    SCH_tasks_G[newIndex].pTask = pFunction;
    SCH_tasks_G[newIndex].Delay = deltaDelay;
    SCH_tasks_G[newIndex].Period = PERIOD;
    SCH_tasks_G[newIndex].Target_Time = system_time + DELAY; // Neo mốc thời gian tuyệt đối
    SCH_tasks_G[newIndex].TaskID = current_index_task;

    // Nếu Task bị trễ (hoặc chạy cùng lúc với Task trước) thì cho phép chạy luôn
    if (deltaDelay == 0 && (newIndex == 0 || SCH_tasks_G[newIndex - 1].RunMe == 1)) {
        SCH_tasks_G[newIndex].RunMe = 1;
    } else {
        SCH_tasks_G[newIndex].RunMe = 0;
    }

    // Trừ bù phần Delay của task bị đẩy lùi về sau
    if (newIndex + 1 < current_index_task + 1) {
        SCH_tasks_G[newIndex + 1].Delay -= deltaDelay;
    }

    current_index_task++;
    return SCH_tasks_G[newIndex].TaskID;
}

void SCH_Dispatch_Tasks(void) {
    if (current_index_task > 0 && SCH_tasks_G[0].RunMe > 0) {
        (*SCH_tasks_G[0].pTask)(); // Thực thi Task
        SCH_tasks_G[0].RunMe -= 1;

        void (*tempTask)() = SCH_tasks_G[0].pTask;
        uint32_t tempPeriod = SCH_tasks_G[0].Period;
        uint32_t targetTime = SCH_tasks_G[0].Target_Time;

        SCH_Delete_Task(0);

        // TÍNH BÙ SAI SỐ KHI NẠP LẠI TASK (Khử Cumulative Drift)
        if (tempPeriod != 0) {
            uint32_t next_target = targetTime + tempPeriod; // Đích đến tiếp theo theo lý thuyết
            uint32_t current_time = system_time;
            uint32_t new_delay = 0;

            if (next_target > current_time) {
                new_delay = next_target - current_time; // Trừ bớt thời gian CPU đã bị ngâm
            } else {
                new_delay = 0; // Đã quá trễ, cần chạy gấp ở lần sau
            }

            SCH_Add_Task(tempTask, new_delay, tempPeriod);
        }
    }
}

uint8_t SCH_Delete_Task(uint32_t TASK_INDEX) {
    if (TASK_INDEX >= current_index_task) return 0;

    // Nếu xóa 1 task ở giữa chừng, phải cộng dồn Delay của nó cho task đứng ngay sau
    // để tránh việc task phía sau bị chạy sớm hơn dự kiến.
    if (TASK_INDEX + 1 < current_index_task) {
        SCH_tasks_G[TASK_INDEX + 1].Delay += SCH_tasks_G[TASK_INDEX].Delay;
    }

    // Dồn mảng lên lấp chỗ trống
    for (int i = TASK_INDEX; i < current_index_task - 1; i++) {
        SCH_tasks_G[i] = SCH_tasks_G[i + 1];
    }

    current_index_task--;
    SCH_tasks_G[current_index_task].pTask = 0;
    SCH_tasks_G[current_index_task].Delay = 0;
    SCH_tasks_G[current_index_task].Period = 0;
    SCH_tasks_G[current_index_task].RunMe = 0;

    return 1;
}
