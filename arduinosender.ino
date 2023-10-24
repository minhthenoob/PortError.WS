#include <SoftwareSerial.h>

SoftwareSerial espSerial(5, 6);
String str;

void setup(){
Serial.begin(9600);
espSerial.begin(9600);
delay(2000);
}
void loop()
{
str =String("data drom arduino");
espSerial.println(str);
delay(1000);
}