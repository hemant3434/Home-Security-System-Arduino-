

int inputPin = 8;               
int pirState = LOW;            
int val = 0;

int b_vol=25;
int buzzer=10;           
int ledPin = 13;

int state=0;

void setup() {
  pinMode(inputPin, INPUT);

  pinMode(ledPin, OUTPUT); 
  pinMode(buzzer,OUTPUT);

  Serial.begin(9600);
}

void loop() {
  
 if(Serial.available()>0){
    state=Serial.read();
  }

  if(state=='a'){
    b_vol=b_vol+5;
    Serial.println(b_vol);
    state=0;
  }
  else if(state=='b'){
    b_vol=b_vol-5;
    Serial.println(b_vol);
    state=0;
  }
  else if(state=='c'){
    b_vol=255;
    Serial.println(b_vol);
    state=0;
  }
  else if(state=='d'){
    b_vol=0;
    Serial.println(b_vol);
    state=0;
  }
  else if(state=='x'){
    analogWrite(buzzer,b_vol);
    delay(2000);
    Serial.println("DET");
    state=0;
  }

  
  val = digitalRead(inputPin);
  if (val == HIGH) {              
    if (pirState == LOW) {
      pirState = HIGH;
    }
    digitalWrite(ledPin, HIGH);
    analogWrite(buzzer,b_vol);
    Serial.write('y');
    delay(2000);
  } 
  
  else {
    if (pirState == HIGH){
      pirState = LOW;
    }
    digitalWrite(ledPin, LOW);
    analogWrite(buzzer,0); 
  }

}
