#include <Wire.h> 
#include <LiquidCrystalTr_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("BÜYÜK: İÜĞİŞÇÖ");
  lcd.setCursor(0,1);
  lcd.print("küçük: ıüğişçö");
  delay(5000);
  lcd.clear();
  lcd.print(F("Flaş makro ile"));
  lcd.setCursor(0,1);
  lcd.print(F("İÜĞİŞÇÖ-ıüğişçö"));
}

void loop()
{
	// Do nothing here...
}
