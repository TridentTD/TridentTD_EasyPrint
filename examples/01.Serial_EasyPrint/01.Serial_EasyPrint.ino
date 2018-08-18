
// ตัวอย่างนี้ให้ save file ต่างหากออกมาก่อน จึงจะแสดงภาษาไทยได้ถูกต้อง

#include <TridentTD_EasyPrint.h>

void setup() {
  Serial.begin(115200);

  Serial << endl;   // ขึ้นบรรทัดใหม่
  Serial << "ไม่อยากพิมพ์ print(...)" << "ทำอย่างไรดี?" << endl;
  Serial << "พิมพ์ข้อความแบบต่อเนื่องได้เลย " << "วันนี้ วันที่ " << 18 << " สิงหาคม พ.ศ." << 2561 <<endl;
  Serial << "แสดงวันที่ เวลา ไม่ต้องห่วง เติม 0 ให้เอง : " << TD_DATE(4,8,2561) << " " << TD_TIME(9,7,15) <<endl;
  Serial << String("ทดสอบ แสดงจำนวนจริงกำหนดหลักทศนิยมได้ : ") << " : " << TD_FLOAT(12.4334343,5) << endl;
  Serial << TD_FILL('=',20) <<endl;
  Serial << "แสดงเลขฐาน 2  : " << TD_BIN(234) <<endl;   // binary based number
  Serial << "แสดงเลขฐาน 8  : " << TD_OCT(234) <<endl;   // oct based number
  Serial << "แสดงเลขฐาน 16 : " << TD_HEX(234) <<endl;   // hex besed number 

}

void loop() {
}
