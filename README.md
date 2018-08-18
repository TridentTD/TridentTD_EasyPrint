# TridentTD_EasyPrint

การแสดงข้อความ print แบบง่ายๆ ออกทาง Serial, LCD, File, Server, Client ฯลฯ  
ในสไตล์ตามแบบของ C++ ด้วย โอเปอเรเตอร์ <<  
ช่วยลดการ ต้องพิมพ์ print(...)  หรือ println(...) ลงได้  

## วิธีการใช้

1. ให้เพิ่ม ไลบรารี่ TridentTD_EasyPrint.h ก่อนการใช้งาน  
```
#include <TridentTD_EasyPrint.h>
```
  
2. ต้องการ print ส่งข้อความไปที่ Serial หรือ SoftwareSerial  
ตลอดจน LCD, File, Server, Client ฯลฯ  
ได้โดยตรงเลย ด้วย <<  และหากต้องการขึ้นบรรทัดใหม่ ด้วยคำสั่ง endl ตามแบบของ C++  

```
// ตัวอย่าง print ออกไปที่ Serial พร้อมขึ้นบรรทัดใหม่ด้วย endl
Serial << "Hello World! << endl;  

// ตัวอย่าง print วันที่ และ เวลา ออกไปที่ตัวแปร lcd โดยไม่ต้องห่วงเรื่องการเติม 0
lcd << TD_DATE(4,5,2561) << " " << TD_TIME(12,5,3);   //-->  04/05/2561 12:05:03

// ตัวอย่าง print เลขฐานต่างๆ ไปยังตัวแปร file แทนการใช้ file.print(....)
file << "Data1" << ":" << "Data2" << ":" << "Data3" << endl;

// ตัวอย่าง print เลขฐานต่างๆ ออกไปที่ Serial
Serial << TD_BIN(234) <<endl;   // แสดงเลข 234 ในเลขฐาน 2
Serial << TD_OCT(234) <<endl;   // แสดงเลข 234 ในเลขฐาน 8
Serial << TD_DEC(234) <<endl;   // แสดงเลข 234 ในเลขฐาน 10
Serial << TD_HEX(234) <<endl;   // แสดงเลข 234 ในเลขฐาน 16

```
  
3. สามารถทำการ Bridge ข้อมูล ข้ามกันได้เลยด้วย >>  
```
Serial  >> myDevice;    // ดูในตัวอย่างที่ 6, ตัวอย่างที่ 7
```
   
4. สามารถทำการ Super Bridge คือ การส่งข้อมูล String ที่เตรียมไว้  
แจกไปจนครบทุกอุปกรณ์ได้ด้วยการใช้ >> ซ้อนกันเรื่อยๆ ได้เลย  

```
String data_json = "{\"h\": 55.12, \"t\":23.53}\n";
data_json >> Serial  >> myDevice1 >> myDevice2 >> Udp;    // ดูในตัวอย่างที่ 8
```

__หมายเหตุ__  
สำหรับ lcd ไม่ต้องใช้ endl ในการขึ้นบรรทัดใหม่  
  
  
### TridentTD
18 สิงหาคม 2561  
