// Wifi
#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 8); // RX | TX

void sendData(String comando, const int timeout){
    /*
  Enviar comando al esp8266 y verificar la respuesta del módulo, todo esto dentro del tiempo timeout
  */
  long int time = millis(); // medir el tiempo actual para verificar timeout
  BT1.print(comando); // enviar el comando al ESP8266
  while( (time+timeout) > millis()) {//mientras no haya timeout
    while(BT1.available()) {//mientras haya datos por leer
      // Leer los datos disponibles
      char c = BT1.read(); // leer el siguiente caracter
      Serial.print(c);
    }
  }
  return;
}

void configWIFI(){
  Serial.begin(9600);
  BT1.begin(9600);
  sendData("AT+RST\r\n",2000);      // resetear módulo
  sendData("AT+CWMODE=1\r\n",1000); // configurar como cliente
  sendData("AT+CWJAP=\"Pepe\",\"pepitopp\"\r\n",8000); //SSID y contraseña para unirse a red 
  sendData("AT+CIFSR\r\n",1000);    // obtener dirección IP
  sendData("AT+CIPMUX=1\r\n",1000); // configurar para multiples conexiones
  sendData("AT+CIPSERVER=1,80\r\n",1000);         // servidor en el puerto 80
}

void runWIFI(){
  long int time = millis(); // medir el tiempo actual para verificar timeout
  //BT1.print("AT+CIFSR\r\n"); // enviar el comando al ESP8266
  BT1.print("AT+CIPSTA?\r\n");
  int contador = 0;
  String ip;
  while( (time+1000) > millis()) {//mientras no haya timeout
    while(BT1.available()) {//mientras haya datos por leer
      // Leer los datos disponibles
      char c = BT1.read(); // leer el siguiente caracter
      Serial.print(c);
      ip = ip+c;  
    }
  }

  int pos1=0, pos2=0;
  Serial.println("Imprimiendo IP :"+ip+ "******");
  Serial.print("Indice 1:");
  pos1=ip.indexOf("gateway");
  pos1+=9;
  Serial.println(pos1);
  Serial.print("Indice 2:");
  pos2=ip.indexOf("netmask");
  pos2-=11;
  Serial.println(pos2);
  String gateway = ip.substring(pos1,pos2);
  Serial.println("gateway ACTUAL:" + gateway);
  //Serial.println(ip.substring(ip.indexOf("+CIFSR:STAIP,"), ip.indexOf("+CIFSR:STAMAC")));
  Serial.println("FIN Imprimiendo IP");

//Armamos el encabezado de la peticion http
  String peticionHTTP= "GET /?bandera=0&id=1&latitud=1.0&longitud=2.0&lleno=0";
  peticionHTTP=peticionHTTP+String(variable1)+"&b="+String(variable2)+" HTTP/1.1\r\n";
  peticionHTTP=peticionHTTP+"Host: "+gateway+"\r\n\r\n";

  //Enviamos el tamaño en caracteres de la peticion http:  
  SerialESP8266.print("AT+CIPSEND=");
  SerialESP8266.println(peticionHTTP.length());

  //esperamos a ">" para enviar la petcion  http
  if(SerialESP8266.find(">")) // ">" indica que podemos enviar la peticion http
  {
    Serial.println("Enviando HTTP . . .");
    SerialESP8266.println(peticionHTTP);
  }
  
}

void setup(){
  Serial.begin(9600);
  configWIFI(); //Serial 115200
}

void loop(){
  // Iniciar módulo WIFI ESP8266
  runWIFI();
}

