//pin nummers toekennen
const int sensorPin = 2;
const int potPin = A0;
const int pwmPin = 3;

// Variabelen declareren
int sensState;
int sensPrevState;
int sensStep;
int sensPrevStep;
int sensStepDif;
int rpm;
int pwm;

void setup() {
  // serial verbinding starten
  Serial.begin(9600);
  // pinmodes instellen
  pinMode(sensorPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  // potentiometer uitlezen en schalen voor gebruik als pwm signaal
  pwm = map(analogRead(potPin), 1, 1023, 1, 255);
  // digitaal signaal van de infra rood sensor uitlezen
  sensState = digitalRead(sensorPin);

  //motor aansturen met pwm signaal
  analogWrite(pwmPin, pwm);

  //kijken of de sensorwaarde omhoog is gegaan t.o.v. de vorige meting
  if ((sensState == 1) && (sensPrevState == 0)) {
    //tijdstip van puls opslaan en aftrekken van vorig tijdstip zodat je een tijd tussen de pulsen krijgt in ms
    sensPrevStep = sensStep;
    sensStep = millis();
    sensStepDif = sensStep - sensPrevStep;
    // tijd tussen pulsen omrekenen naar toeren per minuut
    rpm = round((1000 / sensStepDif) * 60);
    // data naar de serial monitor/plotter schijven
    Serial.print(pwm);
    Serial.print(" , ");
    Serial.println(rpm);
  }
  // vorige status van IR sensor overschijven met huidige status
  sensPrevState = sensState;
}
