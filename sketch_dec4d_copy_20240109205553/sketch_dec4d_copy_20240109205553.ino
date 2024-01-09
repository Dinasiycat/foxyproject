#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 12); // RX, TX
byte message[] = {0xAA, 0x01, 0x00, 0xAB };
byte play_001[] = {0xAA, 0x07, 0x02, 0x00, 0x01,0xB4};
byte switch_to_TF[] = {0xAA, 0x01, 0x01, 0xB7};
Servo engine;
int spic = 2;
int r = 3;
int g = 4;
int b = 5;
int r1 = 7;
int g2 = 10;
int trig = 9;
int echo = 8;
int a = 0;

void setup() {
  // put your setup code here, to run once:
engine.attach(11);
pinMode(r, OUTPUT);
pinMode(spic, OUTPUT);
pinMode(g, OUTPUT);
pinMode(b, OUTPUT);
pinMode(r1, OUTPUT);
pinMode(g2, OUTPUT);
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
Serial.begin(9600);
mySerial.begin(9600);
mySerial.write(switch_to_TF, sizeof(switch_to_TF));
}

void loop() {
 int duration, cm; // назначаем переменную "cm" и "duration" для показаний датчика
  digitalWrite(trig, LOW); // изначально датчик не посылает сигнал
  delayMicroseconds(2);
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  cm = duration / 58; 

  Serial.print(cm); 
  Serial.println(" cm");

 
  if (cm <= 50 && a == 0){
    a = 1;
    engine.write(90);
    digitalWrite(r, HIGH);
    digitalWrite(r1, HIGH);
    tone(spic, 200);
    mySerial.write(play_001, sizeof(play_001));
  }
  delay(1000);
  engine.write(0);
}
