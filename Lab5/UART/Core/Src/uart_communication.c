#include "uart_communication.h"
#include "command_parser.h"
#include "software_timer.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

typedef enum {
    UART_IDLE,
    UART_WAIT_OK
} UartCommState;

static UartCommState comm_state = UART_IDLE;
static uint32_t adc_value = 0;
static char tx_packet[32];

// Handle !RST# request and 3s !OK# timeout
void uart_communication_fsm(void) {
    switch (comm_state) {
        case UART_IDLE:
            if (command_flag == 1) {
                command_flag = 0;
                if (command_data == CMD_RST) {
                    adc_value = HAL_ADC_GetValue(&hadc1);
                    sprintf(tx_packet, "\r\n!ADC=%lu#", adc_value);
                    HAL_UART_Transmit(&huart2, (uint8_t *)tx_packet, strlen(tx_packet), 100);
                    setTimer1(300); // 3s timeout
                    comm_state = UART_WAIT_OK;
                }
            }
            break;

        case UART_WAIT_OK:
            if (command_flag == 1) {
                command_flag = 0;
                if (command_data == CMD_OK) {
                    comm_state = UART_IDLE;
                }
            } else if (timer1_flag == 1) {
                // Resend previous packet
                HAL_UART_Transmit(&huart2, (uint8_t *)tx_packet, strlen(tx_packet), 100);
                setTimer1(300);
            }
            break;

        default:
            comm_state = UART_IDLE;
            break;
    }
}
