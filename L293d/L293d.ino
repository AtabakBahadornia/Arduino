#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AFMotor.h>
AF_DCMotor motor(2, MOTOR12_64KHZ);
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "000002";
int val=0;
void setup() {
  Serial.begin(9600);
  pinMode(11,INPUT);
  radio.begin();
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();              //This sets the module as receiver
  motor.setSpeed(100);
 motor.run(RELEASE);
}


void loop(){
  if(radio.available());
    radio.read(&val,sizeof(val));
  Serial.println(val);
  motor.run(FORWARD);
}
