
#define enA 9
#define in1 6
#define in2 7
#define button 4

#include<stdlib.h>
#include<string.h>

  volatile byte rpmcount;
  char strData[10];
  
void setup() {
  Serial.begin(1200);
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(button, INPUT);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  attachInterrupt(0, rpm_fun, FALLING);
}

void rpm_fun()
 {
      rpmcount++;
 }

void loop() {
    rpmcount=0;
    digitalWrite(in2, LOW);
    char but_stat=Serial.read();
    if (but_stat=='a'){  
      digitalWrite(in2, HIGH);
      analogWrite(enA,85);
      delay(10000);
      detachInterrupt(0);
      itoa(rpmcount,strData,10);
      strcat(strData,"\n");
      Serial.write(strData);
}
    else if (but_stat=='b'){
      digitalWrite(in2, HIGH);
      analogWrite(enA,170);
      delay(10000);
      detachInterrupt(0);
      itoa(rpmcount,strData,10);
      strcat(strData,"\n");
      Serial.write(strData);
}
    else if (but_stat=='c'){
      digitalWrite(in2, HIGH);
      analogWrite(enA,255);
      delay(10000);
      detachInterrupt(0);
      itoa(rpmcount,strData,10);
      strcat(strData,"\n");
      Serial.write(strData);
    }
    
    attachInterrupt(0, rpm_fun, FALLING);
     


}
