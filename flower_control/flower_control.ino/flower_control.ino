#include <Servo.h>

// SERVOS
Servo bloom1, bloom2, bloom3;
Servo sway1, sway2, sway3;

// PINS
const int BLOOM1_PIN = 3;
const int BLOOM2_PIN = 5;
const int BLOOM3_PIN = 6;

const int SWAY1_PIN = 9;
const int SWAY2_PIN = 10;
const int SWAY3_PIN = 11;

const int pirPin = 2;
const int ldrPin = A4;
const int micPin = A5;

// BLOOM CALIBRATION
const int OPEN_POS = 110;
const int NORMAL_CLOSE = 0;
const int RECOIL_CLOSE = 0;

// SWAY CALIBRATION
const int CENTER_SWAY = 0;
const int SWAY_MAX = 80;

// LIGHT THRESHOLDS
const int LIGHT_OPEN_THRESHOLD  = 800;
const int LIGHT_CLOSE_THRESHOLD = 650;

// MIC CALIBRATION
const int micThreshold = 300;
const unsigned long swayDuration = 1500;

// TIMING
const int recoilHoldTime = 2000;

// STATES
int currentBloomPos = OPEN_POS;
bool isRecoiling = false;
bool isBloomOpen = true;

// SWAY STATE
int currentSwayPos = CENTER_SWAY;
bool swayForward = true;
unsigned long lastSwayUpdate = 0;
const int swayUpdateInterval = 25;
unsigned long lastWindTrigger = 0;

// Bloom functions
void writeBloom(int pos) {
  bloom1.write(pos);
  bloom2.write(pos);
  bloom3.write(pos);
}

void moveBloomSmooth(int target, int stepDelay) {
  int step = (target > currentBloomPos) ? 1 : -1;

  while (currentBloomPos != target) {
    currentBloomPos += step;
    writeBloom(currentBloomPos);
    delay(stepDelay);
  }
}

void openBloom() {
  moveBloomSmooth(OPEN_POS, 8);
  isBloomOpen = true;
}

void closeBloom() {
  moveBloomSmooth(NORMAL_CLOSE, 8);
  isBloomOpen = false;
}

void recoil() {
  isRecoiling = true;

  // Snap
  moveBloomSmooth(RECOIL_CLOSE, 2);

  // Pause (recoil)
  sway1.write(CENTER_SWAY);
  sway2.write(CENTER_SWAY);
  sway3.write(CENTER_SWAY);
  currentSwayPos = CENTER_SWAY;
  swayForward = true;

  // Hold shut
  delay(recoilHoldTime);

  // Return based on current light state
  int light = analogRead(ldrPin);

  if (light >= LIGHT_OPEN_THRESHOLD) {
    openBloom();
  } else {
    closeBloom();
  }

  isRecoiling = false;
}

// Mic / Sway functions
int readMicAmplitude() {
  int maxVal = 0;
  int minVal = 1023;

  for (int i = 0; i < 40; i++) {
    int val = analogRead(micPin);
    if (val > maxVal) maxVal = val;
    if (val < minVal) minVal = val;
    delay(1);
  }

  return maxVal - minVal;
}

void writeSway(int pos) {
  sway1.write(pos);
  sway2.write(pos);
  sway3.write(pos);
}

void updateSway() {
  unsigned long now = millis();

  if (now - lastSwayUpdate < swayUpdateInterval) {
    return;
  }

  lastSwayUpdate = now;

  if (swayForward) {
    currentSwayPos++;
    if (currentSwayPos >= SWAY_MAX) {
      currentSwayPos = SWAY_MAX;
      swayForward = false;
    }
  } else {
    currentSwayPos--;
    if (currentSwayPos <= CENTER_SWAY) {
      currentSwayPos = CENTER_SWAY;
      swayForward = true;
    }
  }

  writeSway(currentSwayPos);
}

void centerSwayIfNeeded() {
  if (currentSwayPos != CENTER_SWAY) {
    if (currentSwayPos > CENTER_SWAY) {
      currentSwayPos--;
    } else if (currentSwayPos < CENTER_SWAY) {
      currentSwayPos++;
    }
    writeSway(currentSwayPos);
  }
}

// Setup
void setup() {
  Serial.begin(9600);

  bloom1.attach(BLOOM1_PIN);
  bloom2.attach(BLOOM2_PIN);
  bloom3.attach(BLOOM3_PIN);

  sway1.attach(SWAY1_PIN);
  sway2.attach(SWAY2_PIN);
  sway3.attach(SWAY3_PIN);

  pinMode(pirPin, INPUT);

  int light = analogRead(ldrPin);

  if (light >= LIGHT_OPEN_THRESHOLD) {
    writeBloom(OPEN_POS);
    currentBloomPos = OPEN_POS;
    isBloomOpen = true;
  } else {
    writeBloom(NORMAL_CLOSE);
    currentBloomPos = NORMAL_CLOSE;
    isBloomOpen = false;
  }

  writeSway(CENTER_SWAY);
  currentSwayPos = CENTER_SWAY;
}

// Loop
void loop() {
  int motion = digitalRead(pirPin);
  int light = analogRead(ldrPin);
  int sound = readMicAmplitude();
  unsigned long now = millis();

  Serial.print("Light: ");
  Serial.print(light);
  Serial.print(" | Motion: ");
  Serial.print(motion);
  Serial.print(" | Sound: ");
  Serial.print(sound);
  Serial.print(" | BloomOpen: ");
  Serial.print(isBloomOpen);
  Serial.print(" | Sway: ");
  Serial.println(currentSwayPos);

  // 1. Pir recoil -> Highest priority
  if (motion == HIGH && !isRecoiling) {
    recoil();
    return;
  }

  // 2. Bloom logic with hysteresis
  if (!isRecoiling) {
    if (!isBloomOpen && light >= LIGHT_OPEN_THRESHOLD) {
      openBloom();
    } 
    else if (isBloomOpen && light <= LIGHT_CLOSE_THRESHOLD) {
      closeBloom();
    }
  }

  // 3. Mic trigger sway burst
  if (sound > micThreshold) {
    lastWindTrigger = now;
  }

  // 4. Sway only while wind tigger is recent
  if (!isRecoiling && (now - lastWindTrigger < swayDuration)) {
    updateSway();
  } else if (!isRecoiling) {
    centerSwayIfNeeded();
  }

  delay(50);
}