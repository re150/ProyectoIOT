#include <WiFi.h>
#include <HTTPClient.h>

const char* red = "Totalplay-2.4G-c400"; // Nombre de la red WiFi
const char* password = "ZbsDPf8yU97RYD9t"; // Contraseña de la red WiFi
const char* serverUrl = "http://192.168.100.9:8080/api/datos"; // URL del endpoint de Spring Boot

void setup() {
  Serial.begin(9600);
  WiFi.begin(red, password); // Conectar a la red WiFi

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {   // Verificar el estado de la conexión WiFi

    HTTPClient http;    // Declarar objeto de clase HTTPClient

    http.begin(serverUrl);      // Especificar el destino de la solicitud
    http.addHeader("Content-Type", "application/json");  // Especificar el encabezado content-type

    int sensorValue = 45; // Ejemplo de lectura de un sensor
    String jsonData = "{\"valor\":" + String(sensorValue) + "}"; // Datos JSON

    Serial.println("Enviando solicitud HTTP POST a " + String(serverUrl));
    int httpResponseCode = http.POST(jsonData);   // Enviar la solicitud

    if (httpResponseCode > 0) {
      String response = http.getString();                       // Obtener la respuesta a la solicitud
      Serial.println("Código de respuesta HTTP: " + String(httpResponseCode));   // Imprimir código de respuesta
      Serial.println("Respuesta del servidor: " + response);           // Imprimir respuesta de la solicitud
    } else {
      Serial.print("Error en la solicitud: ");
      Serial.println(httpResponseCode);
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }

    http.end();  // Cerrar la conexión

    delay(10000);  // Enviar una solicitud cada 10 segundos
  } else {
    Serial.println("Error en la conexión WiFi");
  }
}
