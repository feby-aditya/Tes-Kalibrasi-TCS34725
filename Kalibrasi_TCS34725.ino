#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_60X
);

uint16_t r, g, b, c;

// nilai kalibrasi
float R_white = 7720;
float G_white = 11500;
float B_white = 9720;

float R_black = 0;
float G_black = 0;
float B_black = 0;

void setup() {
  Serial.begin(115200);

  if (!tcs.begin()) {
    Serial.println("Sensor tidak ditemukan");
    while (1);
  }

  Serial.println("Sensor siap");
}

void loop() {

  tcs.getRawData(&r, &g, &b, &c);

  float r_cal = (r - R_black) / (R_white - R_black);
  float g_cal = (g - G_black) / (G_white - G_black);
  float b_cal = (b - B_black) / (B_white - B_black);

  int R = r_cal * 255;
  int G = g_cal * 255;
  int B = b_cal * 255;

  Serial.print("R: "); Serial.print(r);
  Serial.print("   G: "); Serial.print(g);
  Serial.print("   B: "); Serial.print(b);
  Serial.print("   C: "); Serial.print(c);

  Serial.print("   Calibrated R: "); Serial.print(R);
  Serial.print("   G: "); Serial.print(G);
  Serial.print("   B: "); Serial.println(B);

  delay(500);
}