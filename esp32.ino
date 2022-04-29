#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

#include "DHT.h"
#define DHT_SENSOR_PIN  14 // ESP32 pin GIOP23 connected to DHT11 sensor
#define DHT_SENSOR_TYPE DHT11

#define DHTTYPE DHT11
// Nhiet do, Do am
int nhietDo=0;
int doAm=0;

// Initialise DHT sensor
//Provide the token generation process info.
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"


#define WIFI_SSID "Redmi Note 8"
#define WIFI_PASSWORD "00000000"

// Insert Firebase project API Key
#define API_KEY  "AIzaSyC3nL49UW4fwjni2Wk2UOnH2sy8xBOUQrI"
#define DATABASE_URL  "https://esp32-firebase-80d4f-default-rtdb.firebaseio.com/" 

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
const int ledPin=2;


 // Initialise DHT sensor
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("OK");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback; 
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  dht_sensor.begin(); 
} 

void loop(){
 
  float humi  = dht_sensor.readHumidity();   
  float Temperature = dht_sensor.readTemperature(); 
  //float tempF = dht_sensor.readTemperature(true);
  if (isnan(Temperature) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
  } 
  else {
    Firebase.RTDB.setString(&firebaseData,"/DHT11/Humid", humi);
    Firebase.RTDB.setString(&firebaseData,"/DHT11/Temperature", Temperature);
  }

  if(Firebase.RTDB.getString(&firebaseData,"/Led1Status")){
  firebaseData.stringData();
  Serial.println(firebaseData.stringData());
  
  if(firebaseData.stringData()=="1"){
    digitalWrite(32, HIGH);
    Serial.println("ON");
  }else {
    digitalWrite(32,LOW);
    Serial.println("OFF");
  }
  }

  if(Firebase.RTDB.getString(&firebaseData,"/Led2Status")){
  firebaseData.stringData();
  Serial.println(firebaseData.stringData());
  
  if(firebaseData.stringData()=="1"){
    digitalWrite(33, HIGH);
    Serial.println("ON");
  }else {
    digitalWrite(33, LOW);
    Serial.println("OFF");
  }
  }
}
