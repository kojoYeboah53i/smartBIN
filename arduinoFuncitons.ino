
//constrain sensor value 
int constrainedInput = constrain(Serial.parseInt(), minimumValue, maximumValue); // this is wrong 

//avoid using other functions inside the constrain

//use this instead 
int input = Serial.parseInt();
int constrainedInput = constrain(input, minimumValue, maximumValue); // this is wrong 

sensVal = constrain(sensVal, 10, 150);  // limits range of sensor values to between 10 and 150
/*
Returns
sensVal: if sensVal is between 10 and 150

10: if sensVal is less than 10

150: if sensVal is greater than 150

*/


//parseInt() returns the first valid (long) integer number from the serial buffer
parseInt(char skipChar);  //skipChar: used to skip the indicated char in the search