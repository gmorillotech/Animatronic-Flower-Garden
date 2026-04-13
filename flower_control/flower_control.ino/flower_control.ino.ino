#include <Servo.h>

const int PETAL_CLOSED_ANGLE = 10;
const int PETAL_OPEN_ANGLE   = 90;

const int LDR_PIN = A4;
const int LIGHT_THRESHOLD = 500; // we may tune this

Servo s1;
Servo s2;
Servo s3;
Servo s4;

int currentAngle = PETAL_CLOSED_ANGLE;

void moveAllServosSmoothly(int targetAngle) {
  int step = (targetAngle > currentAngle) ? 1 : -1;

  while (currentAngle != targetAngle) {
    currentAngle += step;

    s1.write(currentAngle);
    s2.write(currentAngle);
    s3.write(currentAngle);
    s4.write(currentAngle);

    delay(15);
  }
}

void setup() {
  Serial.begin(9600);

  s1.attach(3);
  s2.attach(5);
  s3.attach(6);
  s4.attach(9);

  s1.write(PETAL_CLOSED_ANGLE);
  s2.write(PETAL_CLOSED_ANGLE);
  s3.write(PETAL_CLOSED_ANGLE);
  s4.write(PETAL_CLOSED_ANGLE);

  delay(1000);
}

void loop() {
  int lightValue = analogRead(LDR_PIN);
  Serial.println(lightValue);

  if (lightValue > LIGHT_THRESHOLD) {
    moveAllServosSmoothly(PETAL_OPEN_ANGLE);
  } else {
    moveAllServosSmoothly(PETAL_CLOSED_ANGLE);
  }

  delay(200);
}