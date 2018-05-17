<?php
require_once 'DaosCaneca.php';
require_once 'Caneca.php';

$caneca = new Caneca();
$db = new DaosCaneca("root","");

if( isset($_GET['bandera'])){
	$bandera=$_GET['bandera'];
	echo $bandera;
	
	if(is_null($db->Obtener($_GET['id']))){
		$caneca->__SET('latitud', $_GET['latitud']);
		$caneca->__SET('longitud', $_GET['longitud']);
        $caneca->__SET('lleno', $_GET['lleno']);
		$db->Registrar($caneca);
	}else{
		$caneca = $db->Obtener($_GET['id']);
		$caneca->__SET('lleno', $_GET['lleno']);
		$db->Registrar($caneca);
	}
}else{
	$tamArray = sizeOf($db->Listar());
	echo"<!DOCTYPE html>";
	echo"<html>";
	echo"  <head>";
	echo"	<meta name='viewport' content='initial-scale=1.0, user-scalable=no'>";
	echo"	<meta charset='utf-8'>";
	echo"	<link rel='stylesheet' type='text/css' href='estilo.css'>";
	echo"	<script src='funcion.js'></script>";
	echo"	<title>Waypoints in directions</title>";
	echo"  </head>";
	echo"  <body>";
	echo"	<div id='map'></div>";
	echo"	<div id='right-panel'>";
	echo"	<div>";
	echo"	<select id='start' style='visibility:hidden'>";
	for($i=0;$i<1;$i++){
		if($db->Listar()[$i]->lleno==1){
			echo"	  <option value='".$db->Listar()[$i]->latitud.",".$db->Listar()[$i]->longitud."'selected>".$i."</option>";
		}
	}
	echo"	</select>";
	echo"	<select multiple id='waypoints' style='visibility:hidden'>";
	for($i=1;$i<$tamArray-1;$i++){
		if($db->Listar()[$i]->lleno==1){
			echo"	  <option value='".$db->Listar()[$i]->latitud.",".$db->Listar()[$i]->longitud."'selected>".$i."</option>";	
		}
	}
	echo"	</select>";
	echo"	<select id='end' style='visibility:hidden'>";
	for($i=$tamArray-1;$i<$tamArray;$i++){
		if($db->Listar()[$i]->lleno==1){
			echo"	  <option value='".$db->Listar()[$i]->latitud.",".$db->Listar()[$i]->longitud."'selected>".$i."</option>";	
		}
	}	
	echo"	</select>";
	echo"	<br>";
	echo"	  <input value='Generar' type='submit' id='submit'>";
	echo"	</div>";
	echo"	<div id='directions-panel'></div>";
	echo"	</div>";
	echo"	<script async defer";
	echo"	src='https://maps.googleapis.com/maps/api/js?key=AIzaSyDK7uYFVRUksnrOsYE1JyeHOQu-qJDeFkU&callback=initMap'>";
	echo"	</script>";
	echo"  </body>";
	echo"</html>";
}
?>