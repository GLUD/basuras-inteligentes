// Wifi
#include <SoftwareSerial.h>
#include <NewPing.h>
#include <TinyGPS.h>
SoftwareSerial BT1(9, 8); // RX | TX
SoftwareSerial serial1(10, 11); // RX, TX
TinyGPS gps1;

const int Trigger = 4;   //Pin digital 2 para el Trigger del sensor
const int Echo = 3;   //Pin digital 3 para el Echo del sensor
// Variables de la caneca
const long dMax = 8;
const long dMin = 9;
bool lleno = 0;
double latitud;
double longitud;

void setup() {
  serial1.begin(9600);
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  //configWIFI(); //Serial 115200
}

void loop(){
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm

  if(d<=3){
    lleno == 1;
  }
  
  delay(100);          //Hacemos una pausa de 100ms

  // Iniciar módulo WIFI ESP8266
  //runWIFI();

  Serial.print(lleno);
  
  bool recebido = false;

  while (serial1.available()) {
     char cIn = serial1.read();
     recebido = gps1.encode(cIn);
  }

  if (recebido) {
     //Latitude e Longitude
     long latitude, longitude;
     unsigned long idadeInfo;
     gps1.get_position(&latitude, &longitude, &idadeInfo);     

     if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 6);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }
     latitud=float(latitude) / 100000;
     longitud=float(longitude) / 100000;

     if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
        Serial.print("Idade da Informacao (ms): ");
        Serial.println(idadeInfo);
     }
  }
  Serial.print(latitud);
  Serial.print(longitud);
}

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
  //sendData("AT+CWJAP=\"UDNet_Eventos\",\"hackathon_2018\"\r\n",8000); //SSID y contraseña para unirse a red 
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

 Serial.println("Estableciendo conex´on con el servidor");



 gateway="192.168.173.1/?bandera=0&id=0&latitud=1.0&longitud=2.0&lleno=0";
 //gateway="www.aprende-web.net";

 int variable1=364;
 float variable2=3.14;
 
 BT1.println("AT+CIPSTART=\"TCP\",\"" + gateway + "\",80");

 
if( BT1.find("OK"))
      { 
        Serial.println("Conexion establecida con el servidor");
      }
 /*
//Armamos el encabezado de la peticion http
  String peticionHTTP= "GET 192.168.173.1/?bandera=0&id=0&latitud=1.0&longitud=2.0&lleno=0 HTTP/1.1\r\n";
  //peticionHTTP=peticionHTTP+String(variable1)+"&b="+String(variable2)+" HTTP/1.1\r\n";
  //peticionHTTP=peticionHTTP+"Host: 192.163.173.1\r\n\r\n";
  Serial.println("Peticion HTTP: "+ peticionHTTP);
  //Enviamos el tamaño en caracteres de la peticion http:  
  BT1.print("AT+CIPSEND=");
  BT1.println(peticionHTTP.length());
  Serial.println("Peticion en proceso");
  //esperamos a ">" para enviar la petcion  http
  /*if(BT1.find(">")) // ">" indica que podemos enviar la peticion http
  {
    Serial.println("Enviando HTTP . . .");
    BT1.println(peticionHTTP);
  //}
  */
}
