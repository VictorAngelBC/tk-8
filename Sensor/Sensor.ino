/*

    VCC  -> 5V
    GND  -> GND
    DATA -> Pin 4  (con resistencia 10k)

*/

#include <DHT.h>

#define DHT_PIN   4      
#define DHT_TYPE  DHT11

DHT dht(DHT_PIN, DHT_TYPE);

unsigned long contador      = 0;
unsigned long ultimaLectura = 0;
const unsigned int INTERVALO_MS = 2000;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); 
  dht.begin();
  delay(2000);
}

void loop() {
  if (millis() - ultimaLectura >= INTERVALO_MS) {
    ultimaLectura = millis();
    contador++;

    float hum  = dht.readHumidity();
    float temp = dht.readTemperature();

    if (isnan(hum) || isnan(temp)) {
      Serial.println(F("# ERROR: fallo lectura DHT11"));
      return;
    }

    float presion = 1013.25 + (float)(random(-30, 30)) / 10.0;

    float altitud = 44330.0 * (1.0 - pow(presion / 1013.25, 0.1903));

    Serial.print(contador);
    Serial.print(',');
    Serial.print(temp, 2);
    Serial.print(',');
    Serial.print(presion, 2);
    Serial.print(',');
    Serial.print(hum, 2);
    Serial.print(',');
    Serial.println(altitud, 2);
  }
}
