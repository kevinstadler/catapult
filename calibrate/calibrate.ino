#include <Servo.h>

Servo servo;

int value = 700;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);

  servo.attach(2);
  servo.writeMicroseconds(value);
}

void loop() {
  int ms = Serial.parseInt();
  if (ms > 100 && ms < 3000) {  
    value = ms;
    servo.writeMicroseconds(value);
  }

}
