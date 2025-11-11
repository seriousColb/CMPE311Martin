int ledState1 = LOW;
int ledState2 = LOW;

unsigned long previousTimeLed1 = millis();
long timeIntervalLed1 = 1000;
unsigned long previousTimeLed2 = millis();
long timeIntervalLed2 = 1000;
int userPin = 0;
unsigned long taskTime = millis();

void ledTask1(){
  if(millis() - previousTimeLed1 > timeIntervalLed1){
    previousTimeLed1 = millis();

    if(ledState1 == HIGH){
      ledState1 = LOW;

    }
    else{
      ledState1 = HIGH;
    }
    digitalWrite(2, ledState1);

  }

}

void ledTask2(){
  if(millis() - previousTimeLed2 > timeIntervalLed2){
    previousTimeLed2 = millis();

    if(ledState2 == HIGH){
      ledState2 = LOW;

    }
    else{
      ledState2 = HIGH;
    }
    digitalWrite(3, ledState2);

  }

}

void takeInput(){
  
  if(Serial.available()){
    
    if(userPin == 1){  
      timeIntervalLed1 = Serial.parseInt();
      userPin = 0;
      while(Serial.available())
        Serial.read();
      Serial.println("Select an LED(1 or 2):");
    }
    else if(userPin == 2){
      timeIntervalLed2 = Serial.parseInt();
      userPin = 0;
      while(Serial.available())
        Serial.read();
      Serial.println("Select an LED(1 or 2):");
    }
    else{
      userPin = Serial.parseInt();
      Serial.println("Input a blink rate(ms):");
      while(Serial.available()){
        Serial.read();
      }
    }
    
  }
}

void (*taskPntr[3])() = {ledTask1, ledTask2, takeInput};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(2, OUTPUT);
  pinMode(3,OUTPUT);
  Serial.println("Select an LED(1 or 2):");
  

}


void loop() {
  // put your main code here, to run repeatedly:
  while(1){
    int i = 0;
    for(i =0; i < 3; i++){
      taskPntr[i]();
    }
  }

}
