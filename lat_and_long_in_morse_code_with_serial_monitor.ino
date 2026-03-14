#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(8, 9);
TinyGPSPlus gps;

#define RELAY_PIN 7
#define DOT_DURATION 200  // ms
#define DASH_DURATION 600
#define GAP_DURATION 200
#define LETTER_GAP 600

// Convert character to Morse code
String toMorse(char c) {
  switch (c) {
    case '0': return "-----";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    case '.': return ".-.-.-";
    case '-': return "-....-";
    default: return "";
  }
}

// Function to activate relay for each Morse symbol
void transmitMorse(String text) {
  for (int i = 0; i < text.length(); i++) {
    String morse = toMorse(text[i]);
    if (morse.length() > 0) {
      for (int j = 0; j < morse.length(); j++) {
        digitalWrite(RELAY_PIN, HIGH); // relay ON
        if (morse[j] == '.') {
          delay(DOT_DURATION);
        } else if (morse[j] == '-') {
          delay(DASH_DURATION);
        }
        digitalWrite(RELAY_PIN, LOW);  // relay OFF between parts
        delay(GAP_DURATION);
      }
      delay(LETTER_GAP); // pause between letters
    }
  }
}

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());

    if (gps.location.isUpdated()) {
      float lat = gps.location.lat();
      float lon = gps.location.lng();

      String latStr = String(lat, 6);
      String lonStr = String(lon, 6);

      Serial.println("Latitude: " + latStr);
      Serial.println("Longitude: " + lonStr);

      Serial.println("Transmitting latitude in Morse...");
      transmitMorse(latStr);
      delay(1000);
      Serial.println("Transmitting longitude in Morse...");
      transmitMorse(lonStr);
      Serial.println("-----------------------");
    }
  }
}
