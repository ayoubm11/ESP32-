#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

const char* ssid = "SSID_WIFI"; // Remplacez par le nom de votre réseau Wi-Fi
const char* password = "motdepasse"; // Remplacez par le mot de passe de votre réseau Wi-Fi

#define HUMIDITY_PIN 34
#define POMPE_PIN 32

WebServer server(80);

const float HUMIDITY_THRESHOLD = 50.0;

// Route pour lecture d'humidité
void handleHumidity() {
  int raw = analogRead(HUMIDITY_PIN);
  float humidity = map(raw, 0, 4095, 100, 0);

  StaticJsonDocument<200> json;
  json["humidity"] = humidity;

  String response;
  serializeJson(json, response);
  server.send(200, "application/json", response);
}

// Route pour lancer arrosage manuel
void handleWater() {
  Serial.println("Commande d’arrosage reçue !");
  digitalWrite(POMPE_PIN, HIGH);
  delay(3000);
  digitalWrite(POMPE_PIN, LOW);
  server.send(200, "text/plain", "Arrosage manuel déclenché");
}

// Route pour envoyer une position GPS simulée
void handleLocation() {
  StaticJsonDocument<200> json;
  json["latitude"] = 33.5731;   // Casablanca
  json["longitude"] = -7.5898;

  String response;
  serializeJson(json, response);
  server.send(200, "application/json", response);
}

void setup() {
  Serial.begin(115200);
  pinMode(POMPE_PIN, OUTPUT);
  digitalWrite(POMPE_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connexion...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnecté !");
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());

  server.on("/humidity", HTTP_GET, handleHumidity);
  server.on("/water", HTTP_GET, handleWater);
  server.on("/location", HTTP_GET, handleLocation);

  server.begin();
  Serial.println("Serveur lancé !");
}

void loop() {
  server.handleClient();

  int raw = analogRead(HUMIDITY_PIN);
  float humidity = map(raw, 0, 4095, 100, 0);

  Serial.print("Humidité détectée : ");
  Serial.print(humidity);
  Serial.println(" %");

  if (humidity <= HUMIDITY_THRESHOLD) {
    Serial.println("Humidité basse détectée. Activation de la pompe...");
    digitalWrite(POMPE_PIN, HIGH);
    delay(10000);
    digitalWrite(POMPE_PIN, LOW);
    Serial.println("Pompe désactivée.");
  }

  delay(5000);
}
