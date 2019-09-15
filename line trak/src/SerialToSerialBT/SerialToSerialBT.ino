
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#include "BluetoothSerial.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


// the number of pin
#define forward  26
#define reverse 27
#define left    14
#define right   12

#define motorforward  1
#define motorreverse  2
#define motorleft     3
#define motorright    4

#define sensor7 36
#define sensor6 39
#define sensor5 34
#define sensor4 35
#define sensor3 32
#define sensor2 33
#define sensor1 25


//DEBUG
#define debug 1


// setting PWM properties
const int freq = 5000;
const int channelforward  = 0;
const int channelreverse  = 1;
const int channelleft     = 2;
const int channelright    = 3;
const int resolution  = 8;


#define Sensitive 2.5



//status WORK
#define ledPin 2


void DealyStart(int N)
{
  while(N>0)
  {
    OLED.clearDisplay();
    OLED.setTextColor(WHITE, BLACK);
    OLED.setCursor(50,20);
    OLED.setTextSize(5);
    OLED.println(N);
    OLED.display();
    delay(1000);
    N--;
  }
  OLED.clearDisplay();
  OLED.display();

}


BluetoothSerial SerialBT;


void setup() {

  // configure LED PWM functionalitites
  ledcSetup(channelforward, freq, resolution);
  ledcSetup(channelreverse, freq, resolution);
  ledcSetup(channelleft   , freq, resolution);
  ledcSetup(channelright  , freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(forward, channelforward);
  ledcAttachPin(reverse, channelreverse);
  ledcAttachPin(left, channelleft);
  ledcAttachPin(right, channelright);


  //setup
  ledcWrite(channelforward, 0);
  ledcWrite(channelreverse, 0);
  ledcWrite(channelleft   , 0);
  ledcWrite(channelright  , 0);


  //OLED
  if(debug == 1 || debug == 2)
  {
    Serial.begin(9600);
    OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  }
  DealyStart(5);


  Serial.begin(115200);
  SerialBT.begin("ESP32 Line follower"); //Bluetooth device name
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin, 0);
}


float inputsensor[7]  = {0,0,0,0,0,0,0};
byte  input[7]        = {0,0,0,0,0,0,0};
int   motor[4]        = {0,0,0,0};
byte  leftInput       = 0;
byte  rightInput      = 0;
byte  midInput        = 0;
byte  gottagofast     = 0;
char  Receive;




void loop() {
  if(SerialBT.available()){
    Receive = SerialBT.read();
    if (Receive == '0'){
      gottagofast = 0;
      SerialBT.print("0");
    }
    if (Receive == '1'){
      gottagofast = 1;
      SerialBT.print("1");
    }
    if (Receive == '2'){
      gottagofast = 2;
      SerialBT.print("2");
    }
    if (Receive == '3'){
      gottagofast = 3;
      SerialBT.print("3");
    }
    if (Receive == '4'){
      gottagofast = 4;
      SerialBT.print("4");
    }
    if (Receive == '5'){
      gottagofast = 5;
      SerialBT.print("5");
    }
    if (Receive == '6'){
      gottagofast = 6;
      SerialBT.print("6");
    }
    if (Receive == '7'){
      gottagofast = 7;
      SerialBT.print("7");
    }
    if (Receive == '8'){
      gottagofast = 8;
      SerialBT.print("8");
    }
    if (Receive == '9'){
      gottagofast = 9;
      SerialBT.print("9");
    }
  }
  //setzero
  inputsensor[1-1] = {0};
  inputsensor[2-1] = {0};
  inputsensor[3-1] = {0};
  inputsensor[4-1] = {0};
  inputsensor[5-1] = {0};
  inputsensor[6-1] = {0};
  inputsensor[7-1] = {0};

  input[1-1] = {0};
  input[2-1] = {0};
  input[3-1] = {0};
  input[4-1] = {0};
  input[5-1] = {0};
  input[6-1] = {0};
  input[7-1] = {0};

  //motor[1-1] = {0};
  //motor[2-1] = {0};
  //motor[3-1] = {0};
  //motor[4-1] = {0};

  leftInput  = 0;
  rightInput = 0;
  midInput   = 0;


  //inputsensor
  if(inputsensor[1-1] = analogRead(sensor1)*3.3/4096 <= Sensitive ){input[1-1] = 1;}
  if(inputsensor[2-1] = analogRead(sensor2)*3.3/4096 <= Sensitive ){input[2-1] = 1;}
  if(inputsensor[3-1] = analogRead(sensor3)*3.3/4096 <= Sensitive ){input[3-1] = 1;}
  if(inputsensor[4-1] = analogRead(sensor4)*3.3/4096 <= Sensitive ){input[4-1] = 1;}
  if(inputsensor[5-1] = analogRead(sensor5)*3.3/4096 <= Sensitive ){input[5-1] = 1;}
  if(inputsensor[6-1] = analogRead(sensor6)*3.3/4096 <= Sensitive ){input[6-1] = 1;}
  if(inputsensor[7-1] = analogRead(sensor7)*3.3/4096 <= Sensitive ){input[7-1] = 1;}


  //proces
  leftInput  = input[1-1]+input[2-1]+input[3-1];
  midInput   = input[4-1];
  rightInput = input[5-1]+input[6-1]+input[7-1];

  if(gottagofast == 9)
  {

  }


  //test
  if(gottagofast == 0)
  {
    motor[1-1]=0;
    motor[2-1]=0;
    motor[3-1]=0;
    motor[4-1]=0;
  }
  if(gottagofast ==1)
  {
    motor[1-1]=250;
    motor[2-1]=0;
  }
  if(gottagofast ==2)
  {
    motor[1-1]=0;
    motor[2-1]=250;
  }
  if(gottagofast ==3)
  {
    motor[3-1]=250;
    motor[4-1]=0;
  }
  if(gottagofast ==4)
  {
    motor[3-1]=0;
    motor[4-1]=250;
  }
  if(gottagofast ==5)
  {
    motor[3-1]=0;
    motor[4-1]=0;
  }

  //output
  ledcWrite(channelforward, motor[1-1]);
  ledcWrite(channelreverse, motor[2-1]);
  ledcWrite(channelleft   , motor[3-1]);
  ledcWrite(channelright  , motor[4-1]);


  //debug
  if(debug == 1)
  {
    OLED.clearDisplay();
    OLED.setTextColor(WHITE, BLACK);
    OLED.setCursor(0,0);
    OLED.setTextSize(1);
    OLED.printf("sensor7 = ");
    OLED.println(analogRead(sensor7)*3.3/4096);
    OLED.printf("sensor6 = ");
    OLED.println(analogRead(sensor6)*3.3/4096);
    OLED.printf("sensor5 = ");
    OLED.println(analogRead(sensor5)*3.3/4096);
    OLED.printf("sensor4 = ");
    OLED.println(analogRead(sensor4)*3.3/4096);
    OLED.printf("sensor3 = ");
    OLED.println(analogRead(sensor3)*3.3/4096);
    OLED.printf("sensor2 = ");
    OLED.println(analogRead(sensor2)*3.3/4096);
    OLED.printf("sensor1 = ");
    OLED.println(analogRead(sensor1)*3.3/4096);
    OLED.display();
    delay(200);
  }
  if(debug == 2)
  {
    OLED.clearDisplay();
    OLED.setTextColor(WHITE, BLACK);
    OLED.setCursor(0,0);
    OLED.setTextSize(1);
    OLED.printf("sensor7 = ");
    OLED.println(inputsensor[7-1]);
    OLED.printf("sensor6 = ");
    OLED.println(inputsensor[6-1]);
    OLED.printf("sensor5 = ");
    OLED.println(inputsensor[5-1]);
    OLED.printf("sensor4 = ");
    OLED.println(inputsensor[4-1]);
    OLED.printf("sensor3 = ");
    OLED.println(inputsensor[3-1]);
    OLED.printf("sensor2 = ");
    OLED.println(inputsensor[2-1]);
    OLED.printf("sensor1 = ");
    OLED.println(inputsensor[1-1]);
    OLED.display();
    delay(200);
  }
}
