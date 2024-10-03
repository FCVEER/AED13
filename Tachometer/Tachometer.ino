const int sensorPin = 2;
const int potPin = A0;
const int pwmPin = 3;
const int inputMotor1 = 8;
const int inputMotor2 = 7;

int sensState;
int sensPrevState;
int sensStep;
int sensPrevStep;
int sensStepDif;
int rpm;


int pwm;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  pwm = map(analogRead(potPin), 1, 1023, 1, 255);
  sensState = digitalRead(sensorPin);

  digitalWrite(inputMotor1, LOW);
  digitalWrite(inputMotor2, HIGH);
  analogWrite(pwmPin, pwm);

  if ((sensState == 1) && (sensPrevState == 0)) {
    sensPrevStep = sensStep;
    sensStep = millis();
    sensStepDif = sensStep - sensPrevStep;
    rpm = round((1000 / sensStepDif) * 60);
    Serial.print(pwm);
    Serial.print(" , ");
    Serial.println(rpm);
  }
  sensPrevState = sensState;
}
