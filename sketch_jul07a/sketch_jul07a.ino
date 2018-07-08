#include <MFRC522.h>
#include <SPI.h>
#include <Servo.h>
#define SAD 10
//#define RST 5
#define RST 9
#define buzzer 2

int ii=0;
MFRC522 nfc(SAD, RST);
Servo myservo;  // create servo object to control a servo

 byte status;
  byte data[MAX_LEN];
  byte serial[5];
  int i, j, pos;
 


void setup() {
  pinMode(buzzer,OUTPUT);
  SPI.begin();
  // Read a fast as possible. There is a limit for how long we are
  // allowed to read from the tags.
  Serial.begin(115200);

  Serial.println("Looking for MFRC522.");
  nfc.begin();
  myservo.attach(A0);  // attaches the servo on pin 9 to the servo object

  // Get the firmware version of the RFID chip
  byte version = nfc.getFirmwareVersion();
  if (! version) {
    Serial.print("Didn't find MFRC522 board.");
    while(1); //halt
  }

  Serial.print("Found chip MFRC522 ");
  Serial.print("Firmware ver. 0x");
  Serial.print(version, HEX);
  Serial.println(".");
}


void loop() 
{
  // Send a general request out into the aether. If there is a tag in
  // the area it will respond and the status will be MI_OK.
  status = nfc.requestTag(MF1_REQIDL, data);
  String content= "";

  if (status == MI_OK) {
    Serial.println("Tag detected.");
    Serial.print("Type: ");
    Serial.print(String(data[0], HEX));
    Serial.print(", ");
    Serial.println(String(data[1], HEX));

    // calculate the anti-collision value for the currently detected
    // tag and write the serial into the data array.
    status = nfc.antiCollision(data);
    memcpy(serial, data, 5);

    Serial.println("The serial number of the tag is:");
    for (i = 0; i < 3; i++) {
      Serial.print(serial[i], HEX);
      Serial.print(", ");
    }
    Serial.println(serial[3], HEX);
}
// store the HEX serial number in String form for comparing
content.concat(String(serial[0],HEX));
content.concat(String(serial[1],HEX));
content.concat(String(serial[2],HEX));
content.concat(String(serial[3],HEX));
delay(1000);
// 1cd682cb is known tag (card)
Serial.println(content);
if (content.equals("1cd682cb")||content.equals("d16680cb"))
  
{
  
      Serial.println("Authorized access");
    Serial.println();
    digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
    doormove();   // move the door 
    ii=1;
   }
  // content.replace("1cd682cb","");


}


void doormove()
{
                   
myservo.write(1);      
    delay(5000);               
}


