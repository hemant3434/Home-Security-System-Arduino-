
int inputPin = 8;               
int pirState = LOW;            
int val = 0;

int b_vol=25;
String mode="At Home";
int buzzer=10;           
int ledPin = 13;                


#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


#include <IRremote.h>
int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;

int state=0;

void setup() {
  lcd.begin(16, 2);
  
  pinMode(inputPin, INPUT);

  pinMode(ledPin, OUTPUT); 
  pinMode(buzzer,OUTPUT); 

  irrecv.enableIRIn();
 
  Serial.begin(9600);
}

void loop(){
  //  Up 3249147378 3772778233
  //  Down 3249163698 3772810873
  //  Left 3249196338 3772819033
  //  Right 3249180018 3772794553
  // 98D3:61:F5C5BA Slave Address  
  if(Serial.available()>0){
    state=Serial.read();
  }
 
  lcd.setCursor(0,0);
  lcd.print("Volume: ");
  lcd.setCursor(8,0);
  lcd.print(b_vol, DEC);
  lcd.setCursor(0,1);
  lcd.print("Mode: "+mode);
  
  if(state=='y'){
    analogWrite(buzzer,b_vol);
    delay(2000);
    Serial.println("DET");
    state=0;
  }
  
  if (irrecv.decode(&results)) {
    if(results.value==3249147378){
      if(b_vol>=0 && b_vol<=250){
        b_vol=b_vol+5;
        lcd.clear();
        Serial.write('a');
      }
    }
    else if(results.value==3249163698){
      if(b_vol>=5 && b_vol<=255){
        b_vol=b_vol-5;
        lcd.clear();
        Serial.write('b');
      }
    }
    else if(results.value==3249196338){
      lcd.clear();
      mode="Away";
      b_vol=255;
      Serial.write('c');
    }
    else if(results.value==3249180018){
      lcd.clear();
      mode="At Home";
      b_vol=0;
      Serial.write('d');
    }
    irrecv.resume();
  }
  
  val = digitalRead(inputPin);  

  if (val == HIGH) {              
    if (pirState == LOW) {
      pirState = HIGH;
    }
    digitalWrite(ledPin, HIGH);
    analogWrite(buzzer,b_vol);
    Serial.write('x');
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
