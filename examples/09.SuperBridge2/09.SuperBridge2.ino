#include <TridentTD_EasyPrint.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

SoftwareSerial R232Serial(4,5);  //กำหนดขา rx,tx

// Ethernet config
IPAddress ether_ip      = IPAddress(192, 168, 43, 177); // กำหนด IP ของ Ethernet
uint16_t  ether_port    = 8888;                         // กำหนด Port ของ Ethernet
byte      ether_mac[]   = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //กำหนด mac address

// UDP Server config
IPAddress udpserver_ip  = IPAddress(192, 168, 43, 1); // กำหนด IP ขอว UDP Server ที่ต้องการ
uint16_t  udpserver_port= 12345;                      // กำหนด Port ของ UDP Server

EthernetUDP Udp;

void setup(){
  Serial.begin(115200);                 // เริ่มต้นใช้งาน Serial Monitor
  R232Serial.begin(9600);               // เริ่มต้นใช้งาน R232Serial
  Ethernet.begin(ether_mac, ether_ip);  // เริ่มต้นเชื่อมต่อ Ethernet
  Udp.begin(ether_port);                // เริ่มต้นใช้งาน UDP Client ของ Ethernet
}


void loop(){
  if( R232Serial.available()) {
    Udp.beginPacket(udpserver_ip, udpserver_port);  // เชื่อมต่อไปยัง UDP Server ที่ต้องการ
    // หากมีข้อมูลมาจาก R232Serial จะทำการส่งต่อไปแสดงที่ Serial Monitor พร้อมทั้งส่งขึ้นไปยัง Udp Server ให้ด้วย
    R232Serial >> Serial >> Udp;
    Udp.endPacket();
  }
}

