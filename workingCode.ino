// Author Isaac Yeboah 
//https://github.com/kojoYeboah53i/smartBIN
// Could be modified or redistibuted as long as
// all rights resevered under the opensource license






//API URL
//http://smartbin-app-1.herokuapp.com/updatebin?bin_id=1
//http://smartbin-app-1.herokuapp.com/updatebin?bin_id=2//

#ifndef Smartbin_h
#define Smartbin_h

#if (ARDUINO >= 100)

#include "Arduino.h"

#else
#include "WProgram.h"
#endif

#include "SoftwareSerial.h"
SoftwareSerial gsm_(10, 11);
class Smartbin_1

{
public:
  Smartbin_1(int pin1, int pin2, int pin3, int pin4, String bat_status); //constructor
  ~Smartbin_1();
 
  float binStatus();
  bool gsmConn();
  void boot_(String bat_status);
  bool conn_server(String message, String value);

  
    int wait = 2000;
    String gsmData;

    String gsmConnData = "";
    String gsmHttpData ="";

    int pin_Gled;
  int pin_Rled;
  int pin_echo;
  int pin_tripn;
  String server_message;

  String battery;
  String server_url;
  String id_value; 
    long duration;
    float distance;

private:

};

#endif

//   #definiftions  //public function Blink definiftions

//constructor
Smartbin_1::Smartbin_1(int pin1, int pin2, int pin3, int pin4, String bat_status) : pin_Gled(pin1), pin_Rled(pin2), pin_tripn(pin3), pin_echo(pin4), battery(bat_status)
{



  pinMode(pin_Gled, OUTPUT);
  pinMode(pin_Rled, OUTPUT);
  pinMode(pin_tripn, OUTPUT);
  pinMode(pin_echo, INPUT);

  //Serial.println("a new instance is constructed");

  //boot_(battery);
}

//destructor
Smartbin_1::~Smartbin_1(void)
{
  //destroy
  // Serial.println("arduino ram is freed....  ");
}




//binStatus status definiftion
float Smartbin_1::binStatus(){

 
  digitalWrite(pin_tripn, LOW);
  delayMicroseconds(2);
 
  digitalWrite(pin_tripn, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_tripn, LOW);
 
  duration = pulseIn(pin_echo, HIGH);
 
  distance = duration * 0.034 / 2;
  
  return distance;



}
void Smartbin_1::boot_(String bat_status)
{

  if (!gsmConn())
  {

    Serial.println("Connection to server failed!");
  }

  else
   
  delay(5);
    conn_server("The arduino is on", "value");
   
   
}

bool Smartbin_1::gsmConn()
{
 
      gsm_.println("AT+CFUN=1");
      delay(10000);
     while (gsm_.available())
  {
    gsmData += (gsm_.read());
  }
      gsm_.println("AT+CMEE=2");
    delay(wait);
      while (gsm_.available())
  {
    gsmData += (gsm_.read());
  }

  gsm_.println("AT+CGATT=1");
  delay(wait + 8000);
  while (gsm_.available())
  {
    gsmData += (gsm_.read());
  }

  delay(wait);

  gsm_.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(wait);
  while (gsm_.available())
  {
    gsmData += (gsm_.read());
  }

  gsm_.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  delay(wait);
  while (gsm_.available())
  {
    gsmData += (gsm_.read());
  }

  gsm_.println("AT+SAPBR=1,1");
  delay(10000);
  while (gsm_.available())
  {
    gsmData += (gsm_.read());
  }
  gsm_.println("AT+SAPBR=2,1");  
      delay(10000);
  while (gsm_.available())
  {
    gsmConnData += (gsm_.read());
  }
  if ((gsmConnData.indexOf("0,0,0,0") > 0) || (gsmConnData.indexOf("ERROR") > 0))
  {
    //no internet connection
    return false;
  }
  else
    return true;

  //Serial.println(gsmData)  for troublshooting
}

bool Smartbin_1::conn_server(String message, String value)
{
  String gsmHttpData_="";
  server_message= message;
  id_value = value;

  gsm_.println("AT+HTTPINIT");
  delay(wait);
  while (gsm_.available())
  {
    gsmHttpData += (gsm_.read());
  }

  gsm_.print(("AT+HTTPPARA=\"URL\",\"http://ratty53iadu.000webhostapp.com/smartbin_talk.php?"+value+"="));
  gsm_.print(server_message);
  gsm_.println("\"");
  delay(wait);
  while (gsm_.available())
  {
    gsmHttpData += (gsm_.read());
  }

  gsm_.println("AT+HTTPACTION=0");
  delay(wait);
  while (gsm_.available())
  {
    gsmHttpData_ += (gsm_.read());
  }
  
  gsm_.println("AT+HTTPTERM");
  delay(wait);
  while (gsm_.available())
  {
    gsmHttpData+= (gsm_.read());
  }

  if(gsmHttpData_.indexOf("OK") >0 ){
    return true;
  } 
    else return false;

    gsm_.println("AT+CFUN=0");
    delay(10000);
     while (gsm_.available())
  {
    gsmHttpData += (gsm_.read());
  }

  //uncomment this line to debug
  //Serial.println(gsmHttpData)  for troublshooting
}


//application

Smartbin_1 dustbin_1(13, 4, 6, 9, "");

void setup()

{
  Serial.begin(9600);
  
  gsm_.begin(38400);
  

  digitalWrite(dustbin_1.pin_Gled, HIGH);
  digitalWrite(dustbin_1.pin_Rled, LOW);

  }







void loop()
{

    if (!dustbin_1.gsmConn()){
      Serial.println("Connection to server failed");
  }
    float distance_ =  dustbin_1.binStatus();
    String content_distance = "";

  if (distance_ <= 5.0) {
  dustbin_1.conn_server("bin_full", "binstatus");
      Serial.println("binstatus : FULL");
  
  digitalWrite(dustbin_1.pin_Gled, LOW);

  delay(dustbin_1.wait);

  digitalWrite(dustbin_1.pin_Rled, HIGH);
  delay(dustbin_1.wait);

    content_distance = distance_;
    dustbin_1.conn_server(content_distance, "content_distance");
    content_distance = "";
    distance_  =0.0;
    }


    if (distance_ >= 6.0) {
  dustbin_1.conn_server("bin_not_full", "binstatus");
      Serial.println("binstatus : NOT FULL");
  
  digitalWrite(dustbin_1.pin_Gled, HIGH);

  delay(dustbin_1.wait);

  digitalWrite(dustbin_1.pin_Rled, LOW);
  delay(dustbin_1.wait);


    content_distance = distance_;
    dustbin_1.conn_server(content_distance, "content_distance");
    content_distance = "";
    distance_  =0.0;
}

  
}






//php back end script
/*
<?php

session_start();
//binstatus
//content_distance
//value

if (isset($_GET['value'])) {
    $arduinoVar = $GET['value'];
    echo "<H3>The device is on </H3>";
    echo "<br>";
    echo $arduinoVar;
}
if (isset($_GET['content_distance'])) {
    $distance = $GET['content_distance'];
    echo "<H3>The distance the trash and the lid is </H3>";
    echo "<br>";
    echo $distance;
}



//listen for arduino response
if (isset($_GET['binstatus'])){
$binStatus = $GET['binstatus'];

if (!$binStatus==='bin_full') {
    $my_file_update = fopen("Not_ful_update.text", "w");
    fwrite($my_file_update, "bin one not full");
    fclose($my_file_update);
     $_message="arduino called";
}






if ($binStatus==='bin_full'){
    //code goes here
  
 
//API Url
$url = 'http://smartbin-app-1.herokuapp.com/updatebin?bin_id=1';
 

$ch = curl_init($url);
 
//The JSON data.
$jsonData = array(
    'bin_id_1' => 'full',
);
 

$jsonDataEncoded = json_encode($jsonData);
 

curl_setopt($ch, CURLOPT_POST, 1);
 

curl_setopt($ch, CURLOPT_POSTFIELDS, $jsonDataEncoded);
 

curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json')); 
 

$result = curl_exec($ch);


$my_file_update = fopen("full_update.text", "w");
fwrite($my_file_update, "bin one full");
fclose($my_file_update);
 $_message="arduino called";

 
}

}





*/