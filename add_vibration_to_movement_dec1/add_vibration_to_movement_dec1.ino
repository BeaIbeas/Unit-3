#include "runningaverage.h"

#define CHB_DIR 13 
#define CHB_PWM 11 
#define CHB_BRK 8
#define CHB_SNS A1

#define CHA_DIR 12
#define CHA_PWM 3
#define CHA_BRK 9
#define CHA_SNS A0

#define LGT_SNS_RGT A2
#define LGT_SNS_LFT A3

// mapping ranges light sensors (thresholds)
#define LGT_THR_LFT_MIN 180 // lowerbund of the LEFT eye
#define LGT_THR_LFT_MAX 988
#define LGT_THR_RGT_MIN 240 // right
#define LGT_THR_RGT_MAX 990

#define LDR_READ_EVERY_MS 200

#define VIBRATION_PIN 5
int motorB_speed = 0;

RunningAverage avgL( (1000/LDR_READ_EVERY_MS)*10 );
RunningAverage avgR( (1000/LDR_READ_EVERY_MS)*10 );

int leftEye, rightEye;

void init_motor() {
  pinMode(CHA_DIR, OUTPUT);
  pinMode(CHA_BRK, OUTPUT);
  digitalWrite(CHA_DIR, LOW);
  digitalWrite(CHA_BRK, LOW);
  pinMode(CHB_DIR, OUTPUT);
  pinMode(CHB_BRK, OUTPUT);
  digitalWrite(CHB_DIR, LOW);
  digitalWrite(CHB_BRK, LOW);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  init_motor();
  
  pinMode(VIBRATION_PIN, OUTPUT);

  // introduce calibration
  // CALIBRATE DARKNESS VALUES

  // WAIT

  // CALIBRATE LIGHT VALUES
}

void debug_text() {
  Serial.print("left sensor: ");
  Serial.println(leftEye);
  Serial.print("right sensor: ");
  Serial.println(rightEye);
}

void debug_graph() {
  Serial.print(leftEye);
  Serial.print(",");
  Serial.print(rightEye);
  Serial.print(",");
  Serial.print( avgL.getAverage() );
  Serial.print(",");
  Serial.println( avgR.getAverage() );
}

void loop() {
  //int lightRight = analogRead(LGT_SNS_RGT)/4; 
  //int lightLeft = analogRead(LGT_SNS_LFT)/4;

  // first we read the value of the left eye, and we add that value to the average calculator
  rightEye = readEye(LGT_SNS_RGT); 
  avgR.addValue( rightEye );
  
  leftEye = readEye(LGT_SNS_LFT);
  avgL.addValue( leftEye );
  
  debug_graph();
    
  // put your main code here, to run repeatedly:
  analogWrite(CHB_PWM, mappedMotorValue(leftEye, true)); //conect sensor value to direction
  analogWrite(CHA_PWM, mappedMotorValue(rightEye, false));
  if (rightEye > 400 || leftEye > 400) { // when the room is really dark it should be around 400. Maximun is 1000.
    shake(true);
  }
  else if (rightEye < 400 || leftEye < 400) { // if there is no light stops vibrating
    shake(false);
  }
 
}

double readEye(int eye) { //def. of function (number is double) ??????????
  double reading = .0;
  // read 4 times to get a stable reading
  for(int i = 0; i < 4; i++) {
    reading += analogRead(eye);
    delay(5);
  }

  return (reading / 4.0); //???????????????????
}

void shake(bool _shakeOn) {
  digitalWrite (VIBRATION_PIN, _shakeOn); // if the light is turned on, it activates the vibrating module
//  delay (1000); 
//  digitalWrite (5, LOW); 
//  delay (1000);
}

void turn(int howmuch) {}
void forward(int steps) {}

int mappedMotorValue(int reading, bool isLeft){
  int mappedValue;
  if(isLeft){
    mappedValue = map(reading, LGT_THR_LFT_MIN, LGT_THR_LFT_MAX, 0, 1023);
  }else{
    mappedValue = map(reading, LGT_THR_RGT_MIN, LGT_THR_RGT_MAX, 0, 1023);
  }
  mappedValue = mappedValue/4;
  if(mappedValue < 0) return 0;
  // --------------------------
  if(mappedValue > 255) return 255;
  return mappedValue;
}

