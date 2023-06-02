#include <Servo.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;

Servo myservo1;
Servo myservo2; 
Servo myservo3; 
Servo myservo4;

SoftwareSerial HC05(0,1); //rx tx
char c = '0';
int pos = 0;

void setup() {
  pinMode(10,OUTPUT);
  HC05.begin(9600);
  Serial.begin(9600);
  myservo1.attach(8);
  myservo2.attach(7);
  myservo3.attach(6);
  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
 // attaches the servo on pin 9 to the servo object
 Serial.print("Parasite power is: "); 
 if (sensors.isParasitePowerMode()) Serial.println("ON");
 else Serial.println("OFF");
 if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0"); 
 Serial.print("Device 0 Address: ");
 printAddress(insideThermometer);
 Serial.println();
 sensors.setResolution(insideThermometer, 9);
 Serial.print("Device 0 Resolution: ");
 Serial.print(sensors.getResolution(insideThermometer), DEC); 
 Serial.println();

}



void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if(tempC == DEVICE_DISCONNECTED_C) 
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
  HC05.println("temp=" + String(tempC));
  Serial.print("temp=" + String(tempC));
}



void loop() {
  char c = Serial.read();
  if (c == '2') {
     for (pos = 0; pos <= 50; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
       myservo3.write(pos);              // tell servo to go to position in variable 'pos'
       delay(15);                     // waits 15 ms for the servo to reach the position
       }
     for (pos = 50; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
       myservo3.write(pos);              // tell servo to go to position in variable 'pos'
       }
     c = '0';
     }
     if (c == '5') {
     for (pos = 0; pos <= 50; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
       myservo3.write(pos);              // tell servo to go to position in variable 'pos'
       delay(15);                     // waits 15 ms for the servo to reach the position
       }
     for (pos = 50; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
       myservo3.write(pos);              // tell servo to go to position in variable 'pos'
       }
     c = '0';
     }
  if (c == '3') {
     for (pos = 0; pos <= 50; pos += 1) { // goes from 0 degrees to 180 degrees
       // in steps of 1 degree
       myservo2.write(pos);              // tell servo to go to position in variable 'pos'
       delay(15);                      // waits 15 ms for the servo to reach the position
       }
     for (pos = 50; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
       myservo2.write(pos);              // tell servo to go to position in variable 'pos'
         
     c = '0';}
     }
  if (c == '1') {
      pos = 0;
     while (pos == 0){
       myservo1.write(0);
       delay(97);
       myservo1.write(90);
       delay(5000);
       myservo1.write(180);
       delay(110);
       myservo1.write(90);
       pos = 1;  
       c='0';}}
  if (c == '4'){ 
     Serial.print("Requesting temperatures...");
     sensors.requestTemperatures();
     Serial.println("DONE");
     printTemperature(insideThermometer);
      c = '0';}}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
