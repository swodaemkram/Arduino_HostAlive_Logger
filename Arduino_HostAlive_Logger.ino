/*
  Host Alive data Recorder 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 by Mark Meadows
 
 */
#include <SD.h>
#include <SPI.h>         
#include <Ethernet.h>
#include <ICMPPing.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // max address for ethernet shield
byte ip[] = {192,168,2,177}; // ip address for ethernet shield
byte pingAddr[] = {184,45,91,177}; // ip address to ping
const int chipSelect = 4;

SOCKET pingSocket = 0;

char buffer [256];

void setup() 
{
  // start Ethernet
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop()
{
  ICMPPing ping(pingSocket);
  ping(4, pingAddr, buffer);
  Serial.println(buffer);
  File dataFile = SD.open("pinglog.txt", FILE_WRITE);
  dataFile.println(buffer);
  dataFile.close();
  delay(10000);
}
