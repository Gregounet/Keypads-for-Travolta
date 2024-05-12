#include <Arduino.h>

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "input_keypads.h"

int keypad1_r1 = KEYPAD1_R1;
int keypad1_r2 = KEYPAD1_R2;
int keypad1_r3 = KEYPAD1_R3;
int keypad1_r4 = KEYPAD1_R4;

int keypad1_c1 = KEYPAD1_C1;
int keypad1_c2 = KEYPAD1_C2;
int keypad1_c3 = KEYPAD1_C3;

int keypad2_r1 = KEYPAD2_R1;
int keypad2_r2 = KEYPAD2_R2;
int keypad2_r3 = KEYPAD2_R3;
int keypad2_r4 = KEYPAD2_R4;

int keypad2_c1 = KEYPAD2_C1;
int keypad2_c2 = KEYPAD2_C2;
int keypad2_c3 = KEYPAD2_C3;

int output_b4 = OUTPUT_B4;
int output_b5 = OUTPUT_B5;
int output_b6 = OUTPUT_B6;
int output_b7 = OUTPUT_B7;

int input_b0 = INPUT_B0;
int input_b1 = INPUT_B1;
int input_b2 = INPUT_B2;

/*
 * Right nibble (bits 0, 1 and 2) == keypad scan input
 * Left nibble (bits 5, 6 and 7 as bit 4 == 00) == keypad scan output
 *
 */

// uint8_t key_out[2][23] = {
//     {0x01, 0x02, 0x03, 0x55, 0x46, 0x42, 0x04, 0x05, 0x06, 0x47, 0x15, 0x14, 0x07, 0x10, 0x11, 0x51, 0x52, 0x53, 0x20, 0x00, 0x50, 0x56, 0x57},
//     {0x30, 0x21, 0x22, 0x23, 0x24, 0x54, 0x25, 0x26, 0x27, 0x17, 0x40, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x16, 0x41, 0x43, 0x44, 0x45}};

uint8_t key_out[2][23] = {
    {0x20, 0x40, 0x60, 0xA5, 0xC4, 0x44, 0x80, 0xA0, 0xC0, 0xE4, 0xA1, 0x81, 0xE0, 0x01, 0x21, 0x25, 0x45, 0x65, 0x02, 0x00, 0x05, 0xC5, 0xE5},
    {0x03, 0x22, 0x42, 0x62, 0x82, 0x85, 0xA2, 0xC2, 0xE2, 0xE1, 0x04, 0x23, 0x43, 0x63, 0x83, 0xA3, 0xC3, 0xE3, 0xC1, 0x24, 0x64, 0x84, 0xA4}};

void init_pins(void)
{
  pinMode(keypad1_r1, INPUT_PULLUP);
  pinMode(keypad1_r2, INPUT_PULLUP);
  pinMode(keypad1_r3, INPUT_PULLUP);
  pinMode(keypad1_r4, INPUT_PULLUP);

  pinMode(keypad1_c1, INPUT);
  pinMode(keypad1_c2, INPUT);
  pinMode(keypad1_c3, INPUT);

  pinMode(keypad2_r1, INPUT_PULLUP);
  pinMode(keypad2_r2, INPUT_PULLUP);
  pinMode(keypad2_r3, INPUT_PULLUP);
  pinMode(keypad2_r4, INPUT_PULLUP);

  pinMode(keypad2_c1, INPUT);
  pinMode(keypad2_c2, INPUT);
  pinMode(keypad2_c3, INPUT);

  pinMode(output_b4, OUTPUT);
  pinMode(output_b5, OUTPUT);
  pinMode(output_b6, OUTPUT);
  pinMode(output_b7, OUTPUT);

  pinMode(input_b0, INPUT);
  pinMode(input_b1, INPUT);
  pinMode(input_b2, INPUT);
}

uint8_t
read_key(uint8_t scan_in)
{
  uint8_t modifier;
  uint8_t key_sharp = HIGH;

  uint8_t keypad[23];
  uint8_t key_pressed;

  uint8_t keycode;
  uint8_t scan_out = 0x10;

#ifdef DEBUG
  Serial.print("scan_in == ");
  Serial.println(scan_in);
#endif

  for (uint8_t i = 0; i < 23; i++)
    keypad[i] = HIGH;

  pinMode(keypad1_c1, OUTPUT);
  digitalWrite(keypad1_c1, LOW);
  keypad[0] = (uint8_t)digitalRead(keypad1_r1);
  keypad[6] = (uint8_t)digitalRead(keypad1_r2);
  keypad[12] = (uint8_t)digitalRead(keypad1_r3);
  keypad[18] = (uint8_t)digitalRead(keypad1_r4);
  digitalWrite(keypad1_c1, HIGH);
  pinMode(keypad1_c1, INPUT);

  pinMode(keypad1_c2, OUTPUT);
  digitalWrite(keypad1_c2, LOW);
  keypad[1] = (uint8_t)digitalRead(keypad1_r1);
  keypad[7] = (uint8_t)digitalRead(keypad1_r2);
  keypad[13] = (uint8_t)digitalRead(keypad1_r3);
  keypad[19] = (uint8_t)digitalRead(keypad1_r4);
  digitalWrite(keypad1_c2, HIGH);
  pinMode(keypad1_c2, INPUT);

  pinMode(keypad1_c3, OUTPUT);
  digitalWrite(keypad1_c3, LOW);
  keypad[2] = (uint8_t)digitalRead(keypad1_r1);
  keypad[8] = (uint8_t)digitalRead(keypad1_r2);
  keypad[14] = (uint8_t)digitalRead(keypad1_r3);
  keypad[20] = (uint8_t)digitalRead(keypad1_r4);
  digitalWrite(keypad1_c3, HIGH);
  pinMode(keypad1_c3, INPUT);

  pinMode(keypad2_c1, OUTPUT);
  digitalWrite(keypad2_c1, LOW);
  keypad[3] = (uint8_t)digitalRead(keypad2_r1);
  keypad[9] = (uint8_t)digitalRead(keypad2_r2);
  keypad[15] = (uint8_t)digitalRead(keypad2_r3);
  keypad[21] = (uint8_t)digitalRead(keypad2_r4);
  digitalWrite(keypad2_c1, HIGH);
  pinMode(keypad2_c1, INPUT);

  pinMode(keypad2_c2, OUTPUT);
  digitalWrite(keypad2_c2, LOW);
  keypad[4] = (uint8_t)digitalRead(keypad2_r1);
  keypad[10] = (uint8_t)digitalRead(keypad2_r2);
  keypad[16] = (uint8_t)digitalRead(keypad2_r3);
  keypad[22] = (uint8_t)digitalRead(keypad2_r4);
  digitalWrite(keypad2_c2, HIGH);
  pinMode(keypad2_c2, INPUT);

  pinMode(keypad2_c3, OUTPUT);
  digitalWrite(keypad2_c3, LOW);
  keypad[5] = (uint8_t)digitalRead(keypad2_r1);
  keypad[11] = (uint8_t)digitalRead(keypad2_r2);
  keypad[17] = (uint8_t)digitalRead(keypad2_r3);
  key_sharp = (uint8_t)digitalRead(keypad2_r4);
  digitalWrite(keypad2_c3, HIGH);
  pinMode(keypad2_c3, INPUT);

  // "#"" used as modifier

  modifier = (key_sharp == LOW) ? 1 : 0;

  // smallest keycode takes precedence
  for (key_pressed = 0; key_pressed < 23; key_pressed++)
    if (keypad[key_pressed] == LOW)
      break;

#ifdef DEBUG
  Serial.print("key_pressed == ");
  Serial.println(key_pressed);

  Serial.print("modifier == ");
  Serial.println(modifier);
#endif

  if (key_pressed < 23)
  {
    keycode = key_out[modifier][key_pressed];
#ifdef DEBUG
    Serial.print("keycode == 0x");
    Serial.println(keycode, HEX);
#endif
    if ((keycode & 0x07) == scan_in)
      scan_out = (keycode & 0xF0) | (scan_in & 0x0F);
  }

#ifdef DEBUG
  Serial.print("scan_out == ");
  Serial.println(scan_out);
#endif

  return scan_out;
}
