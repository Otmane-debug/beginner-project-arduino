#include <Keypad.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int ledPin = 13;

const int trigPin = 10;
const int echoPin = 11;

long duration;
int distance;


int i = 0;

char pswd[4] = "1234";

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad Keys = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);

  myservo.attach(12);  // attaches the servo on pin 11 to the servo object


  pinMode(ledPin, OUTPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}
  
void loop(){
char customKey = Keys.getKey();

  if(customKey == pswd[i]){
    Serial.println(customKey);
    i++;
    if(i==4){
      Serial.println("Correct");
      i=0;
      myservo.write(0);
      delay(5500);
      myservo.write(90);
    }
  }

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;


  if(distance < 100){
    digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }
  delay(150);
}
