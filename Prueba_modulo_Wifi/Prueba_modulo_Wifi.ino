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
  BT1.print("AT+CIFSR\r\n"); // enviar el comando al ESP8266
  int contador = 0;
  String ip;
  while( (time+1000) > millis()) {//mientras no haya timeout
    while(BT1.available()) {//mientras haya datos por leer
      // Leer los datos disponibles
      char c = BT1.read(); // leer el siguiente caracter
      ip = Serial.print(c)+ip;  
    }
  }
  Serial.println(ip.substring(ip.indexOf("+CIFSR:STAIP,"), ip.indexOf("+CIFSR:STAMAC")));  
}

void setup(){
  Serial.begin(9600);
  configWIFI(); //Serial 115200
}

void loop(){
  // Iniciar módulo WIFI ESP8266
  runWIFI();
}

