#include <DHT.h>

// Definir los pines de los sensores
#define DHTPIN 8
#define DHTTYPE DHT11
#define soilMoisturePin A0
#define lightSensorPin 7
#define waterLevelPin A1  // Nuevo pin para el sensor de nivel de agua

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(lightSensorPin, INPUT);
}

void loop() {
  // Leer los sensores
  float humedadAmbiente = dht.readHumidity();
  float temperatura = dht.readTemperature();
  int valorHumedadSuelo = map(analogRead(soilMoisturePin), 0, 1023, 100, 0);
  int estadoLuz = digitalRead(lightSensorPin);
  bool luzDetectada = (estadoLuz == LOW);
  
  // Leer el nivel de agua
  int valorNivelAgua = map(analogRead(waterLevelPin), 0, 1023, 0, 100);  // Mapeamos el valor de 0 a 100

  // Crear un objeto JSON
  String jsonData = "{";
  jsonData += "\"humedadAmbiente\":";
  jsonData += humedadAmbiente;
  jsonData += ",\"temperatura\":";
  jsonData += temperatura;
  jsonData += ",\"humedadSuelo\":";
  jsonData += valorHumedadSuelo;
  jsonData += ",\"luzDetectada\":";
  jsonData += luzDetectada ? "true" : "false";
  jsonData += ",\"nivelAgua\":";
  jsonData += valorNivelAgua;
  jsonData += "}";

  // Enviar el JSON por el puerto serie
  Serial.println(jsonData);

  delay(2000);
}
