/*
TridentTD_EasyPrint.h - Arduino library for supporting the << streaming operator
Copyright (c) 2015-2018 TridentTD.  All rights reserved.

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
*/

/* 
   18-08-2018 TridentTD
    reedit and added TD_DATE 
*/

#ifndef ARDUINO_STREAMING
#define ARDUINO_STREAMING

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <IPAddress.h>

#define STREAMING_LIBRARY_VERSION 5.1


#ifndef cout
#define cout Serial
#endif


// Generic template
template<class T> 
inline Print &operator <<(Print &stream, T arg) 
{ stream.print(arg); return stream; }

struct TD_BASED 
{ 
  long val; 
  int base;
  TD_BASED(long v, int b): val(v), base(b) 
  {}
};

#if ARDUINO >= 100

struct TD_BYTE_CODE
{
	byte val;
	TD_BYTE_CODE(byte v) : val(v)
	{}
};
#define TD_BYTE(a)    TD_BYTE_CODE(a)

inline Print &operator <<(Print &obj, const TD_BYTE_CODE &arg)
{ obj.write(arg.val); return obj; } 

#else

#define TD_BYTE(a)    TD_BASED(a, BYTE)

#endif

#define TD_HEX(a)     TD_BASED(a, HEX)
#define TD_DEC(a)     TD_BASED(a, DEC)
#define TD_OCT(a)     TD_BASED(a, OCT)
#define TD_BIN(a)     TD_BASED(a, BIN)

// Specialization for class TD_BASED
//  usage : Serial << TD_HEX(a);

inline Print &operator <<(Print &obj, const TD_BASED &arg)
{ obj.print(arg.val, arg.base); return obj; } 

#if ARDUINO >= 18

// usage : Serial << TD_FLOAT(gps_latitude, 6); // 6 digits of precision
struct TD_FLOAT
{
  float val;
  int digits;
  TD_FLOAT(double v, int d): val(v), digits(d)
  {}
};

inline Print &operator <<(Print &obj, const TD_FLOAT &arg)
{ obj.print(arg.val, arg.digits); return obj; }
#endif

// Specialization for enum _EndLineCode
// Thanks to Arduino forum user Paul V. who suggested this
// clever technique to allow for expressions like
//   Serial << "Hello!" << endl;

enum _EndLineCode { endl };

inline Print &operator <<(Print &obj, _EndLineCode arg) 
{ obj.println(); return obj; }


// TD_Fill struct
// usage : Serial << TD_FILL('=', 20) << endl;   ---->  ====================   

struct TD_FILL
{
char ch;
int len;
TD_FILL(char c, int l): ch(c), len(l)
{}
};

inline Print &operator <<(Print &obj, const TD_FILL &arg)
{ for (int i=0; i< arg.len; i++) obj.write(arg.ch); return obj; }

// TD_TIME struct
//  usage :  Serial << TD_TIME(1,12,3) << endl;     ---->  01:12:03
struct TD_TIME
{
uint8_t hour;
uint8_t minu;
uint8_t sec;
TD_TIME(uint8_t h, uint8_t m, uint8_t s): hour(h), minu(m), sec(s)
{}
};

inline Print &operator <<(Print &obj, const TD_TIME &arg)
{ obj.print(((arg.hour<10)?"0":"")); obj.print(int(arg.hour));
obj.print(((arg.minu<10)?":0":":")); obj.print(int(arg.minu));
obj.print(((arg.sec<10)?":0":":")); obj.print(int(arg.sec));
return obj; } 

// TD_DATE struct
// usage :  Serial << TD_DATE(2,5,18) << endl;     ---->  02/05/18

struct TD_DATE
{
uint8_t date;
uint8_t month;
uint16_t year;
TD_DATE(uint8_t d, uint8_t m, uint16_t y): date(d), month(m), year(y)
{}
};

inline Print &operator <<(Print &obj, const TD_DATE &arg)
{ obj.print(((arg.date<10)?"0":"")); obj.print(int(arg.date));
obj.print(((arg.month<10)?"/0":"/")); obj.print(int(arg.month));
obj.print(((arg.year<10)?"/0":"/")); obj.print(int(arg.year));
return obj; } 

inline String operator >>(String str, Print &obj)
{ obj.print(str); return str;}

inline int operator >>(int arg , Print &obj)
{ obj.print(arg); return arg;}

inline TD_FLOAT operator >>(const TD_FLOAT arg, Print &obj)
{ obj.print(arg.val, arg.digits);  return arg; }

inline IPAddress operator >>(IPAddress arg, Print &obj)
{ obj.print(arg);  return arg; }

inline String operator >> (Stream &obj1, Stream &obj2)
{ 
  String _buf="";
  if( obj1.available() ){
    while(obj1.available()) {
      char c = (char)obj1.read(); 
      obj2 << c; _buf +=c;
    }
  }
  return _buf;
}

namespace TridentTD {
  String UTF8_to_TIS620(String utf8_str, bool debug = false);  // แปลง UTF8 String ไปเป็น  TIS620 String
  String TIS620_to_UTF8(String tis620_str, bool debug = false); // แปลง TIS620 String ไปเป็น UTF8 String
  uint32_t  UTF8_code(String c);              // แปลง char ตัวไทย ว่ามีค่า UTF8 อะไร
  uint8_t   TIS620_code(String c);            // แปลง char ตัวไทย ว่ามีค่า TIS620 อะไร
  String    UTF8_String(uint32_t code);       // แปลง รหัส UTF8 ว่าคอ char อะไร
  String    TIS620_String(uint8_t code);      // แปลง รัหส TIS620 ว่าคือ char อะไร
}



#endif
