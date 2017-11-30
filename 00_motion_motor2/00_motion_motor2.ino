int pin1 = 7; //to LDR left
int pin2 = 8; // to LDR right
int LDRValue1 = 0; // result of reading the digital pin, why 0????????????????
int LDRValue2 = 0; // result of reading the digital pin

void setup() {
  Serial.begin(9600); // ----------- ??? ------------
}

void loop() {
  LDRValue1 = digitalRead(pin1);// read the value from the LDR
  LDRValue2 = digitalRead(pin2);// read the value from the LDR
  
  Serial.print(LDRValue1);         // print the LDR1 value to the serial port
  Serial.print(" ");               // print a space
  Serial.print(LDRValue2);         // print the LDR2 value to the serial port
  
  if((LDRValue1==1)&&(LDRValue2==1)) {
    Serial.print(" -> LOW"); } // for the movement this could be used for go straight
  else if ((LDRValue1==1)&&(LDRValue2==0)) {
    Serial.print(" -> MEDIUM"); }  // for the movement this could be used for go left
    // else if ((LDRValue1==0)&&(LDRValue2==1)) {
   // for the movement this could be used for go right
  else if ((LDRValue1==0)&&(LDRValue2==0)) {
    Serial.print(" -> HIGH"); } // for the movement this could be used for go back
    
  Serial.println(" light");
  
  delay(100);                  
}
