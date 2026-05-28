#include <krnl.h>
#define STK 150
struct speedData {
  float rmp, time;
};

struct allInfo {
  float time, currentSpeed, desiredSpeed, maxSpeed;
};

speedData speedBuffer[2];
allInfo infoBuffer[2];
int maxSpeedBuffer[2];


struct k_msg_t *Queue_Ctrl, *Queue_ReadSpd, *Queue_Cmot;          // message queues
struct k_t *pTask1, *pTask2, *pTask3, *pTask4, *pTask5, *pTask6;  // task
struct k_t *Timed_sem1, *CommIn_sem2, *ReadMtr_sem3;              // semaphores

unsigned char taskStak1[STK], taskStak2[STK], taskStak3[STK], taskStak4[STK], taskStak5[STK], taskStak6[STK];

void setup() {
  Serial.begin(115200);
  k_init(6, 3, 3);
  pTask1 = k_crt_task(CommIn, 10, taskStak1, 150);       // Seriel protocol
  pTask2 = k_crt_task(TaskCtrl, 10, taskStak2, 150);     // Processer nedenstående variabler
  pTask3 = k_crt_task(ReadMeter, 10, taskStak3, 150);    // Læser potentiometer
  pTask4 = k_crt_task(ReadSpeed, 10, taskStak4, 150);    // Læser current speed
  pTask5 = k_crt_task(ChangeSpeed, 10, taskStak5, 150);  // Ændrer hastighed
  pTask6 = k_crt_task(CommOut, 10, taskStak6, 150);

  Queue_Ctrl = k_crt_send_Q(2, sizeof(int), maxSpeedBuffer);
  Queue_ReadSpd = k_crt_send_Q(2, sizeof(speedData), speedBuffer);
  Queue_Cmot = k_crt_send_Q(2, sizeof(allInfo), InfoBuffer);

  Timed_Sem1 = k_crt_sem(0, 1);
  CommIn_sem2 = k_crt_sem(0, 1);
  ReadMtr_sem3 = k_crt_sem(0, 1);

  k_start();
  while (1)
    ;
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
        allInfo.maxSpeed = atoi(buffer);
        if (allInfo.maxSpeed > 100) allInfo.maxSpeed = 100;
        if (allInfo.maxSpeed < -100) allInfo.maxSpeed = -100;
        Serial.println(allInfo.maxSpeed);
      }
      else {
        buffer[bufferIndex++] = c;
      }
    }
  }
k_wait(CommIn_sem2,0);
k_signal(CommIn_sem2;
}

void TaskCtrl(){
int struct{         //denne struck skal printes i CommOut
  //information

}info;

k_wait();
k_signal();
}

void ReadMeter(){
  while(1)
  allInfo.desiredSpeed = (analogRead(A0)/511.5)-1;    // når potentiometeret er på 50%: maintain speed, alt under eller over giver relativ ændring i hastighed.
/*
AnalogRead læser værdien som uint_10t,
Dette divideres med 511.5 for at få værdien til at være mellem 0-2 (kommatal),
-1 for at få intervallet mellem [-1,1]
*/
k_wait(ReadMtr_sem3,0);
k_signal(ReadMtr_sem3);
}

void ReadSpeed(){


}

void ChangeSpeed(){


}

void CommOut(){
  while(1){
    




    
  }
}












void loop() {
}
