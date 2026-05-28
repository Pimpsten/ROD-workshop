#include <krnl.h>
struct k_t *pTask1, *pTask2, *pTask3, *pTask4, *pTask5, *pTask6;  // task
int maxSpeed, currentSpeed, newSpeed;
float desiredSpeed;

const int pwmPin = 10;
const int dirPin = 12;

unsigned char taskStak1[STK],taskStak2[STK],taskStak3[STK],taskStak4[STK],taskStak5[STK],taskStak6[STK];

void setup() {
  Serial.begin(115200);¨

  pinMode(pwmPin, OUTPUT);
  pinMode(dirPin, OUTPUT);


  k_init(6, /*to be chosen*/, /*to be chosen*/);
  pTask1 = k_crt_task(CommIn, 10, taskStak1, 150);       // Seriel protocol
  pTask2 = k_crt_task(TaskCtrl, 10, taskStak2, 150);     // Processer nedenstående variabler
  pTask3 = k_crt_task(ReadMeter, 10, taskStak3, 150);    // Læser potentiometer
  pTask4 = k_crt_task(ReadSpeed, 10, taskStak4, 150);    // Læser current speed
  pTask5 = k_crt_task(ChangeSpeed, 10, taskStak5, 150);  // Ændrer hastighed
  pTask6 = k_crt_task(CommOut,10,taskStak6,150);         // Printer værdierne



  k_start();
  while(1);
}

void CommIn(){
  char buffer[5];
  byte bufferIndex = 0;
  while (1) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '<') 
        bufferIndex = 0;
      else 
        if (c == '>') {
        buffer[bufferIndex] = '\0';
        maxSpeed = atoi(buffer);
        if (maxSpeed > 100) maxSpeed = 100;
        if (maxSpeed < -100) maxSpeed = -100;
        Serial.println(maxSpeed);
      }
      else {
        buffer[bufferIndex++] = c;
      }
    }
  }
k_wait();
k_signal();
}

void TaskCtrl(){
int struct{         //denne struck skal printes i CommOut
  //information

}info;

k_wait();
k_signal();
}

void ReadMeter(){
 float desiredSpeed = (analogRead(A0)/511.5)-1;    // når potentiometeret er på 50%: maintain speed, alt under eller over giver relativ ændring i hastighed.
/*
AnalogRead læser værdien som uint_10t,
Dette divideres med 511.5 for at få værdien til at være mellem 0-2 (kommatal),
-1 for at få intervallet mellem [-1,1]
*/
k_wait(sem);
k_signal(sem);
}

void ReadSpeed(){


}

void ChangeSpeed(){

  newSpeed;

  while (1) {
    k_receive();  // sæt timeout til -1

    if (newSpeed == 0) {
      analogWrite(pwmPin, 0);
    } else if (newSpeed > 0) {
      digitalWrite(dirPin, HIGH);
    } else {
      digitalWrite(dirPin, LOW);
    }

    analogWrite(pwmPin, abs(newSpeed));
  }
}

}

void CommOut(){


}












void loop() {
}

