<?php
session_start();
$eunits = $_SESSION['eunits'];
$time = 1030;
$eunits = 10;
$ebill = $eunits*1.45;
$conn = new mysqli("localhost", "id2119234_abhinav", "ps3isfun", "id2119234_airaid");
if(!$conn){
	echo " Connection to database failed<br>";
}
else{
	echo "Connection to database successful<br>";
}

/*$request = $_GET["inc"];
if($request === "1" ){
   $_SESSION['eunits']++;
   $eunits = $_SESSION['eunits'];
   $ebill = $eunits*1.45;
   
}*/

if(date('Hi') == $time){
 $sql = "INSERT INTO electricity (edate,eu,eb)
 VALUES (NOW(),$eunits,$ebill)";
 $result=mysqli_query($conn,$sql);
 if ($conn->query($sql) == true) {
    echo "<br>New record created successfully<br>";
    $_SESSION['eunits'] = 0; 
    $eunits = $_SESSION['eunits'];
 }
 else {
    echo "failed to insert <br>";
 }
 $conn->close();
}

?>