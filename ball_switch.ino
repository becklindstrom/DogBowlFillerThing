
//Water Level Indicator Variables
int level;
int LED_pin = ;   //Digital


//Filling Variables
int bowlFill = True;
int tankFill = True;
int button_Pin = ;
volatile unsigned long fillDuration = 0;


//Ultrasonic Variables
int trig_Pin = ;  //Digital
int echo_Pin = ;  //Digital
long sonicDuration;
int sonicDistance;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_Pin,OUTPUT);
  pinMode(trig_Pin,OUTPUT);
  pinMode(echo_Pin,INPUT);
  pinMode(button_Pin,INPUT);
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  level = analogRead(A0);
  Serial.println(level);
  
  if(level < 500){
    digitalWrite(LED_Pin, HIGH); //Turn on LED to indicate low Bowl Water Level
    bowlFill = False;

    while(bowlFill == 'False' && tankFill == 'True'){
      if(fillDuration < 1000){
        //Run Motor
      }
      elseif(fillDuration >= 1000){
        tankFill = False;
      }
    }
  }

  if(button_Pin == HIGH){
    tankFill = False;    
  }

}

//Code Source: https://howtomechatronics.com/projects/arduino-radar-project/
int calculateDistance(){ 
  
  digitalWrite(trig_Pin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig_Pin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig_Pin, LOW);
  sonic_Duration = pulseIn(echo_Pin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  sonicDistance= sonicDuration*0.034/2;
  return sonicDistance;

}

