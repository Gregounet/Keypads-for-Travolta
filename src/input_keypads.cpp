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

int output_b0 = OUTPUT_B0;
int output_b1 = OUTPUT_B1;
int output_b2 = OUTPUT_B2;
int output_b4 = OUTPUT_B4;
int output_b5 = OUTPUT_B5;
int output_b6 = OUTPUT_B6;
int output_b7 = OUTPUT_B7;


/*
 * Left nibble (bits 5, 6 and 7 as bit 4 == 00) == keypad scan output
 * Right nibble (bits 0, 1 and 2) == keypad scan input
 *
 */

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

  pinMode(output_b0, OUTPUT);
  pinMode(output_b1, OUTPUT);
  pinMode(output_b2, OUTPUT);
  pinMode(output_b4, OUTPUT);
  pinMode(output_b5, OUTPUT);
  pinMode(output_b6, OUTPUT);
  pinMode(output_b7, OUTPUT);

}

uint8_t
read_key(void)
{
  uint8_t modifier;
  uint8_t key_pressed;
  uint8_t keypad[23];

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
  modifier = !(uint8_t)digitalRead(keypad2_r4);
  digitalWrite(keypad2_c3, HIGH);
  pinMode(keypad2_c3, INPUT);

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
    return key_out[modifier][key_pressed];
  else
    return 0x10;
}
