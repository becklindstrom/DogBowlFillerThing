const byte POWER_PIN = 7;
const byte SIGNAL_PIN = A5;
const byte LED_E = 3;
const byte LED_F = 2;

// water level constants
int value = 0; 
const byte full = 145; 
const byte empty = 130;

//pump relay pins
const byte RELAY_PIN = 10;

//ultrasonic pins
int trig_Pin = 11;
int echo_Pin = 12;
long sonicDuration;
int sonicDistance;


void setup() {

  //general
  Serial.begin(9600);

  //water pump
  pinMode(RELAY_PIN, OUTPUT); 
  digitalWrite(RELAY_PIN, LOW);  

  //water level
  pinMode(POWER_PIN, OUTPUT); 
  digitalWrite(POWER_PIN, LOW);
  pinMode(LED_E, OUTPUT); 
  pinMode(LED_F, OUTPUT); 

  //ultrasonic
  pinMode(trig_Pin,OUTPUT);
  pinMode(echo_Pin,INPUT);
}

void loop() {
  //turn on sensor and check value
  digitalWrite(POWER_PIN, HIGH);
  delay(10);
  value = analogRead(SIGNAL_PIN);
  digitalWrite(POWER_PIN, LOW);
  
  //Create csv output for graphs
  Serial.print(millis());
  Serial.print(", ");
  Serial.print(value);
  Serial.print(", ");
  Serial.println(sonicDistance);

  //ultrasonic interupt
  sonicDistance = calculateDistance();
 
  //check if value is higher than threshold - if yes turn on LED
  if(sonicDistance > 20){
    
    if (value < empty){ // IF LOW
      digitalWrite(LED_E,HIGH);
      digitalWrite(LED_F,LOW);
      digitalWrite(RELAY_PIN,HIGH);
      
    } else if (value > full) {
      digitalWrite(LED_E,LOW);
      digitalWrite(RELAY_PIN,LOW);
      digitalWrite(LED_F,HIGH);

    } else {
      digitalWrite(LED_E,LOW);
      digitalWrite(LED_F,LOW);
    }

    delay(100);
    
  }else{
  digitalWrite(RELAY_PIN,LOW);
}
}

//Function to convert ultrasonic duration to distance
int calculateDistance(){ 
  
  digitalWrite(trig_Pin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig_Pin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig_Pin, LOW);
  sonicDuration = pulseIn(echo_Pin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  sonicDistance = sonicDuration*0.034/2;
  return sonicDistance;


}
