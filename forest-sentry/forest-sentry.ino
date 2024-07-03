#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <ArduinoJson.h> 
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

//DHT11 Sensor
#define DHTPIN D3     
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ-2 Sensor
#define MQ2PIN A0

// YL-38 Rain Sensor
#define RAINPIN D2

// Definir pines para GPS
static const int GPS_RXPin = D4;  // Pin para recibir datos del GPS
static const int GPS_TXPin = D5;  // Pin para enviar datos al GPS
static const uint32_t GPSBaud = 9600;

// Crear objeto TinyGPS++
TinyGPSPlus gps;

// Crear objeto SoftwareSerial
SoftwareSerial gpsSerial(GPS_RXPin, GPS_TXPin);

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "iPhone Josue Montecinos"
#define WLAN_PASS       "quetimporta"

/************************* Server *********************************/
#define SERVER_URL      "http://tu-servidor.com/api/datos"  // URL del servidor donde se enviarán los datos

/*************************** Sketch Code ************************************/


double latitud = 0.0;
double longitud = 0.0;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(GPSBaud);  // Comunicación con el módulo GPS
  dht.begin();
  Serial.println("GPS Test iniciado");
  //****************************************** Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}

String nmeaSentence = "";
bool sentenceStart = false;

void loop() {
  // Read from sensors
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int smokeLevel = analogRead(MQ2PIN);
  int rainStatus = digitalRead(RAINPIN);

  // Evaluar el nivel de alerta
  int alertLevel = evaluateAlertLevel(temperature, humidity, smokeLevel, rainStatus);

  // Leer datos del GPS
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
    char c = gpsSerial.read();// Iniciar la captura de la oración al encontrar el signo '$'
    if (c == '$') {
      sentenceStart = true;
      nmeaSentence = ""; // Reiniciar la oración
    }

    // Si la captura ha comenzado, acumula los caracteres
    if (sentenceStart) {
      nmeaSentence += c;
    }

    // Al encontrar el fin de línea, procesar la oración completa
    if (c == '\n' && sentenceStart) {
      sentenceStart = false;
      Serial.print("Cadena NMEA: ");
      Serial.println(nmeaSentence);
    }

  }
  // Si se ha obtenido una nueva localización, mostrarla
  if (gps.location.isUpdated()) {
    Serial.print("Latitud: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitud: ");
    Serial.println(gps.location.lng(), 6);
  }

  // Preparar el JSON con los datos
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["humidity"] = humidity;
  jsonDoc["temperature"] = temperature;
  jsonDoc["smokeLevel"] = smokeLevel;
  jsonDoc["rainStatus"] = rainStatus;
  jsonDoc["alertLevel"] = alertLevel;
  jsonDoc["latitud"] = latitud;
  jsonDoc["longitud"] = longitud;

  String jsonData;
  serializeJson(jsonDoc, jsonData);


  Serial.println("Temperatura: "+ String(temperature));
  Serial.println("Humedad: " + String(humidity));
  Serial.println("Nivel de Gas: " + String(smokeLevel));
  Serial.println("Lluvia: " + interpretRainSensorDigital(rainStatus));


  // Enviar los datos al servidor
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, SERVER_URL);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      // Serial.println(response);
    } else {
      Serial.print("Error en el envío: ");
      // Serial.println(httpResponseCode);
    }
    http.end();
  }
  delay(1000);  // Esperar un minuto antes de enviar el siguiente conjunto de datos
}

String interpretRainSensorDigital(int sensor) {
    // Interpretar el valor y retornar la cadena correspondiente
    if (sensor == 1) {
        return "w:day-sunny"; // Sin lluvia
    } else {
        return "w:rain"; // Lluvia
    }
}

// Función para evaluar el nivel de alerta
int evaluateAlertLevel(float temperature, float humidity, int gasLevel, int rainStatus) {
     if ((temperature >= 30 && temperature <= 35) || (humidity <= 40 && humidity > 30) || (gasLevel >= 300 && gasLevel <= 400) || rainStatus == 1) {
        return 2; // Naranja: Riesgo Moderado
    } else {
        return 1; // Verde: Bajo Riesgo
    }
}