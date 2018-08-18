#include <TridentTD_EasyPrint.h>
#include <SoftwareSerial.h>

SoftwareSerial myDevice1(4,5);
SoftwareSerial myDevice2(10,11);

void setup(){
	Serial.begin(115200);
	myDevice1.begin(9600);
	myDevice2.begin(9600);
}

void loop(){
  // ให้เปิด Serial Monitor แล้ว พิมพ์ค่าเข้า ทาง Serial Input  
  // ค่าจะถูก bridge ส่งต่อไปยัง ทั้ง อุปกรณ์ myDevice1 และ myDevice2 ให้ อัตโนมัติ
  // พร้อมทั้งแสดงบน Serial Monitor ให้ด้วย

	Serial >> myDevice1 >> myDevice2 >> Serial;
}

