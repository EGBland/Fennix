#ifndef __DRIVER_PS2_H_DEFINED
#define __DRIVER_PS2_H_DEFINED 1


#define PS2_DATA_PORT 0x60
#define PS2_STATUS_REGISTER 0x64
#define PS2_COMMAND_REGISTER 0x64

#define PS2_COMMAND_PORT1_ENABLE 0xae
#define PS2_COMMAND_PORT1_DISABLE 0xad
#define PS2_COMMAND_PORT2_ENABLE 0xa8
#define PS2_COMMAND_PORT2_DISABLE 0xa7
#define PS2_COMMAND_READ_CONFIG_BYTE 0x20
#define PS2_COMMAND_WRITE_CONFIG_BYTE 0x60
#define PS2_COMMAND_CONTROLLER_SELF_TEST 0xaa
#define PS2_COMMAND_PORT1_SELF_TEST 0xab
#define PS2_COMMAND_PORT2_SELF_TEST 0xa9
#define PS2_COMMAND_SEND_TO_PORT2 0xd4

#define PS2_DEVICE_RESET 0xff

#define PS2_REPLY_PORT_SELF_TEST_OK 0x00
#define PS2_REPLY_PORT_SELF_TEST_CLOCK_LOW 0x01
#define PS2_REPLY_PORT_SELF_TEST_CLOCK_HIGH 0x02
#define PS2_REPLY_PORT_SELF_TEST_DATA_LOW 0x03
#define PS2_REPLY_PORT_SELF_TEST_DATA_HIGH 0x04
#define PS2_REPLY_CONTROLLER_SELF_TEST_OK 0x55
#define PS2_REPLY_CONTROLLER_SELF_TEST_FAILED 0xfc
#define PS2_REPLY_PORT_RESET_OK 0xaa
#define PS2_REPLY_PORT_RESET_ERROR 0xfc

#define PS2_KB_COMMAND_SET_LEDS 0xed
#define PS2_KB_COMMAND_ECHO 0xee
#define PS2_KB_COMMAND_SET_SCANCODE_SET 0xf0
#define PS2_KB_COMMAND_IDENTIFY 0xf2
#define PS2_KB_COMMAND_SET_TYPEMATIC 0xf3
#define PS2_KB_COMMAND_SCAN_ENABLE 0xf4
#define PS2_KB_COMMAND_SCAN_DISABLE 0xf5
#define PS2_KB_COMMAND_PARAM_RESET 0xf6
#define PS2_KB_COMMAND_MODE_TYPEMATIC_AND_REPEAT 0xf7
#define PS2_KB_COMMAND_MODE_MAKE_AND_RELEASE 0xf8
#define PS2_KB_COMMAND_MODE_MAKE 0xf9
#define PS2_KB_COMMAND_MODE_ALL 0xfa
#define PS2_KB_COMMAND_KEYMODE_TYPEMATIC_AND_REPEAT 0xfb
#define PS2_KB_COMMAND_KEYMODE_MAKE_AND_RELEASE 0xfc
#define PS2_KB_COMMAND_KEYMODE_MAKE 0xfd
#define PS2_KB_COMMAND_RESEND 0xfe

#define PS2_KB_SCANCODE_SET_GET 0x0
#define PS2_KB_SCANCODE_SET_1 0x1
#define PS2_KB_SCANCODE_SET_2 0x2
#define PS2_KB_SCANCODE_SET_3 0x3

#define PS2_KB_REPLY_ACK 0xfa
#define PS2_KB_REPLY_RESEND 0xfe
#define PS2_KB_REPLY_ECHO 0xee

// prep ps/2 controller and keyboard
unsigned char ps2_init();

// get status byte of ps/2 controller
unsigned char ps2_status();

// attempt read byte from ps/2 controller; returns 1 if byte read (result written to arg) and 0 otw
unsigned char ps2_read(unsigned char *received_byte);

// translate scancode to character. this sucks, do this another way
char ps2_translate(unsigned char sc);


#endif