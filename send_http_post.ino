#include <SoftwareSerial.h>

SoftwareSerial sim(10, 11);
const int pin_Gled = 13;
const int pin_Rled = A3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sim.begin(38400);

  delay(100);

  pinMode(pin_Rled, OUTPUT);
   pinMode(pin_Gled, OUTPUT);

  digitalWrite(pin_Rled, LOW);
  delay(100);
   digitalWrite(pin_Gled, HIGH);
  delay(100);
  Serial.println("reseting sim800l module...1");

  delay(100);
  Serial.println("done reseting ");


  sim.println("AT");
  delay(100); gsmRead();
  Serial.println("begin!");

  gsmStart();
  Serial.println("Setting gsm internet...!");


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

void loop() {

  Serial.println("Sending http post...!");

   Smartbin();
  delay(5000);

}

void gsmRead() {
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

/* void gsmHTTP(){
  sim.println("AT+HTTPINIT");
  delay(2000);
  gsmRead();

  sim.print("AT+HTTPPARA=\"URL\",\"http://smartbinproject.herokuapp.com/smartbin/bins");
  sim.print("smart_bin is full  ");
  sim.println("\"");
  delay(1000);
  gsmRead();
  /*
  https://smartbinproject.herokuapp.com/smartbin/bins


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

  //API
  sim.print("AT+HTTPPARA=\"URL\",\"http://ratty53iadu.000webhostapp.com/smartbin_talk.php?value=");

  sim.print("full");
  sim.println("\"");
  delay(1000);
  gsmRead();

  sim.println("AT+HTTPACTION=0");
  delay(8000);
  gsmRead();



  sim.println("AT+HTTPTERM");
  delay(1000);
  gsmRead();

   sim.println("AT+CFUN=0");
   delay(2000);

       sim.println("AT+CFUN=1");
   delay(3000);
  }

  void gsmInternet(){

  }
*/




void Smartbin() {

  float distance_ =  binStatus();
  // distance_ = 3;
  Serial.println("distance: ");
  Serial.print(distance_);

  Serial.println();
  String content_distance = "";

  if ( (distance_ >= 1.0) && distance_ <= 5.0) {
    conn_server("bin_full", "binstatus");
    Serial.println("binstatus : FULL");

    digitalWrite(pin_Gled, LOW);

    delay(100);

    digitalWrite(pin_Rled, HIGH);
    delay(100);

    content_distance = distance_;
    conn_server(content_distance, "content_distance");
    content_distance = "";
    distance_  = 0.0;
  }


  if (distance_ >= 6.0 && distance_ <= 500.0) {
    //while(true)
    conn_server("bin_not_full", "binstatus");
    Serial.println("binstatus : NOT FULL");

    digitalWrite(pin_Gled, HIGH);

    delay(100);

    digitalWrite(pin_Rled, LOW);
    delay(100);


    content_distance = distance_;
    conn_server(content_distance, "content_distance");
    content_distance = "";

  }

  distance_  = 0.0;
  Serial.println(distance_);
  // Serial.println("binstatus : NOT FULL");

}

const int trigPin = 8;
const int echoPin = 3;



float binStatus() {
  long duration;
  float distance;
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
  distance = duration * 0.034 / 2;



  return distance;
}

void conn_server(String server_message, String value) {


  sim.println("AT+HTTPINIT");
  delay(2000);
  gsmRead();

  //API
  sim.print(("AT+HTTPPARA=\"URL\",\"http://ratty53iadu.000webhostapp.com/smartbin_talk.php?" + value + "="));
  sim.print(server_message);
  sim.println("\"");
  delay(1000);
  gsmRead();

  sim.println("AT+HTTPACTION=0");
  delay(8000);
  gsmRead();



  sim.println("AT+HTTPTERM");
  delay(1000);
  gsmRead();

  sim.println("AT+CFUN=0");
  delay(2000);

  sim.println("AT+CFUN=1");
  delay(3000);
}



