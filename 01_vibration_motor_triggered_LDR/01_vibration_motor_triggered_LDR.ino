#include "runningaverage.h"
#define LDR_READ_EVERY_MS 200 //5 times per second > to get average cuantities????????????

//RunningAverage ravg( (1000/LDR_READ_EVERY_MS)*10 );

#define LEFT_EYE A0
#define RIGHT_EYE A1
//#define Light_intensity 1000 // we can define later the light intensity

double readEye(int eye) { //def. of function (number is double) ??????????
  double reading = .0;
  // read 4 times to get a stable reading
  for(int i = 0; i < 4; i++) {
    reading += analogRead(eye);
    delay(5);
  }

  return (reading / 4.0); //???????????????????
}
void shake() {
  digitalWrite (5, HIGH); // if the light is turned on, it activates the vibrating module
//  delay (1000); 
//  digitalWrite (5, LOW); 
//  delay (1000);
}

void setup() {
  // define the input and output
  Serial.begin (9600);
  pinMode (5, OUTPUT); 
  pinMode (LEFT_EYE, INPUT); 
  pinMode (RIGHT_EYE, INPUT); 
}

void loop() {
  
  double lReading = readEye ( LEFT_EYE ); //why this xReading ?????????????????
  double rReading = readEye( RIGHT_EYE );
  
  Serial.print(lReading);
  Serial.print(",");
  Serial.println(rReading);
  //delay(50);
  
  if (lReading > 400 || rReading > 400) { // when the room is really dark it should be around 400. Maximun is 1000.
    shake();
  }
    else if (lReading < 400 || rReading < 400) { // if there is no light stops vibrating
      digitalWrite (5, LOW); //why digitalWrite here and up we wrote shake ??? if we wouldn't have define shake in "void.setup" we would have need to write digitalWrite (5,HIGH)???????
    }
  
   
  
}
