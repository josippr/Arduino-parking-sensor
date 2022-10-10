//Arduino parking sensor with I2C LCD and Distance Meter

#include <LiquidCrystal_I2C.h>

//initialize LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

const int trigPin = 12;
const int echoPin = 11;
const int piezoPin = 9;

long duration;
long distance;

uint8_t obstacle[] = {
  0b00100,
  0b00111,
  0b00111,
  0b00100,
  0b00100,
  0b00111,
  0b00111,
  0b00100
};

byte car1[] = {
  B00000,
  B00001,
  B00110,
  B01000,
  B01111,
  B00100,
  B00000,
  B00000
};

byte car2[] = {
  B00000,
  B11100,
  B00100,
  B00010,
  B11110,
  B01000,
  B00000,
  B00000
};

byte line[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B00000,
  B00000
};

void setup(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.createChar(0, obstacle);
  lcd.home();
  lcd.createChar(1, line);
  lcd.home();
  lcd.createChar(2, car2);
  lcd.home();
  lcd.createChar(3, car1);
  lcd.home();
  lcd.setCursor(15,1);
  lcd.write((byte)0);
}


void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if(distance > 332 || distance < 2){
    Serial.println("Udaljenost je prevelika! ");
    lcd.setCursor(0,0);
    lcd.print("Udaljenost je prevelika!");
  }
  else{
    Serial.print("\n Udaljenost je: ");
    Serial.print(distance);
    Serial.print(" cm");
    lcd.setCursor(0,0);
    lcd.print("Udaljenost je ");
    lcd.print(distance);
    
  }
  delay(50);
  if(distance < 50){  //0.5 m = 50 cm
    noTone(piezoPin);
    
  }
  if(distance > 10 && distance < 50){
    if(distance > 40 && distance <50){
      tone(piezoPin, 500, 500);
      delay(1000);
      lcd.setCursor(14,1);
      lcd.write((byte)1);
      lcd.setCursor(13,1);
      lcd.write((byte)1);
      lcd.setCursor(12,1);
      lcd.write((byte)1);
      lcd.setCursor(11,1);
      lcd.write((byte)1);
      lcd.setCursor(10,1);
      lcd.write((byte)2);
      lcd.setCursor(9,1);
      lcd.write((byte)3);
    }
    if(distance > 30 && distance <40){
      tone(piezoPin, 500, 400);
      delay(700);
      lcd.setCursor(14,1);
      lcd.write((byte)1);
      lcd.setCursor(13,1);
      lcd.write((byte)1);
      lcd.setCursor(12,1);
      lcd.write((byte)1);
      lcd.setCursor(11,1);
      lcd.write((byte)2);
      lcd.setCursor(10,1);
      lcd.write((byte)3);
      lcd.setCursor(9,1);
      lcd.print(" ");
    }
    if(distance > 20 && distance <30){
      tone(piezoPin, 500, 300);
      delay(400);
      lcd.setCursor(14,1);
      lcd.write((byte)1);
      lcd.setCursor(13,1);
      lcd.write((byte)1);
      lcd.setCursor(12,1);
      lcd.write((byte)2);
      lcd.setCursor(11,1);
      lcd.write((byte)3);
      lcd.setCursor(10,1);
      lcd.print(" ");
    }
    if(distance > 10 && distance <20){
      tone(piezoPin, 500, 200);
      delay(100);
      lcd.setCursor(14,1);
      lcd.write((byte)1);
      lcd.setCursor(13,1);
      lcd.write((byte)2);
      lcd.setCursor(12,1);
      lcd.write((byte)3);
      lcd.setCursor(11,1);
      lcd.print(" ");
    }
  }
  while(distance < 10){
    tone(piezoPin, 500);
    lcd.setCursor(0,1);
    lcd.print("OPREZ!");
    lcd.setCursor(14,1);
    lcd.write((byte)2);
    lcd.setCursor(13,1);
    lcd.write((byte)3);
    lcd.setCursor(12,1);
    lcd.print(" ");
  }
  delay(50);
}

  void beep(unsigned char distance){
    tone(piezoPin, 500);
  }

  void beep_init(){
    tone(piezoPin, 500, 300);
    delay(300);
    tone(piezoPin, 500, 300);
    delay(300);
    tone(piezoPin, 500, 300);
    delay(300);
  }
