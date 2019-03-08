#include <SoftwareSerial.h>

SoftwareSerial sim(10, 11);
const int ledPin= 3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sim.begin(38400);

  delay(100);

   pinMode(ledPin, OUTPUT);

    digitalWrite(ledPin, LOW);
  delay(100);
  Serial.println("reseting sim800l module...1");

 delay(100);
  Serial.println("done reseting ");


      sim.println("AT");
  delay(100); gsmRead();
   Serial.println("begin!");

 gsmStart();
   Serial.println("Setting gsm internet...!");

 gsmInternet();
}

void loop() {

 Serial.println("Sending http post...!");

  gsmHTTP();
  delay(5000);
  gsmHTTP_2();
}

void gsmRead(){
   while (sim.available())
  {
    Serial.write(sim.read());
  }

}

void gsmStart()
{
    // put your main code here, to run repeatedly:

    sim.println("AT+CMEE=2");
  delay(4000);
  // Serial.println("GPRS is OFF!");
 gsmRead();

            sim.println("AT+CSQ=?");  //AT+CBAND? 
  delay(1000);
 gsmRead();
 
              sim.println("AT+CBAND?");  //
  delay(1000);
 gsmRead();
              sim.println("AT+CBAND=DCS_MODE");  //AT+CBAND? 
  delay(1000);
   gsmRead();

  }

  void gsmHTTP(){
sim.println("AT+HTTPINIT");
  delay(2000);
  gsmRead();

  sim.print("AT+HTTPPARA=\"URL\",\"http://ratty53iadu.000webhostapp.com/mainfile.php?value=");
   sim.print("Loretta ");
  sim.println("\"");
  delay(1000);
  gsmRead();

 sim.println("AT+HTTPACTION=0");
  delay(8000);
  gsmRead();

 sim.println("AT+HTTPACTION=0,20");
  delay(3000);
  gsmRead();

  sim.println("AT+HTTPTERM");
  delay(1000);
  gsmRead();

}
  void gsmHTTP_2(){
sim.println("AT+HTTPINIT");
  delay(2000);
  gsmRead();

  sim.print("AT+HTTPPARA=\"URL\",\"http://ratty53iadu.000webhostapp.com/testfile.php?value=");
   sim.print("Jessica ");
  sim.println("\"");
  delay(1000);
  gsmRead();

 sim.println("AT+HTTPACTION=0");
  delay(8000);
  gsmRead();

 sim.println("AT+HTTPACTION=0,20");
  delay(3000);
  gsmRead();

  sim.println("AT+HTTPTERM");
  delay(1000);
  gsmRead();

}

void gsmInternet(){
  sim.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(1000);
gsmRead();
  sim.println("AT+SAPBR=3,1,\"APN\",\"web.tigo.com.gh\"");
  delay(5000);
gsmRead();

  sim.println("AT+SAPBR=1,1");
  delay(10000);
gsmRead();
sim.println("AT+SAPBR=2,1");
  delay(10000);
gsmRead();
}
