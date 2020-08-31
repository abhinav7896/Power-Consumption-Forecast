#include<ESP8266WiFi.h>




String ssid = "";
String password = "";
int UNITSBUF = 0;
int count = 0;
int PERKWH = 12;     // 3200 imp/kwh
bool light;
const char *host = "airaidcom.000webhostapp.com";

void wificonnect()                                                                                              //Connect to one of the available wifi access points.
{
 Serial.println("Enter ssid and password \n\n");
 Serial.println("ssid : ");
 if(!Serial.available())
  {
   while(1)
    {
      if(Serial.available())
       break;
    }
  }
 if(Serial.available() && ssid == "")
   {
    while(Serial.available())
     ssid = Serial.readString();
    Serial.print("\n");
    Serial.println("password : \n");
    if(!Serial.available())
      {
        while(1)
         {
          if(Serial.available())
          break;
         }
      }
    if(Serial.available() && password == "")
     {
      while(Serial.available())
       password = Serial.readString();   
     }
    }
 if(ssid != "" && password != "" && !WiFi.isConnected())
 {
  delay(1000);
  Serial.printf("Connecting to %s . . .",ssid.c_str());
  WiFi.begin(ssid.c_str(),password.c_str());
  while(WiFi.waitForConnectResult() != WL_CONNECTED)
   {
    Serial.print(" .");
    delay(750);
   }
 }
 if(WiFi.isConnected())
  {
  Serial.printf(" \n Connected to : %s \n",WiFi.SSID().c_str());
  WiFi.scanDelete();
  }
 else 
  Serial.println("\n\n \t Connection failed");
 }

void sendData()
{
 WiFiClient client;                                                                                             //WifiClient is http client library.
 String url = "/receive.php?inc=1";                 //URL of the service.
 if(client.connect(host,80))                                                                                    //Establishing http connection to the host using WifiClient object.
  Serial.printf("\n\n \t\t Connected to %s \n\n",host);
 else
  Serial.println("\n\n \t\t Could not connect to server! \n");
 Serial.print("Sending data .");
 //delay(500);
 //Serial.print(" .");
 if(client.connected())                                  
 {
 //delay(500);
 while(UNITSBUF > 0)
 {
  Serial.print("GET req .");
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); //Send data in the form of a http GET request if the http connection is established successfully.
  Serial.print(" .");
  //delay(1000);
  //Serial.print(" .");
  //delay(1000);
  //Serial.print(" .");
  Serial.println("\n\n Response : \n\n");
  while(client.available())                                                                                     //Receive response from the server. 
   {
   String msg = client.readStringUntil('\n');
   Serial.println(msg);
   }
  UNITSBUF--;
  }
 }
}  

void setup() {
  // put your setup code here, to run once:
pinMode(0,INPUT);
int num, i;
Serial.begin(115200);
Serial.print("Initializing .");
 delay(500);
 Serial.print(" .");
 delay(500);
 Serial.print(" .");
 delay(1000);
 Serial.print(" .\n");
 WiFi.mode(WIFI_AP_STA);
 if(WiFi.getAutoConnect() == true)
  WiFi.setAutoConnect(false);
 delay(2000);
 if(WiFi.isConnected())
  {
    Serial.printf("Connected to %s \n",WiFi.SSID().c_str());
    Serial.end();
    while(WiFi.isConnected());
  }
 Serial.println("No autoconnect \n");
 delay(1000);
 Serial.print("Scanning. . .");
 num = WiFi.scanNetworks(true);                                                                   //Scan for available access points.
 delay(500);
 Serial.print(" .");
 if(WiFi.scanComplete() == -2)                                                                   
  {
  Serial.println("Scan failed! \n Enter ssid and password manually or reset the module and try again. \n");
  wificonnect();
  }
 while(WiFi.scanComplete() == -1)
 {
  delay(300);
  Serial.print(" .");
  delay(300);
  Serial.print(" .");
  delay(300);
 }
  if(WiFi.scanComplete() == 0)
   {
   Serial.println("\n\n\n\t\t No networks found! Reset the module and try again when WiFi is available \n");
   while(1);
   }
  if(WiFi.scanComplete() > 0)
     {
      num = WiFi.scanComplete();
      Serial.println("\n <<<<<<<<<< Available AP's >>>>>>>>>> \n");
     }
 
 for(i=0;i<num;i++)
  {
    Serial.printf("SSID : %s  \t\t Strength : %d dB \n",WiFi.SSID(i).c_str(),WiFi.RSSI(i));                       //Display available AP's. 
  }
wificonnect();
}

void loop() 
{
  // put your main code here, to run repeatedly:
int val;
val = analogRead(0);
if(val/100 == 0 || val/100 == 1 || val/100 == 2 || val/100 == 3)
 light = 1;
if(light == 1)
 { 
 count++;
 Serial.println("LIGHT!");
 delay(100);
 light = 0;
 }
if(count == PERKWH)
 {
  UNITSBUF++;
  sendData();
  count = 0;
  Serial.println("Count refreshed"); 
 }

}

