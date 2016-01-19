#define sensorCnt 8
#include <Servo.h>
#include <math.h>

Servo srv1;
boolean lineState[sensorCnt];
float lineSensorMean[sensorCnt];
//max about 45degree
int weight[sensorCnt]={-35,-25,-15,-5,5,15,25,35};
int nextCmd = 90;
const int increase = 10;
int currentCmd = 90;
const float kd = 1;


void setup() {
   srv1.attach(9.
   );
   srv1.write(90);
   pinMode(A0, INPUT);
   pinMode(A1, INPUT);
   pinMode(A2, INPUT);
   pinMode(A3, INPUT);
   pinMode(A4, INPUT);
   pinMode(A5, INPUT);
   pinMode(A6, INPUT);
   pinMode(A7, INPUT);
   Serial.begin(9600);
   for(int i=0; i<sensorCnt; ++i)lineSensorMean[i] = 0;
}

void loop() {

  //read sensor
   for(unsigned short i=0; i<sensorCnt; i++) {
      lineState[i] = (analogRead(i)<=550) ? 1 : 0;
   }
  int total = 0;
  int count = 0;
  for(int i=0; i<sensorCnt; ++i) {
    total = total + lineState[i]*weight[i];
    count = count + lineState[i];
  }
  if (count != 0)
  {
    nextCmd = 90 + total/count;
  }

  if (nextCmd > currentCmd + increase)
  {
    currentCmd = currentCmd + increase;
  }
  if ((nextCmd <= currentCmd + increase) && (nextCmd >= currentCmd - increase))
  {
    currentCmd = nextCmd;
  }
  if (nextCmd < currentCmd - increase)
  {
    currentCmd = currentCmd - increase;
  }
   srv1.write(currentCmd);
   
   Serial.print("\tDesired angle: ");
   Serial.print(currentCmd);
   
   Serial.println();
   
}






