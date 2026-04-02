int sequence[100];
int currentLevel = 0;

const int LED_PINS[] = { 5, 6, 7 };
const int BTN_PINS[] = { 2, 3, 4 };
const int BUZZER = 11;

const int TONES[] = { 300, 400, 500 };

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    pinMode(BTN_PINS[i], INPUT_PULLUP);
  }
  pinMode(BUZZER, OUTPUT);

  randomSeed(analogRead(0));
}

void playColor(int index) {
  digitalWrite(LED_PINS[index], HIGH);
  tone(BUZZER, TONES[index]);
  delay(300 - (currentLevel * 20));
  digitalWrite(LED_PINS[index], LOW);
  noTone(BUZZER);
  delay(100);
}

void playSequence() {
  for (int i = 0; i <= currentLevel; i++) {
    playColor(sequence[i]);
    delay(200);
  }
}

bool waitForPlayer() {
  for (int i = 0; i <= currentLevel; i++) {
    bool pressed = false;
    int btnIndex = -1;

    while (!pressed) {
      for (int b = 0; b < 3; b++) {
        if (digitalRead(BTN_PINS[b]) == LOW) {
          btnIndex = b;
          pressed = true;
          playColor(btnIndex);

          while (digitalRead(BTN_PINS[b]) == LOW) { delay(10); }
        }
      }
    }

    if (btnIndex != sequence[i]) {
      return false;
    }
  }
  return true;
}

void loop() {
  sequence[currentLevel] = random(0, 3);

  playSequence();

  bool passed = waitForPlayer();

  if (passed) {
    currentLevel++;
    delay(1000);
  } else {
    tone(BUZZER, 150);
    delay(400);
    tone(BUZZER, 100);
    delay(600);
    noTone(BUZZER);

    for (int x = 0; x < 3; x++) {
      for (int i = 0; i < 3; i++) digitalWrite(LED_PINS[i], HIGH);
      delay(200);
      for (int i = 0; i < 3; i++) digitalWrite(LED_PINS[i], LOW);
      delay(200);
    }

    currentLevel = 0;
    delay(2000);
  }
}
