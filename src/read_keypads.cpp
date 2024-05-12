#include <Arduino.h>
#include "input.h"

char* keys_layout[6][8] = {
    {"0", "1", "2", "3", "4", "5", "6", "7"},
    {"8", "9", "N/A", "N/A", "_", "?", "L", "P"},
    {"+", "W", "E", "R", "T", "U", "I", "O"},
    {"Q", "S", "D", "F", "G", "H", "J", "K"},
    {"A", "Z", "X", "C", "V", "B", "M", "."},
    {"-", "*", "/", "=", "Y", "N", "Clr", "Ent"}};

void setup()
{
  Serial.begin(9600);
  delay(20);

  pinMode(KEYPAD1_R1, INPUT_PULLUP);
  pinMode(KEYPAD1_R2, INPUT_PULLUP);
  pinMode(KEYPAD1_R3, INPUT_PULLUP);
  pinMode(KEYPAD1_R4, INPUT_PULLUP);

  pinMode(KEYPAD1_C1, INPUT);
  pinMode(KEYPAD1_C2, INPUT);
  pinMode(KEYPAD1_C3, INPUT);

  pinMode(KEYPAD2_R1, INPUT_PULLUP);
  pinMode(KEYPAD2_R2, INPUT_PULLUP);
  pinMode(KEYPAD2_R3, INPUT_PULLUP);
  pinMode(KEYPAD2_R4, INPUT_PULLUP);

  pinMode(KEYPAD2_C1, INPUT);
  pinMode(KEYPAD2_C2, INPUT);
  pinMode(KEYPAD2_C3, INPUT);
}

void loop()
{
  for (int i = 0; i < 6; i++)
  {
    int j;
    // Serial.print(i);
    // Serial.print(" -> Ox");
    // Serial.println(read_port2(i),HEX);
    j = read_key(i);
    if (j != 1) {
      // Serial.print("i == ");
      // Serial.print(i);
      // Serial.print(", j == ");
      // Serial.print(j,HEX);
      // Serial.print(", key == ");
      Serial.println(keys_layout[i][j>>1]);
    }
  }
  delay(100);
}
