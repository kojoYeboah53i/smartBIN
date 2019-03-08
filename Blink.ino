int ledGreen = 3, ledYellow = 4, brightness = 0, GreenfadeAmount = 100,  YellowfadeAmount = 10;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
    pinMode(ledGreen, OUTPUT);
   pinMode(ledYellow, OUTPUT);
   digitalWrite(ledGreen,LOW);
    digitalWrite(ledYellow,LOW);
}

// the loop function runs over and over again forever
void loop() {
   led_GreenSend_Data();
   delay(7000);
   
  led_YellowRecieve_Data();
  delay(7000);
}
