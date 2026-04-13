#include <Servo.h>

const int PETAL_CLOSED_ANGLE = 10;
const int PETAL_OPEN_ANGLE   = 90;

const int LDR_PIN = A4;

// Two thresholds instead of one
const int LIGHT_OPEN_THRESHOLD  = 550;
const int LIGHT_CLOSE_THRESHOLD = 450;

Servo s1, s2, s3, s4;

int currentAngle = PETAL_CLOSED_ANGLE;
bool isOpen = false;

void moveAllServosSmoothly(int targetAngle) {
  int step = (targetAngle > currentAngle) ? 1 : -1;

  while (currentAngle != targetAngle) {
    currentAngle += step;

    s1.write(currentAngle);
    s2.write(currentAngle);
    s3.write(currentAngle);
    s4.write(currentAngle);

    delay(20);
  }
}

void setup() {
  Serial.begin(9600);

  s1.attach(3);
  s2.attach(5);
  s3.attach(6);
  s4.attach(9);

  moveAllServosSmoothly(PETAL_CLOSED_ANGLE);
}

void loop() {
  int lightValue = analogRead(LDR_PIN);
  Serial.println(lightValue);

  // Only open if clearly bright
  if (!isOpen && lightValue > LIGHT_OPEN_THRESHOLD) {
    moveAllServosSmoothly(PETAL_OPEN_ANGLE);
    isOpen = true;
  }

  // Only close if clearly dark
  if (isOpen && lightValue < LIGHT_CLOSE_THRESHOLD) {
    moveAllServosSmoothly(PETAL_CLOSED_ANGLE);
    isOpen = false;
  }

  delay(200);
}