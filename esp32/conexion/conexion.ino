#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include "HT_SSD1306Wire.h"

const char* red = "Totalplay-2.4G-c400"; 
const char* password = "ZbsDPf8yU97RYD9t"; 
const char* serverUrl = "http://192.168.100.9:8080/api/datos"; 


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
  WiFi.begin(red, password); // Conectar a la red WiFi

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a WiFi");

  // sencor  y pantalla
  Serial.println(F("DHTxx test!"));

  dht.begin();
  
  display.init();
  display.clear();
  display.display();

}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    
    // Display error message on OLED display
    display.clear();
    display.drawString(0, 0, "Failed to read from DHT sensor!");
    display.display();
    
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahrenheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  // Display the temperature and humidity on the OLED display.
  display.clear();
  display.setLogBuffer(5, 30); // Adjust the log buffer size if necessary
  display.drawString(0, 0, "Humidity: " + String(h) + "%");
  display.drawString(0, 10, "Temperature: " + String(t) + "°C");
  display.drawString(0, 20, "Temperature: " + String(f) + "°F");
  display.drawString(0, 30, "Heat index: " + String(hic) + "°C");
  display.drawString(0, 40, "Heat index: " + String(hif) + "°F");
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
