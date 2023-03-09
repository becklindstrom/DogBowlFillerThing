const byte buttonPin = 2;    
bool buttonState = LOW; 
int count = 0;

void setup(){
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  Serial.println("Begin");
}

void loop() {
  if(debounceButton(buttonState) == HIGH && buttonState == LOW){
    count++;
    buttonState = HIGH;
    Serial.print("count updated: ");
    Serial.println(count);
  } else if(debounceButton(buttonState) == LOW && buttonState == HIGH){
    buttonState = LOW;
    //Serial.println("if 2");
  }
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
