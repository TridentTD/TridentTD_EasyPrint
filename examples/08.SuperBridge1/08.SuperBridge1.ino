#include <TridentTD_EasyPrint.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

// DHT Sensor config
#define DHT_PIN     4
#define DHT_TYPE    DHT11
DHT  dht(DHT_PIN, DHT_TYPE);

// อุปกรณ์รอบข้างต่างๆ ต่อแบบ SoftwareSerial เช่น Bluetooth เป็นต้น
SoftwareSerial myDevice1(4,5);
SoftwareSerial myDevice2(10,11);

// Ethernet config
IPAddress ether_ip      = IPAddress(192, 168, 43, 177);
uint16_t  ether_port    = 8888;
byte      ether_mac[]   = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// UDP Server config
IPAddress udpserver_ip  = IPAddress(192, 168, 43, 1);
uint16_t  udpserver_port= 12345;

EthernetUDP Udp;

void setup(){
  Serial.begin(115200);
  myDevice1.begin(9600);
  myDevice2.begin(9600);

  dht.begin();
  Ethernet.begin(ether_mac, ether_ip);
  Udp.begin(ether_port);
}

uint32_t timer;

void loop(){
  if( millis() -timer >= 2000) { // อ่านค่า sensor และส่ง ในทุก 2 วินาที
    timer = millis();

    // อ่านค่า DHT Sensor
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    while ( isnan(h) || isnan(t) ) {
      h = dht.readHumidity();
      t = dht.readTemperature();
    }

    // เตรียมข้อมูล จาก sensor จัดแบบ String กำหนด format แบบ json
    char buf[50];
    sprintf(buf, "{\"humid\":%.2f,\"temperature\":%.2f}", h, t);
    String data_json = String(buf) + "\n";

    // ทำการส่ง String แสดงผลบน Serial Monitor 
    // พร้อมทั้งส่งไปตาม myDevice ต่างๆ จนครบ
    // และส่งไปยัง Udp Server ที่ทำ IoT ให้ด้วย
    Udp.beginPacket(udpserver_ip, udpserver_port);
    data_json >> Serial >> myDevice1 >> myDevice2 >> Udp;
    Udp.endPacket();
  }
}

