#include <ESP8266WiFi.h>

SoftwareSerial SerialESP8266(3,8); // RX, TX
const char* ssid = "camilo";
const char* password = "12345678";

const char* host = "www.example.com";


void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}


void loop()
{
  // Declaramos o instanciamos un cliente que se conectará al Host
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  // Intentamos conectarnos
  if (client.connect(host, 80))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print(String("GET /") + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );

    Serial.println("[Response:]");
    // Mientras la conexion perdure
    while (client.connected())
    {
      // Si existen datos disponibles
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    // Una vez el servidor envia todos los datos requeridos se desconecta y el programa continua
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);
}
