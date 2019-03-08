#include <SoftwareSerial.h>

SoftwareSerial sim(6,7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sim.begin(4800);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
   sim.println("AT");
  delay(100);
  while(sim.available())
  {
    Serial.write(sim.read());
  }
  sim.println("AT+CGATT?");
  delay(100);
  while(sim.available())
  {
    Serial.write(sim.read());
  }

  sim.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(100);
  while(sim.available())
  {
    Serial.write(sim.read());
  }

  sim.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  delay(100);
  while(sim.available())
  {
    Serial.write(sim.read());
  }

  sim.println("AT+SAPBR=2,1");
  delay(1500);
  while(sim.available())
  {
    Serial.write(sim.read());
  }

  sim.println("AT+HTTPINIT");
  delay(1500);
  while(sim.available())
  {
    Serial.write(sim.read());
  }

  sim.print("AT+HTTPPARA=\"URL\",\"http://google.com");
  sim.print(random(1,5));
  sim.println("\"");
  delay(2000);
  while(sim.available())
  {
    Serial.write(sim.read());
  }

  sim.println("AT+HTTPACTION=0");
  delay(4000);
  while(sim.available())
  {
    Serial.write(sim.read());
  }

  sim.println("AT+HTTPTERM");
  delay(1000);
  while(sim.available())
  {
    Serial.write(sim.read());
  }
}


/*
send on from mega to to turn on ledGreen on uno 
using hardware serial to recieve data from mega
using hardware Softport on mega to send data
*/

//#include <SoftwareSerial.h>

//SoftwareSerial Serial(10, 11); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(ledGreen_BUILTIN, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


 Serial.println("send 'on' or 'off' to toggle ledGreen on pin 13");

}
String data;
void loop() { // run over and over
//try catch hardware serial data over rx and tx
  if (Serial.available()) {

 data = Serial.readString();
  if(data.equals("on"))
  {
    digitalWrite(ledGreen_BUILTIN, HIGH);
    delay(10);
    Serial.println("the uno ledGreen is on");
    //recieve string data on mega into a variable
  }

  //turing ledGreen off
   if(data.equals("off"))
  {
    digitalWrite(ledGreen_BUILTIN, LOW);
    delay(10);
    Serial.println("the uno ledGreen is off");
  }

  }

  }


//this runs on the mega which is the master connected to the laptop

String data ="";


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Softport.begin(9600);

  //pinMode(ledGreen_BUILTIN, OUTPUT);
  while (!Softport) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

    if (Softport.available()) {
       Serial.println("data arrived on Softport");
       delay(100);
      data = Softport.readString();
      Serial.println(data);
    }
        if (Serial.available()) {
       delay(100);

      data = Serial.readString();
      Softport.println(data);
       Serial.println("data sent on Softport");
    }

}

void loop() { // run over and over
//try catch hardware serial data over rx and tx
 
   if (Softport.available()) {
       delay(100);

       Serial.println("data in Softport");

      data = Softport.readString();
      Serial.println(data);
    }
        if (Serial.available()) {
       delay(100);

      data = Serial.readString();
      Softport.println(data);
       Serial.println("data out Softport");

    }
    /*
    const int ledGreenPin=32;
const int ledGreenPin2=33;
boolean ledGreenState=LOW;
String readString;
unsigned long previousMillis=0;
const int interval=2000;

void setup()  
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Softport.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  while (!Softport) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

pinMode(ledGreenPin,OUTPUT);
pinMode(ledGreenPin2,OUTPUT);
Serial.println("Setup Finished");
}

void loop() // run over and over
{blinkwithoutDelay();
checkBluetooth();
}
void blinkwithoutDelay(){
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    ledGreenState=!ledGreenState;
    if (ledGreenState==HIGH)
    Softport.println(F("ledGreen2 is on"));
    else
    Softport.println(F("ledGreen2 is off"));
    digitalWrite(ledGreenPin2, ledGreenState);
  }
}
void checkBluetooth()
{
  if (Softport.available())
  {
    Serial.println(F("something available"));
    Serial.print(F("Number of bytes available: "));
    Serial.println(Softport.available());
    Serial.print(F("The first Byte is a: "));
   // Serial.println(Softport.read());
    char c =Softport.read();
    readString+=c;
    Serial.write(c);
    Serial.println();
    Serial.print(F("The readString is: "));
    Serial.println(readString);
    Serial.println(F("==========end of this loop============"));
    Serial.println();
    if (readString.endsWith("On"))
    {
      digitalWrite(ledGreenPin,HIGH);
      Serial.println(F("ledGreen1 is high"));
    }
    else if (readString.endsWith("Off"))
    { digitalWrite(ledGreenPin,LOW);
      Serial.println(F("ledGreen1 is low"));
    }
  } 
}*/
const int ledGreenPin=32;
const int ledGreenPin2=33;
boolean ledGreenState=LOW;
String readString;
unsigned long previousMillis=0;
const int interval=2000;

void setup()  
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Softport.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  while (!Softport) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

pinMode(ledGreenPin,OUTPUT);
pinMode(ledGreenPin2,OUTPUT);
Serial.println("Setup Finished");
}

void loop() // run over and over
{blinkwithoutDelay();
checkBluetooth();
}
void blinkwithoutDelay(){
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    ledGreenState=!ledGreenState;
    if (ledGreenState==HIGH)
    Softport.println(F("ledGreen2 is on"));
    else
    Softport.println(F("ledGreen2 is off"));
    digitalWrite(ledGreenPin2, ledGreenState);
  }
}
void checkBluetooth()
{
  if (Softport.available())
  {
    Serial.println(F("something available"));
    Serial.print(F("Number of bytes available: "));
    Serial.println(Softport.available());
    Serial.print(F("The first Byte is a: "));
   // Serial.println(Softport.read());
    char c =Softport.read();
    readString+=c;
    Serial.write(c);
    Serial.println();
    Serial.print(F("The readString is: "));
    Serial.println(readString);
    Serial.println(F("==========end of this loop============"));
    Serial.println();
    if (readString.endsWith("On"))
    {
      digitalWrite(ledGreenPin,HIGH);
      Serial.println(F("ledGreen1 is high"));
    }
    else if (readString.endsWith("Off"))
    { digitalWrite(ledGreenPin,LOW);
      Serial.println(F("ledGreen1 is low"));
    }
  } 
}




//this runs on the mega which is the master connected to the laptop

String data ="";


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Softport.begin(9600);

  //pinMode(ledGreen_BUILTIN, OUTPUT);
  //while(!Softport) {
    // wait for serial port to connect. Needed for native USB port only
 // }
/*
    if (Softport.available()>=4) {
       Serial.println("data arrived on Softport");
       delay(1000);
       while(Softport.available()>=1){
      data = Softport.readString();
       }
      Serial.println(data);
    }
    
        if (Serial.available()>=1) {
       delay(1000);
  while(Serial.available()>=1){
      data = Serial.readString();
  }
      Softport.println(data);
       Serial.println("data sent on Softport");
    }
  }*/
}

void loop() { // run over and over
//try catch hardware serial data over rx and tx
 
   if (Softport.available()>=1) {
       delay(1000);

       Serial.println("data in Softport");
      while(Softport.available()>=1){
      data = Softport.readString();
      }
      Serial.println(data);
    }
       else if (Serial.available()>1) {
       delay(1000);
       
       while(Softport.available()>=1){
      data = Serial.readString();
       }
      Softport.println(data);
      // Softport.print(data);
       Serial.println("data out Softport");

    }
}

eventListner(String data){




}

/*

Arduino: 1.8.5 (Windows 10), Board: "Arduino/Genuino Mega or Mega 2560, ATmega2560 (Mega 2560)"

C:\Program Files (x86)\Arduino\arduino-builder -dump-prefs -logger=machine -hardware C:\Program Files (x86)\Arduino\hardware -hardware C:\Users\FaithWorks\AppData\Local\Arduino15\packages -tools C:\Program Files (x86)\Arduino\tools-builder -tools C:\Program Files (x86)\Arduino\hardware\tools\avr -tools C:\Users\FaithWorks\AppData\Local\Arduino15\packages -built-in-libraries C:\Program Files (x86)\Arduino\libraries -libraries C:\Users\FaithWorks\Documents\Arduino\libraries -fqbn=arduino:avr:mega:cpu=atmega2560 -ide-version=10805 -build-path C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823 -warnings=default -build-cache C:\Users\FAITHW~1\AppData\Local\Temp\arduino_cache_886703 -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.avr-gcc.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -prefs=runtime.tools.arduinoOTA.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -prefs=runtime.tools.avrdude.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -verbose C:\Users\FaithWorks\Documents\Arduino\UNNo_serial1_modified\UNNo_serial1_modified.ino
C:\Program Files (x86)\Arduino\arduino-builder -compile -logger=machine -hardware C:\Program Files (x86)\Arduino\hardware -hardware C:\Users\FaithWorks\AppData\Local\Arduino15\packages -tools C:\Program Files (x86)\Arduino\tools-builder -tools C:\Program Files (x86)\Arduino\hardware\tools\avr -tools C:\Users\FaithWorks\AppData\Local\Arduino15\packages -built-in-libraries C:\Program Files (x86)\Arduino\libraries -libraries C:\Users\FaithWorks\Documents\Arduino\libraries -fqbn=arduino:avr:mega:cpu=atmega2560 -ide-version=10805 -build-path C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823 -warnings=default -build-cache C:\Users\FAITHW~1\AppData\Local\Temp\arduino_cache_886703 -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.avr-gcc.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -prefs=runtime.tools.arduinoOTA.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -prefs=runtime.tools.avrdude.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -verbose C:\Users\FaithWorks\Documents\Arduino\UNNo_serial1_modified\UNNo_serial1_modified.ino
Using board 'mega' from platform in folder: C:\Program Files (x86)\Arduino\hardware\arduino\avr
Using core 'arduino' from platform in folder: C:\Program Files (x86)\Arduino\hardware\arduino\avr
Detecting libraries used...
"C:\Program Files (x86)\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics  -flto -w -x c++ -E -CC -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10805 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino" "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega" "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\sketch\UNNo_serial1_modified.ino.cpp" -o "nul"
Generating function prototypes...
"C:\Program Files (x86)\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics  -flto -w -x c++ -E -CC -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10805 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino" "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega" "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\sketch\UNNo_serial1_modified.ino.cpp" -o "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\preproc\ctags_target_for_gcc_minus_e.cpp"
"C:\Program Files (x86)\Arduino\tools-builder\ctags\5.8-arduino11/ctags" -u --language-force=c++ -f - --c++-kinds=svpf --fields=KSTtzns --line-directives "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\preproc\ctags_target_for_gcc_minus_e.cpp"
Compiling sketch...
"C:\Program Files (x86)\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os  -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10805 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino" "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega" "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\sketch\UNNo_serial1_modified.ino.cpp" -o "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\sketch\UNNo_serial1_modified.ino.cpp.o"
C:\Users\FaithWorks\Documents\Arduino\UNNo_serial1_modified\UNNo_serial1_modified.ino: In function 'void loop()':

UNNo_serial1_modified:17: error: 'eventLister' was not declared in this scope

 eventLister(Serial.readString());

                                ^

exit status 1
'eventLister' was not declared in this scope
*/

void eventListner(String data);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(ledGreen_BUILTIN, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


 Serial.println("send 'on' or 'off' to toggle ledGreen on pin 13");


}

void loop() { // run over and over
String data = Serial.readString();
eventListner(data);

}


void eventListner(String data){

//code goes here  
//try catch hardware serial data over rx and tx
 if(data.endsWith("on"))
  {
    digitalWrite(ledGreen_BUILTIN, HIGH);
    delay(10);
    Serial.println("the uno ledGreen is on");

    //recieve string data on mega into a variable
    //mega = Serial.readString();  Serial.println(mega);
  }

  //turing ledGreen off
  if(data.endsWith("off"))
  {
    digitalWrite(ledGreen_BUILTIN, LOW);
    delay(10);
    Serial.println("the uno ledGreen is off");
  }
  

  }
}

void eventListner(String data){
//try catch hardware serial data over rx and tx
  if (Serial.available()>=1) {
   while (Serial.available()>=1){
 //data = Serial.readString();
   }
 
  if(data.endsWith("on"))
  {
    digitalWrite(ledGreen_BUILTIN, HIGH);
    delay(10);
    Serial.println("the uno ledGreen is on");
    //recieve string data on mega into a variable
  }

  //turing ledGreen off
  if(data.endsWith("off"))
  {
    digitalWrite(ledGreen_BUILTIN, LOW);
    delay(10);
    Serial.println("the uno ledGreen is off");
  }
  

  }

  }

/*
  Arduino: 1.8.5 (Windows 10), Board: "Arduino/Genuino Mega or Mega 2560, ATmega2560 (Mega 2560)"

C:\Program Files (x86)\Arduino\arduino-builder -dump-prefs -logger=machine -hardware C:\Program Files (x86)\Arduino\hardware -hardware C:\Users\FaithWorks\AppData\Local\Arduino15\packages -tools C:\Program Files (x86)\Arduino\tools-builder -tools C:\Program Files (x86)\Arduino\hardware\tools\avr -tools C:\Users\FaithWorks\AppData\Local\Arduino15\packages -built-in-libraries C:\Program Files (x86)\Arduino\libraries -libraries C:\Users\FaithWorks\Documents\Arduino\libraries -fqbn=arduino:avr:mega:cpu=atmega2560 -ide-version=10805 -build-path C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823 -warnings=default -build-cache C:\Users\FAITHW~1\AppData\Local\Temp\arduino_cache_886703 -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.avr-gcc.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -prefs=runtime.tools.arduinoOTA.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -prefs=runtime.tools.avrdude.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -verbose C:\Users\FaithWorks\Documents\Arduino\UNNo_serial1_modified\UNNo_serial1_modified.ino
C:\Program Files (x86)\Arduino\arduino-builder -compile -logger=machine -hardware C:\Program Files (x86)\Arduino\hardware -hardware C:\Users\FaithWorks\AppData\Local\Arduino15\packages -tools C:\Program Files (x86)\Arduino\tools-builder -tools C:\Program Files (x86)\Arduino\hardware\tools\avr -tools C:\Users\FaithWorks\AppData\Local\Arduino15\packages -built-in-libraries C:\Program Files (x86)\Arduino\libraries -libraries C:\Users\FaithWorks\Documents\Arduino\libraries -fqbn=arduino:avr:mega:cpu=atmega2560 -ide-version=10805 -build-path C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823 -warnings=default -build-cache C:\Users\FAITHW~1\AppData\Local\Temp\arduino_cache_886703 -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.avr-gcc.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -prefs=runtime.tools.arduinoOTA.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -prefs=runtime.tools.avrdude.path=C:\Program Files (x86)\Arduino\hardware\tools\avr -verbose C:\Users\FaithWorks\Documents\Arduino\UNNo_serial1_modified\UNNo_serial1_modified.ino
Using board 'mega' from platform in folder: C:\Program Files (x86)\Arduino\hardware\arduino\avr
Using core 'arduino' from platform in folder: C:\Program Files (x86)\Arduino\hardware\arduino\avr
Detecting libraries used...
"C:\Program Files (x86)\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics  -flto -w -x c++ -E -CC -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10805 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino" "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega" "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\sketch\UNNo_serial1_modified.ino.cpp" -o "nul"
Generating function prototypes...
"C:\Program Files (x86)\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics  -flto -w -x c++ -E -CC -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10805 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino" "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega" "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\sketch\UNNo_serial1_modified.ino.cpp" -o "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\preproc\ctags_target_for_gcc_minus_e.cpp"
"C:\Program Files (x86)\Arduino\tools-builder\ctags\5.8-arduino11/ctags" -u --language-force=c++ -f - --c++-kinds=svpf --fields=KSTtzns --line-directives "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\preproc\ctags_target_for_gcc_minus_e.cpp"
Compiling sketch...
"C:\Program Files (x86)\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os  -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10805 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino" "-IC:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega" "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\sketch\UNNo_serial1_modified.ino.cpp" -o "C:\Users\FAITHW~1\AppData\Local\Temp\arduino_build_81823\sketch\UNNo_serial1_modified.ino.cpp.o"
C:\Users\FaithWorks\Documents\Arduino\UNNo_serial1_modified\UNNo_serial1_modified.ino: In function 'void loop()':

UNNo_serial1_modified:21: error: expected primary-expression before 'data'

 eventListner(String data = Serial.readString());

                     ^

exit status 1
expected primary-expression before 'data'*/

#include <SoftwareSerial.h>


SoftwareSerial Softport(52, 53);

char data ='null';


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
 Softport.begin(9600);
 Softport.listen();
}

void loop() { // run over and over
//try catch hardware serial data over rx and tx

         Softport.listen();

 
   if (Softport.available()>=1) {
       delay(500);

       Serial.println("data in Softport");
      while(Softport.available()>=1){
      data = Softport.readString();
      }
      Serial.println(data);
    }
        if (Serial.available()>1) {
       delay(500);
       
       while(Softport.available()>=1){
      data = Serial.readString();
       }
      Softport.println(data);
      // Softport.print(data);
       Serial.println("data out Softport");

    }
}

mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+ZZxxxxxxxxxx\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("Last Minute Engineers | lastminuteengineers.com"); //text content
  updateSerial();
  mySerial.write(26);
}

void loop()
{
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}






/*
int ledGreen = 3;           // the PWM pin the ledGreen is attached to
int brightness = 0;    // how bright the ledGreen is
int fadeAmount = 5;    // how many points to fade the ledGreen by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(ledGreen, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  analogWrite(ledGreen, brightness);
  //analogwrite takes 

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}*/
int ledGreen = 3;           // the PWM pin the ledGreen is attached to
int brightness = 0;    // how bright the ledGreen is
int fadeAmount = 5;    // how many points to fade the ledGreen by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(ledGreen, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  analogWrite(ledGreen, brightness);
  //analogwrite takes parameters, the pin number and the pwm value between(0- 255)

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}

void ledGreenGreenSend_Data()
{
  int ledGreen = 3;           // the PWM pin the ledGreen is attached to
int brightness = 0;    // how bright the ledGreen is
int fadeAmount = 5;    // how many points to fade the ledGreen by
  analogWrite(ledGreen, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  delay(70);


saints24ratty53i22


}

/*
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
//long   lat,lon; // create variable for latitude and longitude object
float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(3,4);//rx,tx
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
TinyGPS gps; // create gps object
void setup(){
Serial.begin(9600); // connect serial
//Serial.println("The GPS Received Signal:");
gpsSerial.begin(9600); // connect gps sensor
lcd.begin(16,2);
}
 
void loop(){
    while(gpsSerial.available()){ // check for gps data
    if(gps.encode(gpsSerial.read()))// encode gps data
    { 
    gps.f_get_position(&lat,&lon); // get latitude and longitude
    // display position
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("GPS Signal");
    //Serial.print("Position: ");
    //Serial.print("Latitude:");
    //Serial.print(lat,6);
    //Serial.print(";");
    //Serial.print("Longitude:");
    //Serial.println(lon,6); 
    lcd.setCursor(1,0);
    lcd.print("LAT:");
    lcd.setCursor(5,0);
    lcd.print(lat);
    //Serial.print(lat);
    //Serial.print(" ");
    
    lcd.setCursor(0,1);
    lcd.print(",LON:");
    lcd.setCursor(5,1);
    lcd.print(lon);
    
   }
  }
  
  String latitude = String(lat,6);
    String longitude = String(lon,6);
  Serial.println(latitude+";"+longitude);
  delay(1000);
  
}*/
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
//long   lat,lon; // create variable for latitude and longitude object
float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(3,4);//rx,tx
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
TinyGPS gps; // create gps object
void setup(){
Serial.begin(9600); // connect serial
//Serial.println("The GPS Received Signal:");
gpsSerial.begin(9600); // connect gps sensor
lcd.begin(16,2);
}
 
void loop(){
    while(gpsSerial.available()){ // check for gps data
    if(gps.encode(gpsSerial.read()))// encode gps data
    { 
    gps.f_get_position(&lat,&lon); // get latitude and longitude
    // display position
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("GPS Signal");
    //Serial.print("Position: ");
    //Serial.print("Latitude:");
    //Serial.print(lat,6);
    //Serial.print(";");
    //Serial.print("Longitude:");
    //Serial.println(lon,6); 
    lcd.setCursor(1,0);
    lcd.print("LAT:");
    lcd.setCursor(5,0);
    lcd.print(lat);
    //Serial.print(lat);
    //Serial.print(" ");
    
    lcd.setCursor(0,1);
    lcd.print(",LON:");
    lcd.setCursor(5,1);
    lcd.print(lon);
    
   }
  }
  
  String latitude = String(lat,6);
    String longitude = String(lon,6);
  Serial.println(latitude+";"+longitude);
  delay(1000);
  
}

/*

VSS ======= GND
VCC ======= 5V
VEE ======= 10K Resistor
RS ======= A0 (Analog pin)
R/W ======== GND
E ======== A1
D4 ======== A2
D5 ======== A3
D6 ======== A4
D7 ======== A5
LED+ ======= VCC
LED- ======= GND
Programming
Arduino IDE
*/
#include <LiquidCrystal.h> 
#include <SoftwareSerial.h> 
#include <TinyGPS.h> 
float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object  
SoftwareSerial gpsSerial(3,4);//rx,tx 
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5); 
TinyGPS gps; // create gps object 
void setup(){ 
Serial.begin(9600); // connect serial 
//Serial.println("The GPS Received Signal:"); 
gpsSerial.begin(9600); // connect gps sensor 
lcd.begin(16,2); 
} 
void loop(){ 
  while(gpsSerial.available()){ // check for gps data 
  if(gps.encode(gpsSerial.read()))// encode gps data 
  {  
  gps.f_get_position(&lat,&lon); // get latitude and longitude 
  // display position 
  lcd.clear(); 
  lcd.setCursor(1,0); 
  lcd.print("GPS Signal"); 
  //Serial.print("Position: "); 
  //Serial.print("Latitude:"); 
  //Serial.print(lat,6); 
  //Serial.print(";"); 
  //Serial.print("Longitude:"); 
  //Serial.println(lon,6);  
  lcd.setCursor(1,0); 
  lcd.print("LAT:"); 
  lcd.setCursor(5,0); 
  lcd.print(lat); 
  //Serial.print(lat); 
  //Serial.print(" "); 
  lcd.setCursor(0,1); 
  lcd.print(",LON:"); 
  lcd.setCursor(5,1); 
  lcd.print(lon); 
 } 
} 
String latitude = String(lat,6); 
  String longitude = String(lon,6); 
Serial.println(latitude+";"+longitude); 
delay(1000); 
} 

 /*
 Example code for connecting a Parallax GPS module to the Arduino
 Igor Gonzalez Martin. 05-04-2007
 igor.gonzalez.martin@gmail.com
 English translation by djmatic 19-05-2007
 Listen for the $GPRMC string and extract the GPS location data from this.
 Display the result in the Arduino's serial monitor.
 */ 
 #include <string.h>
 #include <ctype.h>
 int ledPin = 13;                  // LED test pin
 int rxPin = 0;                    // RX PIN 
 int txPin = 1;                    // TX TX
 int byteGPS=-1;
 char linea[300] = "";
 char comandoGPR[7] = "$GPRMC";
 int cont=0;
 int bien=0;
 int conta=0;
 int indices[13];
 void setup() {
   pinMode(ledPin, OUTPUT);       // Initialize LED pin
   pinMode(rxPin, INPUT);
   pinMode(txPin, OUTPUT);
   Serial.begin(4800);
   for (int i=0;i<300;i++){       // Initialize a buffer for received data
     linea[i]=' ';
   }   
 }
 void loop() {
   digitalWrite(ledPin, HIGH);
   byteGPS=Serial.read();         // Read a byte of the serial port
   if (byteGPS == -1) {           // See if the port is empty yet
     delay(100); 
   } else {
     // note: there is a potential buffer overflow here!
     linea[conta]=byteGPS;        // If there is serial port data, it is put in the buffer
     conta++;                      
     Serial.print(byteGPS, BYTE); 
     if (byteGPS==13){            // If the received byte is = to 13, end of transmission
       // note: the actual end of transmission is <CR><LF> (i.e. 0x13 0x10)
       digitalWrite(ledPin, LOW); 
       cont=0;
       bien=0;
       // The following for loop starts at 1, because this code is clowny and the first byte is the <LF> (0x10) from the previous transmission.
       for (int i=1;i<7;i++){     // Verifies if the received command starts with $GPR
         if (linea[i]==comandoGPR[i-1]){
           bien++;
         }
       }
       if(bien==6){               // If yes, continue and process the data
         for (int i=0;i<300;i++){
           if (linea[i]==','){    // check for the position of the  "," separator
             // note: again, there is a potential buffer overflow here!
             indices[cont]=i;
             cont++;
           }
           if (linea[i]=='*'){    // ... and the "*"
             indices[12]=i;
             cont++;
           }
         }
         Serial.println("");      // ... and write to the serial port
         Serial.println("");
         Serial.println("---------------");
         for (int i=0;i<12;i++){
           switch(i){
             case 0 :Serial.print("Time in UTC (HhMmSs): ");break;
             case 1 :Serial.print("Status (A=OK,V=KO): ");break;
             case 2 :Serial.print("Latitude: ");break;
             case 3 :Serial.print("Direction (N/S): ");break;
             case 4 :Serial.print("Longitude: ");break;
             case 5 :Serial.print("Direction (E/W): ");break;
             case 6 :Serial.print("Velocity in knots: ");break;
             case 7 :Serial.print("Heading in degrees: ");break;
             case 8 :Serial.print("Date UTC (DdMmAa): ");break;
             case 9 :Serial.print("Magnetic degrees: ");break;
             case 10 :Serial.print("(E/W): ");break;
             case 11 :Serial.print("Mode: ");break;
             case 12 :Serial.print("Checksum: ");break;
           }
           for (int j=indices[i];j<(indices[i+1]-1);j++){
             Serial.print(linea[j+1]); 
           }
           Serial.println("");
         }
         Serial.println("---------------");
       }
       conta=0;                    // Reset the buffer
       for (int i=0;i<300;i++){    //  
         linea[i]=' ';             
       }                 
     }
   }
 }

 /*
 #include <Adafruit_GPS.h>
#include <Adafruit_GPS.h>
//We can now create our Software Serial object after including the library
SoftwareSerial mySerial(3, 2);

//And finally attach our Serial object pins to our GPS module
Adafruit_GPS GPS(&mySerial);

void setup() {
Serial.begin(115200); //This baud rate will help a lot in printing all of the data that comes from the GPS Module to the serial monitor
GPS.begin(9600); 
//These lines configure the GPS Module
GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //Sets output to only RMC and GGA sentences
GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //Sets the output to 1/second. If you want you can go higher/lower
GPS.sendCommand(PGCMD_ANTENNA); //Can report if antenna is connected or not
}

void loop() {
//Now we will start our GPS module, parse (break into parts) the Last NMEA sentence 
GPS.parse(GPS.lastNMEA()); //This is going to parse the last NMEA sentence the Arduino has received, breaking it down into its constituent parts.
GPS.newNMEAreceived(); //This will return a boolean TRUE/FALSE depending on the case.
//Print the current date/time/etc
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
//If GPS module has a fix, line by line prints the GPS information
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Location (in degrees, works with Google Maps): ");
      Serial.print(GPS.latitudeDegrees, 4);
      Serial.print(", ");
      Serial.println(GPS.longitudeDegrees, 4);
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
}*/

#include <Adafruit_GPS.h>
#include <Adafruit_GPS.h>
//We can now create our Software Serial object after including the library
SoftwareSerial mySerial(3, 2);

//And finally attach our Serial object pins to our GPS module
Adafruit_GPS GPS(&mySerial);

void setup() {
Serial.begin(115200); //This baud rate will help a lot in printing all of the data that comes from the GPS Module to the serial monitor
GPS.begin(9600); 
//These lines configure the GPS Module
GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //Sets output to only RMC and GGA sentences
GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //Sets the output to 1/second. If you want you can go higher/lower
GPS.sendCommand(PGCMD_ANTENNA); //Can report if antenna is connected or not
}

void loop() {
//Now we will start our GPS module, parse (break into parts) the Last NMEA sentence 
GPS.parse(GPS.lastNMEA()); //This is going to parse the last NMEA sentence the Arduino has received, breaking it down into its constituent parts.
GPS.newNMEAreceived(); //This will return a boolean TRUE/FALSE depending on the case.
//Print the current date/time/etc
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
//If GPS module has a fix, line by line prints the GPS information
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Location (in degrees, works with Google Maps): ");
      Serial.print(GPS.latitudeDegrees, 4);
      Serial.print(", ");
      Serial.println(GPS.longitudeDegrees, 4);
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
}