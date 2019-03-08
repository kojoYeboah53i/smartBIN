

int ledGreen = 3, ledYellow = 4, brightness = 0, fadeAmount = 40;




void setup() {
  // declare pin 9 to be an output:
  pinMode(ledGreen, OUTPUT);
   pinMode(ledYellow, OUTPUT);
}


void loop() {
  ledGreenSend_Data();
  ledYellowRecieve_Data();
}




//led blink to indicate data sent
void ledGreenSend_Data()
{

  analogWrite(ledGreen, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    delay(70);
  }

}


  //led blink to indicate data recieved
  void ledYellowRecieve_Data()
  {

    analogWrite(ledYellow, brightness);
    brightness = brightness + fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
      delay(70);

    }
  }
