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
$url = 'https://smartbin-projwork.herokuapp.com/updatebin?bin_id=1';
 

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


