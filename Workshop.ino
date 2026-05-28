#include <krnl.h>
struct k_t *pTask1, *pTask2, *pTask3, *pTask4, *pTask5, *pTask6;  // task
int maxSpeed, desiredSpeed, currentSpeed, newSpeed;

unsigned char taskStak[STK];

void setup() {
  Serial.begin(115200);
  k_init(5, 5, 1);
  pTask1 = k_crt_task(CommIn, 10, taskStak, 150);       // Seriel protocol
  pTask2 = k_crt_task(TaskCtrl, 10, taskStak, 150);     // Processer nedenstående variabler
  pTask3 = k_crt_task(ReadMeter, 10, taskStak, 150);    // Læser potentiometer
  pTask4 = k_crt_task(ReadSpeed, 10, taskStak, 150);    // Læser current speed
  pTask5 = k_crt_task(ChangeSpeed, 10, taskStak, 150);  // Ændrer hastighed
  pTask6 = k_crt_task(CommOut,10,taskStak,150);



  k_start();
  while(1);
}

void CommIn(){

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

k_wait();
k_signal();
}

void ReadSpeed(){


}

void ChangeSpeed(){


}

void CommOut(){


}












void loop() {
}
