#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <TridentTD_EasyPrint.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.init(); 
  lcd.backlight();
  
  // กำหนดตำแหน่ง บรรทัด 0 ตำแหน่ง 0 แล้วแสดง Hello World
  lcd.setCursor(0, 0);
  lcd << "Hello World";   // สำหรับ lcd ไม่ต้องใช้ endl 

  // กำหนดตำแหน่ง บรรทัด 1 ตำแหน่ง 0 แล้วแสดง  วันที่ และ เวลา โดยไม่ต้องห่วงเติม 0   
  lcd.setCursor(0, 1);
  lcd <<  TD_DATE(4,8,2561) << " " << TD_TIME(9,7,15) ; // --->  04/08/2561 09:07:15

}

void loop() {
	
}

