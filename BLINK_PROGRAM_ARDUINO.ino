/*
  Blink onboard LED at 0.1 second interval
*/
void setup() {
  // initialize digital pin PB2 as an output.
  pinMode(A0, OUTPUT); // LED connect to pin PC13
}
void loop() {
  digitalWrite(A0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for 100mS
  digitalWrite(A0, LOW);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for 100mS
}
