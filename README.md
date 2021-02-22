# Arduino-Turkce-Karakter
Arduino LiquidCrystal kütüphanesi Karakter Lcd ekranlarla çalışır. Nano ve uno ile 8x2,16x2 ve 20x4 ekranlarla denenmiştir . String türü değişkenlerde türkçe karakterler kullanıp yazdırılabilir.
LiquidCrysalTr klasöürünü ".../Arduino/libraries" klasörüne atıp "Arduino IDE"yi yeniden başlatarak kullanabilirsiniz.  

LiquidCrystalTr_I2C eklenmiştir. wire.h kütüphanesiyle çalışır 01/2021

Arduino IDE 1.8.12 denenmiştir.

Orjinal kütüphaneye eklenen kodlar ve işlevleri aşağıdaki gibidir

  LiquidCrystalTr.cpp
    1. satır :  #include "LiquidCrystalTr.h".
    168-183 aralığı satırlar: özel karakterler tanımlamaları.
    
  LiquidCrystalTr.h.
    1-2. satırlar tanımlama.
    5. satır : #include "PrintTr.h" değiştirilmiş "Print.h" kütüphanesini tanımlama

  PrintTr.cpp
    31. satır: #include "PrintTr.h".
    51-72 aralığı satırlar Türkçe karakteri tespit eder ve yerine ilgili, uygun karakteri gönderir.
    84-112 aralığı satırlar Flash makrosu için Türkçe karakteri tespit eder ve yerine ilgili, uygun karakteri gönderir.
    
    
    
    
    
