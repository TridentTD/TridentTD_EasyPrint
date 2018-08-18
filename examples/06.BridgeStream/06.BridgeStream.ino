#include <TridentTD_EasyPrint.h>
#include <SoftwareSerial.h>

SoftwareSerial myDevice(4,5);

void setup() {
  Serial.begin(115200); Serial.println();
  myDevice.begin(9600);
}

void loop() {
  // การ bridge ข้อมูลส่งข้ามอุปกรณ์
  // รับค่าทาง Serial Input แล้วแสดงออกทาง SoftwareSerial ได้ทันที
  Serial >> myDevice; 
}

