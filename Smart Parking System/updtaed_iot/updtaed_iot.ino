#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <NTPClient.h>;
#define FIREBASE_HOST "smart-parking-3387e-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "o8NnsbJ5aD8YgHK8SfB4buTOS6rZGS2TIjQLDKSv"
#define WIFI_SSID "1234" 
#define PASSWORD "12345678"
uint8_t arr[5];
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "in.pool.ntp.org", 19800,60000);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Connecting to Wifi");  
  WiFi.begin (WIFI_SSID, PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("=================================Connected to WiFi=================================");
  Serial.print("IP Address is");
  Serial.println(WiFi.localIP());
  Serial.println("=====================Attempting to connect to firebase database====================");
  Firebase.begin(FIREBASE_HOST);
  Serial.println("===============================Firebase connected==================================");
  pinMode(D0,INPUT);
  pinMode(D1,INPUT);
  pinMode(D2,INPUT);
  pinMode(D3,INPUT);
  pinMode(D4,INPUT);
  pinMode(D5,INPUT);
   timeClient.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  arr[0] = digitalRead(D0);
  arr[1] = digitalRead(D1);
  arr[2] = digitalRead(D2);
  arr[3] = digitalRead(D3);
  arr[4] = digitalRead(D4);
  arr[5] = digitalRead(D5);
  timeClient.update();

  
  if(!Firebase.failed()){
 
    Serial.println("Sensor 1");                               //sensor 1 code
    if(arr[0]==HIGH){
      Firebase.setString("park/slot/Sensor1", "Available");
      
      
      Serial.println("HIGH");
    }
    else{
      Firebase.setString("park/slot/Sensor1","Not Available");
       
       int mm = timeClient.getMinutes();
        
       String m= String(mm);
   Firebase.setString("firstfloor/sensor1exit", m);
      Serial.println("LOW");
    }
    Serial.println("Sensor 2");                                 //sensor 2 code
    if(arr[1]==HIGH){
      Firebase.setString("park/slot/Sensor2","Available");
      Serial.println("HIGH");
    }
    else{
      Firebase.setString("park/slot/Sensor2","Not Available");
       
       int sm = timeClient.getMinutes();
       
       String m1= String(sm);
   Firebase.setString("firstfloor/sensor2exit", m1);
      Serial.println("LOW");
    }Serial.println("Sensor 3");                                // sensor 3 code
    if(arr[2]==HIGH){
      Firebase.setString("park/slot/Sensor3","Available");
      Serial.println("HIGH");
    }
    else{
      Firebase.setString("park/slot/Sensor3","Not Available");
      Serial.println("LOW");
       int sm1 = timeClient.getMinutes();
       
       String m2= String(sm1);
       Firebase.setString("firstfloor/sensor3exit", m2);
    }Serial.println("Sensor 4");                                  // sensor 4 code
    if(arr[3]==HIGH){
      Firebase.setString("park/slot/Sensor4", "Available");
      Serial.println("HIGH");
    }
    else{
      Firebase.setString("park/slot/Sensor4","Not Available");
      Serial.println("LOW");
       int sm2 = timeClient.getMinutes();
       
       String m3= String(sm2);
       Firebase.setString("firstfloor/sensor4exit", m3);
    }Serial.println("Sensor 5");                       // sensor 5 code
    if(arr[4]==HIGH){
      Firebase.setString("park/slot/Sensor5", "Available");
      Serial.println("HIGH");
    }
    else{
      Firebase.setString("park/slot/Sensor5","Not Available");
      Serial.println("LOW");
      int sm3 = timeClient.getMinutes();
      
       
       String m4= String(sm3);
       Firebase.setString("firstfloor/sensor5exit", m4);
    }Serial.println("Sensor 6");                      // sensor 6 code
     if(arr[5]==HIGH){
      Firebase.setString("park/slot/Sensor6", "Available");
      Serial.println("HIGH");
      
    }
    else{
      Firebase.setString("park/slot/Sensor6","Not Available");
      Serial.println("LOW");
       int sm4 = timeClient.getMinutes();
       
       String m5= String(sm4);
      Firebase.setString("firstfloor/sensor6exit", m5);
    }
        if(arr[0]==LOW&&arr[1]==LOW&&arr[2]==LOW){
      Firebase.setString("Places/area1/location", "Not Available");
    }
    else{
      Firebase.setString("Places/area1/location", "Available");
    }
    if(arr[3]==LOW&&arr[4]==LOW&&arr[5]==LOW){
      Firebase.setString("Places/area2/location", "Not Available");
    }
    else{
      Firebase.setString("Places/area2/location9", "Available");
    }
   
  }  else Serial.println("Firebase failed");
  
}
