
//led blink to indicate data sent
void led_GreenSend_Data()
{
 for (int i=0; i<20; i++){
  analogWrite(ledGreen, brightness);
  brightness = brightness + GreenfadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    GreenfadeAmount = GreenfadeAmount;
    delay(40);
     analogWrite(ledGreen, 0);
  }
  
delay(10) ;
}

}


  //led blink to indicate data recieved
  void led_YellowRecieve_Data()
  {
for (int i=0; i<20; i++){
    analogWrite(ledYellow, brightness);
    brightness = brightness +YellowfadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      YellowfadeAmount = -YellowfadeAmount;
      delay(110);
      analogWrite(ledYellow, 0);

    }
    delay(10); }
  }
