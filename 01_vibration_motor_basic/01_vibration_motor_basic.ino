void setup() {
  // put your setup code here, to run once:
  pinMode (5, OUTPUT); 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (5, HIGH); //vibrates throught pin 5
  delay (1000); // for 1000 miliseconds
  digitalWrite (5, LOW); //stops throught pin 5
  delay (1000); // for 1000 miliseconds
  
}
