#include <TimerOne.h> // TimeOne라이브러리 사용
//-------타이머 인터럽트를 위한 타이머 카운트------------
volatile unsigned long time_count = 0;
volatile unsigned long Sound_count = 0;

int rec = 5;                                    // rec를 5번 핀으로 
int playe = 4;                                  // playe를 4번 핀으로
int command;                                    // 시리얼 모니터의 명령을 받아들이는 변수

int Soil = A0;

void setup() 
{
  Serial.begin(9600);                          // 시리얼 통신, 속도는 9600
  pinMode (rec, INPUT);                         // rec를 입력으로
  pinMode (playe,OUTPUT);                       // playe를 출력으로
  
  Timer1.initialize(250000); //1000000μs = 1s, 1000us = 0.001s, 1000us = 1ms
  Timer1.attachInterrupt(timerIsr);
}
 
void loop() {
  int soil = analogRead(Soil);
  
  if(Sound_count == 1){
    Sound_C(soil);
    Sound_count = 0;
  }
}

void timerIsr(){
  time_count += 1;
  Sound_count += 1;
}

void Sound_C(int soil){
  int command = Serial.read();

  if (command == 'r'){
    Serial.println("Recording 10 sec.....");
    digitalWrite(rec,HIGH);                 // 녹음 중....
    delay(10000);                           // 10초 동안 녹음 중 
    digitalWrite(rec,LOW);                  // 녹음 종료 
    Serial.println("Recording finished");
  }
  
  if (soil >= 800){                             // 녹음된 소리 재생
    Serial.println("play the record!!");
    digitalWrite(playe,HIGH);               // 재생 중.
    delay(10);
    digitalWrite(playe,LOW);                // 녹음된 소리 재생이 끝나면 low로 
  } else {
    digitalWrite(playe,LOW);
  }
  Serial.println(soil);
}
