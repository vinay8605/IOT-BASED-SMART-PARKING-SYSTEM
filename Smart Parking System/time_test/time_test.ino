9#include<ESP8266WiFi.h>
#include <WiFiUdp.h>
#include<FirebaseArduino.h>
#include <NTPClient.h>
#include <NTPClient.h>;
#define FIREBASE_HOST "smart-parking-3387e-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "o8NnsbJ5aD8YgHK8SfB4buTOS6rZGS2TIjQLDKSv"
#define WIFI_SSID "1234" 
#define PASSWORD "12345678"
uint8_t arr[5];
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 198000,60000);
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
  timeClient.begin();
 

}

void loop() {
  // put your main code here, to run repeatedly:
  arr[0] = digitalRead(D0);
  
  //timer functions
  timeClient.update();
 int hh = timeClient.getHours();
 int mm = timeClient.getMinutes();
 int ss= timeClient.getSeconds();
  
 String h= String(hh); 
  String m= String(mm);
   String s= String(ss);
  
  
 
  
  if(!Firebase.failed()){
 
    Serial.println("Sensor 1");                               //sensor 1 code
    if(arr[0]==HIGH){
      Firebase.setString("firstfloor/Sensor1", "Available");
       String EntryTimeSlot1 =  h +" :" + m + " :" + s;       //sensor 1 time
       
        Firebase.setString("Time/senor1exit",EntryTimeSlot1);
       
      
      Serial.println("HIGH");
    }
    else{
      Firebase.setString("firstfloor/Sensor1","Not Available");
      String ExitTimeSlot1= h +" :" + m + " :" + s ;
      Firebase.setString("Time/senor1entry",ExitTimeSlot1);
      Serial.println("LOW");
    }
     Serial.println("Sensor 2");                                 //sensor 2 code
    if(arr[1]==HIGH){
      Firebase.setString("firstfloor/Sensor2","Available");
      String EntryTimeSlot2 =  h +" :" + m + " :" + s;            //sensor 2 time
      Firebase.setString("Time/senor2exit",EntryTimeSlot2);
      Serial.println("HIGH");
    }
    else{
      Firebase.setString("firstfloor/Sensor2","Not Available");
      Firebase.setString("Time/senor2entry",h +" :" + m);
        String ExitTimeSlot2= h +" :" + m + " :" + s;
      Serial.println("LOW");
    }Serial.println("Sensor 3");                                // sensor 3 code
    if(arr[2]==HIGH){
      Firebase.setString("firstfloor/Sensor3","Available");
      String EntryTimeSlot3 =  h +" :" + m + " :" + s;           //sensor 3 time
      Firebase.setString("Time/senor3exit",EntryTimeSlot3);
      Serial.println("HIGH");
    }
    else{
      Firebase.setString("firstfloor/Sensor3","Not Available");
      String ExitTimeSlot3= h +" :" + m + " :" + s;
      Firebase.setString("Time/senor3entry",ExitTimeSlot3);
      Serial.println("LOW");
    }Serial.println("Sensor 4");                                  // sensor 4 code
    if(arr[3]==HIGH){
      Firebase.setString("secondfloor/Sensor1", "Available");
      String EntryTimeSlot4= h +" :" + m + " :" + s;              //sensor 4 time
      Firebase.setString("Time/senor4exit",EntryTimeSlot4);
      Serial.println("HIGH");
    }
    else{
      Firebase.setString("secondfloor/Sensor1","Not Available");
      String ExitTimeSlot4= h +" :" + m + " :" + s;
      Firebase.setString("Time/senor4entry",h +" :" + m);
      Serial.println("LOW");
    }Serial.println("Sensor 5");                       // sensor 5 code
    if(arr[4]==HIGH){
      Firebase.setString("secondfloor/Sensor2", "Available");
      String EntryTimeSlot5= h +" :" + m + " :" + s;       // sensor 5 time
      Firebase.setString("Time/senor5exit",EntryTimeSlot5);
      Serial.println("HIGH");
    }
    else{
      Firebase.setString("secondfloor/Sensor2","Not Available");
      String ExitTimeSlot5= h +" :" + m + " :" + s;
      Firebase.setString("Time/senor5entry",ExitTimeSlot5);
      Serial.println("LOW");
    }Serial.println("Sensor 6");                      // sensor 6 code
     if(arr[5]==HIGH){
      Firebase.setString("secondfloor/Sensor3", "Available");
      String EntryTimeSlot6= h +" :" + m + " :" + s;       // sensor 6 time
      Firebase.setString("Time/senor6exit",EntryTimeSlot6);
      Serial.println("HIGH");
    }
    else{
      Firebase.setString("secondfloor/Sensor3","Not Available");
      String ExitTimeSlot6= h +" :" + m + " :" + s;
      Firebase.setString("Time/senor6entry",ExitTimeSlot6);
      Serial.println("LOW");
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
