#include <SoftwareSerial.h>

int led = 13;
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() { 
 pinMode(led, OUTPUT);
 Serial.begin(115200);
 mySerial.begin(115200);
 setBt();
}

void loop() {
 //while(1);//stop execution
 while (Serial.available() > 0) {
   int testiJeesus = Serial.parseInt(); 
   if (Serial.read() == '\n') {
     Serial.println(testiJeesus);
   }
 }
}

void setBt(){
 digitalWrite(led, HIGH);//sanity check
 command("AT",2);// response: OK
 command("AT+VERSION",12);// response: OKlinvorV1.5
 command("AT+NAMEArduino",9);//response: OKsetname
 command("AT+BAUD8",8);//response: OK115200
  
}

void command(const char* cmd, int num_bytes_response) {
 delay(1000);
 mySerial.print(cmd);
 delay(1500);
 for (int i=0;i<num_bytes_response;i++)
 Serial.write(mySerial.read());
}
