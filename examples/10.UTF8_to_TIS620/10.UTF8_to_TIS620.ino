// ให้ save sketch file นี้ทีนึงก่อนใช้

#include <TridentTD_EasyPrint.h>

void setup() {
  Serial.begin(115200); Serial.println();

  String thai_utf8_str    = "สวัสดีครับ";
  String thai_tis620_str  = TridentTD::UTF8_to_TIS620(thai_utf8_str);
  
  Serial.println( thai_utf8_str );
  Serial.println( thai_tis620_str);
}

void loop() {

}

