#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI   u8g2  (U8G2_R0, 5, 22, 17); //cs=5, dc=22, res=17

int xValue, yValue;
int joyX = 36;
int joyY = 39;

struct pixel {
  bool lys;
} Display[128][64];






void draw( int i, int j) {
  u8g2.drawPixel(i, j);
}

void opdater() {
  for (int i = 0; i < 128; i++) {
    for (int j = 0; j < 64; j++) {
      if (Display[i][j].lys == true) {
        draw(i, j);
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.firstPage();
  do {
    xValue = analogRead(joyX);
    yValue = analogRead(joyY);

    //print the values with to plot or view
    Serial.print(xValue);
    Serial.print("\t");
    Serial.println(yValue);
    
    Display[yValue/32][xValue/64].lys = true;
    opdater();
  } while ( u8g2.nextPage() );
}
