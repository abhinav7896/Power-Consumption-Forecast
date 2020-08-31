<?php
$conn = new mysqli("localhost", "id2119234_abhinav", "ps3isfun", "id2119234_airaid");
if(!$conn){
	echo " Connection Failed<br>";
}
else{
	echo "Connection successful<br>";
}
$sql1="SELECT avg(eu) from electricity";
    $result1=mysqli_query($conn,$sql1);
$row2=mysqli_fetch_array($result1);

$sql2="SELECT edate,Pulses,eu,eb from electricity";
$result2=mysqli_query($conn,$sql2);
$row3=mysqli_fetch_array($result2);

$res=$row2[0];
$res1=$res*30;
$res2=$res1*1.45;
echo "Estimated electicity units consumed              : ".$res1;
echo "<br><br>Estimated electricity bill for the month : Rs.".$res2."/-";


$conn->close();
?>