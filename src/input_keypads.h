#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
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

#define INPUT_B0 13
#define INPUT_B1 14
#define INPUT_B2 A1

#define OUTPUT_B4 12
#define OUTPUT_B5 11
#define OUTPUT_B6 10
#define OUTPUT_B7 9

extern int output_b4;
extern int output_b5;
extern int output_b6;
extern int output_b7;

extern int input_b0;
extern int input_b1;
extern int input_b2;

void init_pins(void);
uint8_t read_key(uint8_t scan_in);

#endif /* INPUT_H */
