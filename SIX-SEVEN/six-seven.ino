/*
  SIX-SEVENNNN by peeb.
*/

void setup() {
  //You can change it from int = 2 or int i = 3
  for (int i = 2; i <= 9; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(11, OUTPUT);  //For Buzzer
  pinMode(12, OUTPUT);  //For LED
}
/*
  digitalWrite(2, HIGH);//decimal point (you can left this out if you want tbh)
  digitalWrite(3, HIGH);//bottom right
  digitalWrite(4, HIGH);//bottom middle
  digitalWrite(5, HIGH);//bottom left
  digitalWrite(6, HIGH);//top right
  digitalWrite(7, HIGH);//top middle
  digitalWrite(8, HIGH);//middle
  digitalWrite(9, HIGH);//top left
*/

void loop() {
  six();
  delay(500);
  clearDisplay();
  delay(500);
  seven();
  delay(1000);
  clearDisplay();
}

void six() {
  //digitalWrite(2, HIGH); no decimal point
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  tone(11, 425, 500);
  blinkLED(500);
}

void seven() {
  //digitalWrite(2, HIGH); this as well
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(3, HIGH);
  blinkLED(125);
  delay(125);
  tone(11, 200, 500);
  blinkLED(500);
  tone(11, 325, 500);
}

void blinkLED(int duration) {
  digitalWrite(12, HIGH);
  delay(duration);
  digitalWrite(12, LOW);
}

void clearDisplay() {
  for (int i = 2; i <= 9; i++) {
    digitalWrite(i, LOW);
  }
  noTone(11);
}
