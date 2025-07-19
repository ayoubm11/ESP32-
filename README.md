
# 🌱 Code ESP32 - GreenLand

Ce fichier contient le code utilisé pour piloter un **ESP32** dans le cadre du projet **GreenLand**, un système d’arrosage automatique intelligent contrôlé à distance via une application mobile.

## 🔧 Fonctionnalités

- 🔍 Lecture de l’humidité du sol via un capteur capacitif.
- 🌧️ Déclenchement automatique de la pompe si l’humidité est inférieure au seuil.
- 💧 Arrosage manuel via une requête HTTP.
- 📡 Transmission des données via un serveur web intégré à l’ESP32.
- 🗺️ Simulation de la position GPS pour affichage dans une carte de l’application mobile.

## 📡 Points d’accès HTTP

| Route             | Méthode | Description                                |
|------------------|---------|--------------------------------------------|
| `/humidity`       | GET     | Retourne l’humidité du sol (en %)         |
| `/water`          | GET     | Déclenche un arrosage manuel (3 secondes) |
| `/location`       | GET     | Renvoie des coordonnées GPS simulées      |

## ⚙️ Connexions ESP32

| Composant                | Port ESP32 |
|--------------------------|------------|
| Capteur d’humidité       | GPIO 34    |
| Pompe (relais ou MOSFET) | GPIO 32    |
| Alimentation capteur     | 3.3V ou 5V |
| GND                      | GND        |

## 🧪 Exemple de sortie série

```
Connexion...
Connecté !
IP : 192.168.1.42
Serveur lancé !
Humidité détectée : 42.00 %
Humidité basse détectée. Activation de la pompe...
Pompe désactivée.
```

## 📝 Installation

1. Connectez l’ESP32 à votre PC.
2. Ouvrez le fichier `.ino` dans l’IDE Arduino.
3. Installez les bibliothèques nécessaires :
   - `WiFi.h`
   - `WebServer.h`
   - `ArduinoJson.h`
4. Remplacez les valeurs de `ssid` et `password` par celles de votre réseau Wi-Fi.
5. Téléversez le code.
6. Ouvrez le moniteur série (baud : **115200**).

## 📍 Localisation simulée

Le serveur retourne des coordonnées GPS fictives (Casablanca, Maroc) pour permettre l'affichage de la position du système dans l'application mobile.

## 👨‍💻 Auteurs

Projet développé dans le cadre de **GreenLand** – Application mobile d’arrosage intelligent.
