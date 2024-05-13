#include <Arduino.h>

#include <HardwareSerial.h>

#include "input_keypads.h"

char *keys_layout[6][8] = {
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

  init_pins();
}

void loop()
{

  uint8_t scan_out;

  scan_out = read_key();
#ifdef DEBUG
  if (!(scan_out & 0x10))
  {
    Serial.print(", scan_out == ");
    Serial.print(scan_out, HEX);
    Serial.print(", key == ");
    Serial.print(keys_layout[scan_in][(scan_out & 0xE0) >> 5]);
  }
#endif
    digitalWrite(output_b7, scan_out & 0x80);
    digitalWrite(output_b6, scan_out & 0x40);
    digitalWrite(output_b5, scan_out & 0x20);
    digitalWrite(output_b4, scan_out & 0x10);
    digitalWrite(output_b2, scan_out & 0x04);
    digitalWrite(output_b1, scan_out & 0x02);
    digitalWrite(output_b0, scan_out & 0x01);

  delayMicroseconds(100);
}
