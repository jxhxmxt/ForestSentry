#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <DHT.h>

//DHT11 Sensor
#define DHTPIN D3     
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ-2 Sensor
#define MQ2PIN A0

// YL-38 Rain Sensor
#define RAINPIN D2


/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "iPhone Josue Montecinos"
#define WLAN_PASS       "quetimporta"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "jcmbass"
#define AIO_KEY         "aio_Jwmh33Md52Rryx4TpcJCGLZQaH8S"
/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiClientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds for Publishing***************************************/
Adafruit_MQTT_Publish temperatureFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/feed_temperatura");
Adafruit_MQTT_Publish humidityFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/feed_humedad");
Adafruit_MQTT_Publish gasFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/feed_gas");
Adafruit_MQTT_Publish rainFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/feed_lluvia");
Adafruit_MQTT_Publish gpsFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/feed_gps");
Adafruit_MQTT_Publish alertLevelFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/feed_alert_level");

/****************************** Feeds for Subscribing***************************************/

/*************************** Sketch Code ************************************/

void setup() {
  dht.begin();
  Serial.begin(9600);
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
String latAndLon = ""; //Latitud y Longitud de UCA
bool sentenceStart = false;

void loop() {
  MQTT_connect();
  mqtt.processPackets(10000);
  if(! mqtt.ping()) {   // ping the server to keep the mqtt connection alive
    mqtt.disconnect();
  }

  // Read from sensors
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int gasLevel = analogRead(MQ2PIN);
  int rainStatus = digitalRead(RAINPIN);

  // Evaluar el nivel de alerta
  int alertLevel = evaluateAlertLevel(temperature, humidity, gasLevel, rainStatus);
  
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

  // Publish to Adafruit IO
  temperatureFeed.publish(temperature);
  humidityFeed.publish(humidity);
  gasFeed.publish(gasLevel);
  rainFeed.publish(interpretRainSensorDigital(rainStatus).c_str());
  gpsFeed.publish(String("GPS Location: " + latAndLon).c_str());
  alertLevelFeed.publish(alertLevel);


  Serial.println("Temperatura: "+ String(temperature));
  Serial.println("Humedad: " + String(humidity));
  Serial.println("Nivel de Gas: " + String(gasLevel));
  Serial.println("Lluvia: " + interpretRainSensorDigital(rainStatus));
  Serial.println("NMEASentence: " + nmeaSentence);
  Serial.println("Lat and Lon: " + latAndLon);


  delay(3000);
}

// Function to connect and reconnect as necessary to the MQTT server.
void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;}
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 10 seconds...");
       mqtt.disconnect();
       delay(10000);  // wait 10 seconds
       retries--;
       if (retries == 0) {       // basically die and wait for WDT to reset me
         while (1);}}
  Serial.println("MQTT Connected!");
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