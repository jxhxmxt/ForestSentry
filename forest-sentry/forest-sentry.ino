#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <ArduinoJson.h> 

//DHT11 Sensor
#define DHTPIN D3     
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ-2 Sensor
#define MQ2PIN A0

// YL-38 Rain Sensor
#define RAINPIN D2


/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "<wlan-ssid>"
#define WLAN_PASS       "<wlan-pass>"

/************************* Server *********************************/
#define SERVER_URL      "http://tu-servidor.com/api/datos"  // URL del servidor donde se enviarán los datos

/*************************** Sketch Code ************************************/

void setup() {
  Serial.begin(115200);
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
  dht.begin();
}

String nmeaSentence = "";
String latAndLon = "";
bool sentenceStart = false;

void loop() {
  // Read from sensors
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int smokeLevel = analogRead(MQ2PIN);
  int rainStatus = digitalRead(RAINPIN);
  double latitud = 0.0;
  double longitud = 0.0;

  // Evaluar el nivel de alerta
  int alertLevel = evaluateAlertLevel(temperature, humidity, smokeLevel, rainStatus);
  
  // Leer datos del GPS
  while (Serial.available()) {
    char c = Serial.read();

    // Iniciar la captura de la oración al encontrar el signo '$'
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
      processNMEASentence(nmeaSentence);
    }
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
  Serial.println("NMEASentence: " + nmeaSentence);
  Serial.println("Lat and Lon: " + latAndLon);


  // Enviar los datos al servidor
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, SERVER_URL);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.print("Error en el envío: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  delay(60000);  // Esperar un minuto antes de enviar el siguiente conjunto de datos
}

void processNMEASentence(String sentence) {
  double lat = 0.0;
  double lon = 0.0;

  if (sentence.startsWith("$GPGGA") || sentence.startsWith("$GPGLL") || sentence.startsWith("$GPRMC")) {
    // Divide la oración en campos usando la coma como delimitador
    int fieldIndex = 0;
    String fields[15]; // Preparado para hasta 15 campos

    int startIndex = 0;
    int endIndex = -1;
    while ((endIndex = sentence.indexOf(',', startIndex)) != -1) {
      fields[fieldIndex++] = sentence.substring(startIndex, endIndex);
      startIndex = endIndex + 1;
    }
    fields[fieldIndex] = sentence.substring(startIndex); // Último campo

    // Extrae los campos relevantes dependiendo del tipo de oración
    String latitude, latDirection, longitude, longDirection;
    if (sentence.startsWith("$GPGGA")) {
      latitude = fields[2];
      latDirection = fields[3];
      longitude = fields[4];
      longDirection = fields[5];
    } else if (sentence.startsWith("$GPGLL")) {
      latitude = fields[1];
      latDirection = fields[2];
      longitude = fields[3];
      longDirection = fields[4];
    } else if (sentence.startsWith("$GPRMC")) {
      latitude = fields[3];
      latDirection = fields[4];
      longitude = fields[5];
      longDirection = fields[6];
    }

    // Convierte la latitud y la longitud a grados decimales
    lat = convertToDecimal(latitude, latDirection);
    lon = convertToDecimal(longitude, longDirection);

    // Prepara los datos para la publicación
    latAndLon = String(lat, 6) + "," + String(lon, 6); // 6 dígitos de precisión

    // Actualiza las variables globales
    latitud = lat;
    longitud = lon;
  }
}

double convertToDecimal(String degreeMinute, String direction) {
  double rawValue = degreeMinute.toDouble();
  double degrees = int(rawValue / 100);
  double minutes = rawValue - (degrees * 100);
  double decimal = degrees + (minutes / 60);

  if (direction == "S" || direction == "W") {
    decimal *= -1;
  }

  return decimal;
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