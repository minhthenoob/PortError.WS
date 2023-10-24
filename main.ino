#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>
#include<SoftwareSerial.h>

#include <SPI.h>
#include <RFID.h>
#include <MFRC522.h>
#include <dht11.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 
SoftwareSerial(5, 6);

#define DHT11PIN 8
#define SS_PIN 10
#define RST_PIN 9
int red_led = 2;
int green_led = 3;
const int buttonPin = 2; 
int buttonState = 0;
RFID rfid(SS_PIN, RST_PIN);
dht11 DHT11;
Servo servo;

String rfidCard;
String temperature;
String humidity;
String aircomposition;

void setup() {
  servo.attach(7);
  Serial.begin(9600);
  espSerial.begin(9600);
  Serial.println("Hay dat the vao dau doc...");
  int chk = DHT11.read(DHT11PIN);
  SPI.begin();
  rfid.init();
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  digitalWrite(green_led, LOW);
  digitalWrite(red_led, LOW);
  pinMode(buttonPin, INPUT);
  lcd.init();                      // initialize the lcd
  lcd.clear();
  lcd.backlight();
  lcd.print("DOOR LOCKED");
}

void loop() {
  temperature = String(dht.readHumidity());
  humidity = String(dht.readTemperature());
  aircomposition = String("aircomp placeholder");

  espSerial.println(temperature);
  espSerial.println(humidity);
  espSerial.println(aircomposition);
  delay(1500);
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      delay(1000);
      if(rfidCard == "174 158 180 29"){
        digitalWrite(green_led, HIGH);
        digitalWrite(red_led, LOW);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ACCESS GRANTED");

        lcd.setCursor(0,1);
        lcd.print("Humidity(%): ");
        lcd.setCursor(13,1);
        lcd.print((float)DHT11.humidity, 2);

        lcd.setCursor(0,2);
        lcd.print("Temperature(C): ");
        lcd.setCursor(15,2);
        lcd.print((float)DHT11.temperature, 2);
        delay(1000);
        servo.write(90);
  }
      else{
        digitalWrite(green_led, LOW);
        digitalWrite(red_led, HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ACCESS DENIED");
        delay(1000);
        
       
    rfid.halt();
  }

  }
  }
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("DOOR LOCKED");
    servo.write(90);
  } 
  }