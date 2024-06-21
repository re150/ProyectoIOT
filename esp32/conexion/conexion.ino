#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include "HT_SSD1306Wire.h"

const char* red = "red"; 
const char* password = "contraseñan"; 
const char* serverUrl = "ip"; 


// censor
#define DHTPIN 21   
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

// Define the display instance.
#ifdef WIRELESS_STICK_V3
SSD1306Wire display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_64_32, RST_OLED);
#else
SSD1306Wire display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);
#endif

void setup() {
  Serial.begin(9600);
  WiFi.begin(red, password); 

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a WiFi");

  Serial.println(F("DHTxx test!"));

  dht.begin();
  
  display.init();
  display.clear();
  display.display();

}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    display.clear();
    display.drawString(0, 0, "Failed to read from DHT sensor!");
    display.display();
    
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Datos mandados a  spring boot: "));

  
  display.clear();
  display.setLogBuffer(5, 30); 
  display.drawString(0, 0, "Datos mandados a  spring boot ");
  display.drawString(0, 10, "Proyecto IOT" );
  display.drawString(0, 20, "Activo  ") ;
  display.display();

  //metodo post
     delay(2000);
    sendData(h,t,f,hic,hif);
}

void sendData (float h, float t ,float f,float hic, float hif){
   if (WiFi.status() == WL_CONNECTED) {   

    HTTPClient http;   

    http.begin(serverUrl);      
    http.addHeader("Content-Type", "application/json");  

    String jsonData = "{\"valorh\":" + String(h) + 
                    ",\"valort\":" + String(t) +
                    ",\"valorf\":" + String(f) +
                    ",\"valorhc\":" + String(hic) + 
                    ",\"valorhf\":" + String(hif) + 
                    "}"; 

   Serial.println("JSON Data to be sent: ");
   Serial.println(jsonData); 

    Serial.println("Enviando solicitud HTTP POST a " + String(serverUrl));
    int httpResponseCode = http.POST(jsonData); 

    if (httpResponseCode > 0) {
      String response = http.getString();                       
      Serial.println("Código de respuesta HTTP: " + String(httpResponseCode));   
      Serial.println("Respuesta del servidor: " + response);           
    } else {
      Serial.print("Error en la solicitud: ");
      Serial.println(httpResponseCode);
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }

    http.end();  

    delay(20000);  
  } else {
    Serial.println("Error en la conexión WiFi");
  }
}
