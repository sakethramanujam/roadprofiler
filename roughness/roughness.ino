#include<SD.h>
#include<SPI.h>
#include<stdlib.h>

//const int MOSI = 11;
//const int CS = 10;
//const int MISO = 12;
//const int CLOCk = 13;
const int ultraSonicT = 1;
const int ultraSonicE = 2;

const int chipSelect = 4;

File file;

long dist = 0, tim = 0;
int limit;


void setup() {
  Serial.begin(9600);
  pinMode(chipSelect,OUTPUT);
  pinMode(ultraSonicT, OUTPUT);
  pinMode(ultraSonicE, INPUT);
  if(!SD.begin(chipSelect)){
  Serial.println("Card Failure..");
  return;
  }
 }

void loop() {

  String dataString = "";
  
  digitalWrite(ultraSonicT,LOW);
  delayMicroseconds(2);
  digitalWrite(ultraSonicT,HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraSonicT,LOW);

  tim = pulseIn(ultraSonicE,HIGH);//measures the delay time in echoed signal bouncing off the surface
  dist = ((tim*0.034)/2);//distance in millimeters
  dataString+=String(dist);
  //Serial.println(dist);
  //Serial.print(" cms");

  dataString+=",";

  File dataFile = SD.open("1346.csv",FILE_WRITE);
  if(dataFile){
   dataFile.println(dataString);
   dataFile.close();
   Serial.println(dataString);
   }
   else{
    Serial.println("\n Couldnot Open Log File!");
   }
  }
  

