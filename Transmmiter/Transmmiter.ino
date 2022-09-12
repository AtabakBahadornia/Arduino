#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DigitalIO.h>
#define CE_PIN   17
#define CSN_PIN 18
RF24 radio(17, 18); // CE, CSN      
int val=0;
const byte address[6] = "00002";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
void setup() {
radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.stopListening();          //This sets the module as transmitter
Serial.begin(9600);
}
void loop()
{
  val=analogRead(A5);
  val=map(val,0,1023,0,255);
  Serial.println(val);
radio.write(&val, sizeof(val));  //Sending the message to receiver 
delay(10);
}
