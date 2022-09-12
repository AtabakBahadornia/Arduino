#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DigitalIO.h>
#include <AFMotor.h>
#define CE_PIN   17
#define CSN_PIN 18
AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR12_8KHZ);
AF_DCMotor motor4(4, MOTOR12_8KHZ);

RF24 radio(17, 18); // CE, CSN
const byte address[6] = "00002";
boolean button_state = 0;
int val = 0;
void setup() {
pinMode(2, OUTPUT);
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();              //This sets the module as receiver
}
void loop()
{
if (radio.available())              //Looking for the data.
{
  radio.read(&val, sizeof(val));  //Sending the message to receiver 
  Serial.println(val);
    motor1.setSpeed(val);

digitalWrite(2, HIGH);
motor1.run(FORWARD);
delay(5);
}
}
