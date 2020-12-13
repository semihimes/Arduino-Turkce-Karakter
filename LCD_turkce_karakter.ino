/*
 * HD44780 Özel karakter belleği kullanarak türkçe karakter karşılıklarını
 * kod karmaşası yaratmadan yazdırır. Bunun için LiquidCrystalTr.cpp'ye
 * begin() fonksiyonuna özel karakter belleğine (ilk 6 byte) türkçe karakterleri atayan
 * işlev gömülmüştür. Bu karakterleri "seamless" şekilde kullanabilmek için
 * PrintTr.cpp'ye write() ve print() işlevlerinde gerekli düzenleme yapılmıştır.
 * bu değişiklik pratikte kullanılmayan bazı sembollerin kullanılmasını engeller.
 * Semih
 */
#include "LiquidCrystalTr.h"

#include <string.h>
#include <inttypes.h>



//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(0,1,2,3,4,5);

void setup() 
{

  lcd.begin(16,2);
  
}

void loop() 
{
  lcd.clear();
  lcd.print("Türkçe karakterler");
  lcd.setCursor(0,1);
  lcd.print("ıİöÖüÜğĞşŞ");
  delay(3000);lcd.clear();

  lcd.print(F("Flash Makrosuyla"));
  lcd.setCursor(0,1);
  lcd.print(F("ıİöÖüÜğĞşŞ"));
  delay(3000);
  lcd.clear();
  lcd.print(F("noktalama ve"));
  lcd.setCursor(0,1);
  lcd.print(F("bazı semboller"));
  delay(3000);
  lcd.clear();
  lcd.print(F(".,!?:;'^#*/-+_="));
  lcd.setCursor(0,1);
  lcd.print(F("&%[](){}@$<>"));lcd.print(char(223));
  delay(3000); 
}
