#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

#define KEYPAD1_R1 5
#define KEYPAD1_R2 4
#define KEYPAD1_R3 3
#define KEYPAD1_R4 2
#define KEYPAD1_C1 1
#define KEYPAD1_C2 0
#define KEYPAD1_C3 A6

#define KEYPAD2_R1 A5
#define KEYPAD2_R2 A4
#define KEYPAD2_R3 A3
#define KEYPAD2_R4 A2
#define KEYPAD2_C1 6
#define KEYPAD2_C2 7
#define KEYPAD2_C3 8

uint8_t read_key (uint8_t scan_in);

#endif /* INPUT_H */
