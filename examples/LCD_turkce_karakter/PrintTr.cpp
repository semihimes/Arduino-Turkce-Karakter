/*
 Print.cpp - Base class that provides print() and println()
 Copyright (c) 2008 David A. Mellis.  All right reserved.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
 Modified 23 November 2006 by David A. Mellis
 Modified 03 August 2015 by Chuck Todd

 PrintTr.cpp 08 haziran 2020 semih saçı
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Arduino.h"

#include "PrintTr.h"

// Public Methods //////////////////////////////////////////////////////////////

/* default implementation: may be overridden */

/* türkçe custom karakter mapleri
byte h0[8] =  {0, 14, 16, 14, 1, 30, 4, 0};     // Ş - ş
byte h1[8] = {0, 14, 17, 16, 17, 14, 4, 0};     // Ç - ç
byte h2[8] =  {0, 0, 12, 4, 4, 4, 14, 0};       // ı
byte h3[8] =  {4, 0, 14, 4, 4, 4, 14, 0};       // İ
byte h4[8] =  {14, 0, 14, 18, 14, 2, 28, 0};    // ğ
byte h5[8] =  {14, 0, 14, 16, 22, 18, 14, 0};   // Ğ
*/

size_t Print::write(const uint8_t *buffer, size_t size)
{
  size_t n = 0;
  int x;
  while (size--) 
  { 
// Türkçe karakterler için ilgili custom karakteri basar
    switch(*buffer)
        {
/*ş-Ş*/   case 0b11000101: write(byte(0));*buffer++;*buffer++; size--;n++;break;              
          case 0b11000011: *buffer++;
/*ç-Ç*/        if   ((*buffer==167)||(*buffer==135))
                    {write(byte(1));*buffer++; size--;n++;}
/*ü-Ü*/        else if((*buffer==188)||(*buffer==156))
                    {write(0b11110101);*buffer++; size--;n++;}
               break;
/*ı-İ*/   case 0b11000100: *buffer++;
                if     (*buffer==0b10110001){write(byte(2));size--;*buffer++;n++;}
                else if(*buffer==0b10110000){write(byte(3));size--;*buffer++;n++;}
                break;
          case 0b10010110:write(0b11101111);*buffer++;n++; break;
          case 0b10110110:write(0b11101111);*buffer++;n++; break;
/*ğ*/     case 0b10011111:write(byte(4));*buffer++;n++; break;
/*Ğ*/     case 0b10011110:write(byte(5));*buffer++;n++; break;
          default :if (write(*buffer)){ *buffer++;n++;} else break;
    }
  }
  return n;
}

size_t Print::print(const __FlashStringHelper *ifsh)
{
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  size_t n = 0;
  while (1) {
    unsigned char c = pgm_read_byte(p++);
   // print(c,BIN);print(" ");
    if (c == 0){break;}
    
    switch (c)
    {
      case 0b11000101: write(byte(0));p++;n++;break; //ş-Ş 
      case 0b11000011:c = pgm_read_byte(p++);
                      switch(c)
                      {
                        case 182:write(0b11101111);n++;break; //ö
                        case 150:write(0b11101111);n++;break; //Ö
                        case 188:write(0b11110101);n++;break; //ü
                        case 156:write(0b11110101);n++;break; //Ü
                        case 167:write(byte(1));n++;break;    //ç
                        case 135:write(byte(1));n++;break;    //Ç
                        default:print(c);n++;break;
                      }
                      break;
      case 0b11000100:c = pgm_read_byte(p++);
                      switch(c)
                      {
                        case 0b10110001:write(byte(2));n++;break;    // ı
                        case 0b10110000:write(byte(3));n++;break;    // İ
                        case 158: write(byte(5));n++;break;          // Ğ
                        case 159: write(byte(4));n++;break;          // ğ
                        default :print(c,BIN);break;
                      }
                      break;
      default: if (write(c)){ n++;} else break;
    }
   

   

  }
  return n;
}

size_t Print::print(const String &s)
{
  return write(s.c_str(), s.length());
}

size_t Print::print(const char str[])
{
  return write(str);
}

size_t Print::print(char c)
{

  return write(c);
}

size_t Print::print(unsigned char b, int base)
{
  return print((unsigned long) b, base);
}

size_t Print::print(int n, int base)
{
  return print((long) n, base);
}

size_t Print::print(unsigned int n, int base)
{
  return print((unsigned long) n, base);
}

size_t Print::print(long n, int base)
{
  if (base == 0) {
    return write(n);
  } else if (base == 10) {
    if (n < 0) {
      int t = print('-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  } else {
    return printNumber(n, base);
  }
}

size_t Print::print(unsigned long n, int base)
{
  if (base == 0) return write(n);
  else return printNumber(n, base);
}

size_t Print::print(double n, int digits)
{
  return printFloat(n, digits);
}

size_t Print::println(const __FlashStringHelper *ifsh)
{
  size_t n = print(ifsh);
  n += println();
  return n;
}

size_t Print::print(const Printable& x)
{
  return x.printTo(*this);
}

size_t Print::println(void)
{
  return write("\r\n");
}

size_t Print::println(const String &s)
{
  size_t n = print(s);
  n += println();
  return n;
}

size_t Print::println(const char c[])
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t Print::println(char c)
{

  size_t n = print(c);
  n += println();
  return n;
}

size_t Print::println(unsigned char b, int base)
{
  size_t n = print(b, base);
  n += println();
  return n;
}

size_t Print::println(int num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(unsigned int num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(unsigned long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(double num, int digits)
{
  size_t n = print(num, digits);
  n += println();
  return n;
}

size_t Print::println(const Printable& x)
{
  size_t n = print(x);
  n += println();
  return n;
}

// Private Methods /////////////////////////////////////////////////////////////

size_t Print::printNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    char c = n % base;
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  return write(str);
}

size_t Print::printFloat(double number, uint8_t digits) 
{ 
  size_t n = 0;
  
  if (isnan(number)) return print("nan");
  if (isinf(number)) return print("inf");
  if (number > 4294967040.0) return print ("ovf");  // constant determined empirically
  if (number <-4294967040.0) return print ("ovf");  // constant determined empirically
  
  // Handle negative numbers
  if (number < 0.0)
  {
     n += print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += print('.'); 
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
    n += print(toPrint);
    remainder -= toPrint; 
  } 
  
  return n;
}
