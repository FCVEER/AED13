//Variabelen initieren
int PWM;
int Toeren;

int Signaal;
int VorigSignaal;
int Punt1;
int Punt2;
int Verschil;

void setup() {
  Serial.begin(9600);
  //inputs en outputs instellen
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  //signaal van sensor uitlezen
  Signaal = digitalRead(2);
  // kijken of het signaal hoog is terwijl het vorige signaal laag was
  if (Signaal == HIGH && VorigSignaal == LOW) {
    //tijdstippen van de twee meetpunten van elkaar aftrekken om een verschil te krijgen
    Punt2 = Punt1;
    Punt1 = millis();
    Verschil = Punt1 - Punt2;
    //omrekenen naar Tpm
    Toeren = round((1000 / Verschil) * 60);
    Serial.println(Toeren + " , " + PWM);
  }
  //vorig signaal vervangen door huidig signaal
  VorigSignaal = Signaal;

  //potmeter uitlezen en schalen om als PWM gebruikt te worden om de motor aan te sturen
  PWM = map(analogRead(A0), 1, 1023, 1, 255);
  analogWrite(5, PWM);
}
