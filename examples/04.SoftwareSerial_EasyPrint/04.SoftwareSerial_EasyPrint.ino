#include <SoftwareSerial.h>

#define DEVICE_RX				5					// pin rx
#define DEVICE_TX				4					// pin tx

SoftwareSerial  myDevice(DEVICE_RX,DEVICE_TX);

void setup() {
	Serial.begin(115200); 
	myDevice.begin(9600);
}

int  counter=0;
void loop() {
	myDevice << "[DATA]" << counter++ << [END] << endl;
	delay(1000);
}

