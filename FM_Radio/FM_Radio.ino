#include <Wire.h>
#include <LiquidCrystal.h>

unsigned char frekansH = 0;
unsigned char frekansL = 0;

unsigned int frekansB;
double frekans = 0;

static char frekans_ekran[15];

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Wire.begin();
  lcd.begin(16, 2);
  frekans = 93.0;
  frekansAyarla();
  lcd.setCursor(3, 0);
  lcd.print("FM Radyo");
}

void loop()
{
  int reading = analogRead(0);
  frekans = ((double)reading * (108.0 - 87.5)) / 1024.0 + 87.5;
  frekans = ((int)(frekans * 10)) / 10.0;
  frekansAyarla();
  dtostrf(frekans, 6, 2, frekans_ekran);
  lcd.setCursor(4, 1);
  lcd.print(frekans_ekran);
}

void frekansAyarla()
{
  frekansB = 4 * (frekans * 1000000 + 225000) / 32768;
  frekansH = frekansB >> 8;
  frekansL = frekansB & 0XFF;
  delay(100);
  Wire.beginTransmission(0x60);
  Wire.write(frekansH);
  Wire.write(frekansL);
  Wire.write(0xB0);
  Wire.write(0x10);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  delay(100);
}
