#include <ps2.h>

#include <asm.h>

unsigned char ps2_is_read_ready();
void ps2_await_read();
unsigned char ps2_is_write_ready();
void ps2_await_write();
void ps2_send(unsigned char device, unsigned char byte);

unsigned char ps2_init() {
    // TODO check for PS/2 controller existence
    // TODO await read/write buffers!
    // disable PS/2 device ports
    ps2_await_write();
    outb(PS2_COMMAND_REGISTER, PS2_COMMAND_PORT1_DISABLE);
    ps2_await_write();
    outb(PS2_COMMAND_REGISTER, PS2_COMMAND_PORT2_DISABLE);

    // flush data buffer
    inb(PS2_DATA_PORT);

    // get config byte
    ps2_await_write();
    outb(PS2_COMMAND_REGISTER, PS2_COMMAND_READ_CONFIG_BYTE);
    ps2_await_read();
    unsigned char config = inb(PS2_DATA_PORT);
    unsigned char is_dual_port = config & (1<<5);

    // write new config
    config &= ~(1 | (1<<1) | (1<<6));
    ps2_await_write();
    outb(PS2_COMMAND_REGISTER, PS2_COMMAND_WRITE_CONFIG_BYTE);
    ps2_await_write();
    outb(PS2_DATA_PORT, config);

    // self-tests
    ps2_await_write();
    outb(PS2_COMMAND_REGISTER, PS2_COMMAND_CONTROLLER_SELF_TEST);
    ps2_await_read();
    unsigned char test_result = inb(PS2_DATA_PORT);
    if(test_result != PS2_REPLY_CONTROLLER_SELF_TEST_OK) {
        return 1;
    }
    // some controllers reset config on self-test, so restore
    ps2_await_write();
    outb(PS2_COMMAND_REGISTER, PS2_COMMAND_WRITE_CONFIG_BYTE);
    ps2_await_write();
    outb(PS2_DATA_PORT, config);

    // test ports
    ps2_await_write();
    outb(PS2_COMMAND_REGISTER, PS2_COMMAND_PORT1_SELF_TEST);
    ps2_await_read();
    unsigned char port1_result = inb(PS2_DATA_PORT);
    ps2_await_write();
    outb(PS2_COMMAND_REGISTER, PS2_COMMAND_PORT2_SELF_TEST);
    ps2_await_read();
    unsigned char port2_result = inb(PS2_DATA_PORT);
    if(port1_result != PS2_REPLY_PORT_SELF_TEST_OK || port2_result != PS2_REPLY_PORT_SELF_TEST_OK) {
        return 2;
    }
    // all good, enable port clocks and interrupts
    ps2_await_write();
    outb(PS2_COMMAND_REGISTER, PS2_COMMAND_PORT1_ENABLE);
    ps2_await_write();
    outb(PS2_COMMAND_REGISTER, PS2_COMMAND_PORT2_ENABLE);
    config |= 0x1;
    if(is_dual_port) {
        config |= 0x2;
    }
    ps2_await_write();
    outb(PS2_COMMAND_REGISTER, PS2_COMMAND_WRITE_CONFIG_BYTE);
    ps2_await_write();
    outb(PS2_DATA_PORT, config);

    // reset ports
    unsigned char port1_reset_result;
    unsigned char port2_reset_result = PS2_REPLY_PORT_RESET_OK;
    ps2_send(0, PS2_DEVICE_RESET);
    ps2_await_read();
    port1_reset_result = inb(PS2_DATA_PORT);
    if(is_dual_port) {
        ps2_send(1, PS2_DEVICE_RESET);
    }

    if(port1_reset_result == PS2_REPLY_PORT_RESET_OK && port2_reset_result == PS2_REPLY_PORT_RESET_OK) {
        return 0;
    }
    else {
        return 4;
    }
}

unsigned char ps2_status() {
    return inb(PS2_STATUS_REGISTER);
}

unsigned char ps2_is_read_ready() {
    return inb(PS2_STATUS_REGISTER) & 0x1;
}

void ps2_await_read() {
    // TODO timer
    unsigned char ps2_status;
    while(1) {
        ps2_status = inb(PS2_STATUS_REGISTER);
        if(ps2_status & 0x1) return;
    }
}

unsigned char ps2_is_write_ready() {
    return (~(inb(PS2_STATUS_REGISTER) & 0x2)) >> 1;
}

void ps2_await_write() {
    // TODO timer
    unsigned char ps2_status;
    while(1) {
        ps2_status = inb(PS2_STATUS_REGISTER);
        if(~(ps2_status & 0x2)) return;
    }
}

void ps2_send(unsigned char device, unsigned char byte) {
    // TODO timer
    if(device != 0) {
        // second device
        outb(PS2_COMMAND_REGISTER, PS2_COMMAND_SEND_TO_PORT2);
    }
    ps2_await_write();
    outb(PS2_DATA_PORT, byte);
}


void ps2_kb_set_mode(unsigned char mode) {
    ps2_send(0, mode);
}

char ps2_kb_translate(unsigned char scancode) {
    switch(scancode) {
        case 0x1c: return 'A';
        case 0x32: return 'B';
        case 0x21: return 'C';
        case 0x23: return 'D';
        case 0x24: return 'E';
        case 0x2b: return 'F';
        case 0x34: return 'G';
        case 0x33: return 'H';
        case 0x48: return 'I';
        case 0x3b: return 'J';
        case 0x42: return 'K';
        case 0x4b: return 'L';
        case 0x3a: return 'M';
        case 0x31: return 'N';
        case 0x44: return 'O';
        case 0x4d: return 'P';
        case 0x15: return 'Q';
        case 0x2d: return 'R';
        case 0x1b: return 'S';
        case 0x2c: return 'T';
        case 0x3c: return 'U';
        case 0x2a: return 'V';
        case 0x1d: return 'W';
        case 0x22: return 'X';
        case 0x35: return 'Y';
        case 0x1a: return 'Z';
        case 0x45: return '0';
        case 0x16: return '1';
        case 0x1e: return '2';
        case 0x26: return '3';
        case 0x25: return '4';
        case 0x2e: return '5';
        case 0x36: return '6';
        case 0x3d: return '7';
        case 0x3e: return '8';
        case 0x46: return '9';
        case 0x0e: return '`';
        case 0x4e: return '-';
        case 0x55: return '=';
        case 0x5c: return '\\';
        case 0x29: return ' ';
        case 0x54: return '[';
        case 0x4a: return '/';
        case 0x7e: return '*';
        case 0x7c: return '+';
        case 0x71: return '.';
        case 0x70: return '0';
        case 0x69: return '1';
        case 0x72: return '2';
        case 0x7a: return '3';
        case 0x6b: return '4';
        case 0x73: return '5';
        case 0x74: return '6';
        case 0x6c: return '7';
        case 0x75: return '8';
        case 0x7d: return '9';
        case 0x5b: return ']';
        case 0x4c: return ';';
        case 0x52: return '\'';
        case 0x41: return ',';
        case 0x49: return '.';
        default: return ' ';
    }
}