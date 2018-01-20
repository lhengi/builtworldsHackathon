#include <Time.h>
#include <TimeLib.h>
#include <LiquidCrystal.h>

#include <Servo.h>

LiquidCrystal lcd(12,11,5,4,3,2);
Servo myservo;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  
}


void loop()
{
  Serial.print("IR level  ");
  digitalWrite(7,HIGH);
  Serial.println(analogRead(A0));
  
  delay(500);
  Serial.print("IR level  ");
  digitalWrite(7,LOW);
  Serial.println(analogRead(A0));

  delay(500);
  
}

