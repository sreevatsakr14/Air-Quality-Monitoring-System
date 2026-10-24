#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// ================= DHT22 =================
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ================= MQ2 =================
#define MQ_PIN 34

// ================= GP2Y1010 =================
#define DUST_LED_PIN 14
#define DUST_SENSOR_PIN 35

// ================= WiFi =================
const char* ssid = "Vatsa";
const char* password = "vatsa223";

// ================= ThingSpeak =================
String apiKey = "U9OEFZXPGNB1I951";

// ================= VARIABLES =================
float temperature, humidity;
int gasValue;
float dustDensity;
int AQI;

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(DUST_LED_PIN, OUTPUT);
  digitalWrite(DUST_LED_PIN, HIGH);

  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi FAILED!");
  }
}

// ================= DUST FUNCTION =================
float readDust() {
  digitalWrite(DUST_LED_PIN, LOW);   // LED ON
  delayMicroseconds(280);

  int raw = analogRead(DUST_SENSOR_PIN);

  delayMicroseconds(40);
  digitalWrite(DUST_LED_PIN, HIGH);  // LED OFF

  delayMicroseconds(9680);

  float voltage = raw * (3.3 / 4095.0);

  float dust = (voltage - 0.1) * 1000; // approx µg/m3
  if (dust < 0) dust = 0;

  return dust;
}

// ================= LOOP =================
void loop() {

  // ----- Read Sensors -----
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  gasValue = analogRead(MQ_PIN);

  dustDensity = readDust();

  // ----- AQI Calculation -----
  AQI = (dustDensity * 0.6) + (gasValue * 0.2) + (temperature * 0.2);

  // ----- Serial Output -----
  Serial.println("------ AQI DATA ------");
  Serial.println("Temp: " + String(temperature));
  Serial.println("Humidity: " + String(humidity));
  Serial.println("Gas (MQ2): " + String(gasValue));
  Serial.println("Dust (PM2.5): " + String(dustDensity));
  Serial.println("AQI: " + String(AQI));
  Serial.println("----------------------");

  // ----- Send to ThingSpeak -----
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String url = "http://api.thingspeak.com/update?api_key=" + apiKey +
                 "&field1=" + String(temperature) +
                 "&field2=" + String(humidity) +
                 "&field3=" + String(gasValue) +
                 "&field4=" + String(dustDensity) +
                 "&field5=" + String(AQI);

    Serial.println("Sending to ThingSpeak...");
    Serial.println(url);

    http.begin(url);

    int httpCode = http.GET();

    Serial.print("HTTP Response: ");
    Serial.println(httpCode);

    if (httpCode == 200) {
      Serial.println("Upload SUCCESS ✅");
    } else {
      Serial.println("Upload FAILED ❌");
    }

    http.end();
  }

  delay(30000);
}