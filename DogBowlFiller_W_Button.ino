//DEFINE  CONSTANTS
const byte POWER_PIN = 7;
const byte SIGNAL_PIN = A5;
const byte LED_E = 3;
const byte LED_F = 2;



// water level constants
int value = 0; 
const byte full = 120; 
const byte empty = 100;

// fill time constants
int filltime = 7000; //THIS IS THE USER DEFINED CONST FOR MOTOR RUN TIME [ms]
int fillstarttime = 0;
int currenttime = 0;

//pump relay pins
const byte RELAY_PIN = 10;

//ultrasonic pins
int trig_Pin = 11;  //Digital
int echo_Pin = 12;  //Digital
long sonicDuration;
int sonicDistance;

//button pin
const byte buttonPin = 4;
bool buttonState = LOW;

void setup() {
  //general
  Serial.begin(9600);

  //water pump
  pinMode(RELAY_PIN, OUTPUT); 
  digitalWrite(RELAY_PIN, LOW);  

  //water level
  pinMode(POWER_PIN, OUTPUT); 
  digitalWrite(POWER_PIN, HIGH);
  pinMode(LED_E, OUTPUT); 
  pinMode(LED_F, OUTPUT); 

  //ultrasonic
  pinMode(trig_Pin,OUTPUT);
  pinMode(echo_Pin,INPUT);
  
  //button
  pinMode(buttonPin, INPUT);
}

void loop() {
  //turn on water level sensor, check value and turn off
  digitalWrite(POWER_PIN, HIGH);
  //delay(10);
  value = analogRead(SIGNAL_PIN);
  //digitalWrite(POWER_PIN, LOW);

  //ultrasonic interupt
  sonicDistance = calculateDistance();
  Serial.println(sonicDistance);
  //water pump interrupt
 
  //check if value is higher than threshold - if yes turn on LED
  if(sonicDistance > 20){         //IF DOG NOT CLOSE
    if (value < empty){ // IF LOW
      Serial.println("empty BEGIN");
      digitalWrite(LED_E,HIGH);
      digitalWrite(LED_F,LOW);
      fillstarttime = millis();
      while ((currenttime < (filltime + fillstarttime)) && (value < empty)){
        Serial.println("empty IN WHILE LOOP");
        digitalWrite(RELAY_PIN,HIGH);

        value = analogRead(SIGNAL_PIN);
        currenttime = millis();     
      }
      Serial.println("empty AFTER WHILE LOOP");
      if(value <= full){
        while (!(debounceButton(buttonState) == HIGH && buttonState == LOW)){
          buttonState = HIGH;
        } 
      }
      Serial.println("empty END");

    } else if (value > full) {
      digitalWrite(LED_E,LOW);
      digitalWrite(RELAY_PIN,LOW);
      digitalWrite(LED_F,HIGH);
      //Serial.println("FULL");
      
    } else {
      digitalWrite(LED_E,LOW);
      digitalWrite(LED_F,LOW);
      //Serial.println(value);
    }
    
  } else {  // IF DOG CLOSE
    digitalWrite(RELAY_PIN,LOW);
  }
}
    


//USER FUNCTIONS

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

bool debounceButton(bool state){
  //Serial.println("in function");
  bool stateNow = digitalRead(buttonPin);
  if(state != stateNow)
  {
    delay(10);
    stateNow = digitalRead(buttonPin);
  }
  return stateNow;
}
