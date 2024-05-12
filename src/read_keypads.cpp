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

  uint8_t scan_in;
  uint8_t scan_out;
  scan_in =
      digitalRead(input_b2) * 4 +
      digitalRead(input_b1) * 2 +
      digitalRead(input_b0);

#ifdef DEBUG
  Serial.println();
  Serial.print("Périphérique *** scan_in == ");
  Serial.print(scan_in);
#endif

  scan_out = read_key(scan_in);
  if (!(scan_out & 0x10))
  {
#ifdef DEBUG
    Serial.print(", scan_out == ");
    Serial.print(scan_out, HEX);
    Serial.print(", key == ");
    Serial.print(keys_layout[scan_in][(scan_out & 0xE0) >> 5]);
#endif
  }
    digitalWrite(output_b7, scan_out & 0x80);
    digitalWrite(output_b6, scan_out & 0x40);
    digitalWrite(output_b5, scan_out & 0x20);
    digitalWrite(output_b4, scan_out & 0x10);

  delayMicroseconds(100);
}
