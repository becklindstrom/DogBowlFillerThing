const byte POWER_PIN = 7;
const byte SIGNAL_PIN = A5;
const byte LED_E = 3;
const byte LED_F = 2;


int value = 0; // variable to store the sensor value
const byte full = 120; 
const byte empty = 100;


void setup() {
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT); 
  digitalWrite(POWER_PIN, LOW);

  pinMode(LED_E, OUTPUT); 
  pinMode(LED_F, OUTPUT); 
}

void loop() {
  //turn on sensor and check value
  digitalWrite(POWER_PIN, HIGH);
  delay(10);
  value = analogRead(SIGNAL_PIN);
  digitalWrite(POWER_PIN, LOW);

  
  //check if value is higher than threshold - if yes turn on LED
  if (value < empty){ // IF LOW
    digitalWrite(LED_E,HIGH);
    digitalWrite(LED_F,LOW);
    Serial.println("LOW");
  } else if (value > full) {
    digitalWrite(LED_E,LOW);
    digitalWrite(LED_F,HIGH);
    Serial.println("FULL");
  } else {
    digitalWrite(LED_E,LOW);
    digitalWrite(LED_F,LOW);
    Serial.println(value);
  }

  delay(100);
}