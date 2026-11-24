#include "command_parser.h"

typedef enum {
    CP_IDLE,
    CP_GOT_EXCL,
    CP_GOT_R,
    CP_GOT_RS,
    CP_GOT_RST,
    CP_GOT_O,
    CP_GOT_OK
} ParserState;

uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

uint8_t command_flag = 0;
uint8_t command_data = CMD_NONE;

static ParserState parser_state = CP_IDLE;
static uint8_t read_index = 0;

// Parse !RST# and !OK# from ring buffer
void command_parser_fsm(void) {
    while (read_index != index_buffer) {
        uint8_t ch = buffer[read_index++];
        if (read_index == MAX_BUFFER_SIZE) {
            read_index = 0;
        }

        // Restart frame on '!'
        if (ch == '!') {
            parser_state = CP_GOT_EXCL;
            continue;
        }

        switch (parser_state) {
            case CP_IDLE:
                break;

            case CP_GOT_EXCL:
                if (ch == 'R') parser_state = CP_GOT_R;
                else if (ch == 'O') parser_state = CP_GOT_O;
                else parser_state = CP_IDLE;
                break;

            case CP_GOT_R:
                parser_state = (ch == 'S') ? CP_GOT_RS : CP_IDLE;
                break;

            case CP_GOT_RS:
                parser_state = (ch == 'T') ? CP_GOT_RST : CP_IDLE;
                break;

            case CP_GOT_RST:
                if (ch == '#') {
                    command_flag = 1;
                    command_data = CMD_RST;
                }
                parser_state = CP_IDLE;
                break;

            case CP_GOT_O:
                parser_state = (ch == 'K') ? CP_GOT_OK : CP_IDLE;
                break;

            case CP_GOT_OK:
                if (ch == '#') {
                    command_flag = 1;
                    command_data = CMD_OK;
                }
                parser_state = CP_IDLE;
                break;

            default:
                parser_state = CP_IDLE;
                break;
        }
    }
}
