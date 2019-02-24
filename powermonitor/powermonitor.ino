#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(13, 11, 10, 9);

int pin = A0;
float a;
bool v = 0;
bool vv = 0;
float last = 0;
float now = 0;
float kw = 0;
float minA = 5000;
float maxA = 0;
char* dispPow;

void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT_PULLUP);
  last = millis();

  u8g.setFont(u8g_font_unifont);
}

void loop() {
  a = analogRead(pin);
  if (a > maxA)
    maxA = a;
  if (a < minA)
    minA = a;

  v = a < minA + ((maxA-minA) / 2);
  if (v == vv)
    return;

  vv = v;
  if (!v) {
    now = millis();
    kw = 1/((now - last)/1000)*60*60/3200;
    if (kw > 15) return;
    Serial.print(kw,3);
    Serial.println("  kW");

    u8g.firstPage();
    do {
      u8g.setPrintPos(0,0);
      u8g.drawStr(0, 30, "Power:        kW");
      u8g.setPrintPos(51, 30);  // set position
      u8g.print(kw, 3);
      u8g.setColorIndex(1);
    } while (u8g.nextPage());

    last = now;
  }

}
