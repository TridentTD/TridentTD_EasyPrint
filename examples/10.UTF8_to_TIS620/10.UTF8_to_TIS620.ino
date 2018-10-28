// ให้ save sketch file นี้ทีนึงก่อนใช้

#include <TridentTD_EasyPrint.h>

void setup() {
  Serial.begin(115200); Serial.println();

  String thai_utf8_str    = "สวัสดีครับ Hello World";
  String thai_tis620_str  = TridentTD::UTF8_to_TIS620(thai_utf8_str);
  
  Serial  << "Thai UTF8 String   : " << thai_utf8_str << endl
          << "Thai TIS620 String : " << thai_tis620_str << endl;

  for(int i =0; i < thai_tis620_str.length(); ++i)
    Serial << "[charAt " << i << "] code = " << (int)thai_tis620_str[i] << endl;

  Serial.println("--------------------------");

  // แปลงกลับคืน
  String thai_utf8_str2  = TridentTD::TIS620_to_UTF8(thai_tis620_str);
  Serial  << "Thai UTF8 String (reconvert) : " <<  thai_utf8_str2 << endl;

  Serial.println("--------------------------");

  // ดูว่าอักขระไทย นั้นมี รหัส UTF8 และ TIS620 คืออะไร

  Serial  << "UTF8   : " << TD_HEX(TridentTD::UTF8_code("ก"))   << endl
          << "TIS620 : " << TD_HEX(TridentTD::TIS620_code("ก")) << endl;

}


void loop() {

}

