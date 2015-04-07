#include <CajuStreamShell.h>

#define LED 13

CajuStreamShell ss(&Serial);

void test(){
  digitalWrite(LED, LOW);
}

void test2(){
  digitalWrite(LED, HIGH);
}

void setup(){
  Serial.begin(9600);
  
  ss.addCommand("test", test);
  ss.addCommand("test2", test2);
}

void loop(){
  
}


void serialEvent() {
  ss.tick();
}