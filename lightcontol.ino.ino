
#include<ESP8266WiFi.h>                                                                                         //esp8266 wifi library for coding the wifi module.

String ssid = "";
String password = "";
WiFiServer server(80);
bool val = 0;
String htmlPage = String("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n")
                  +"<html>"
                  +"<h1>DEVICE CONTROL</h1>"
                  +"<br><br><br>"
                  +"Device 1 : <br>"
                  +"<a href='/switchON'><button type='button'>Switch On</button></a>"
                  +"<br><br>" 
                  +"<a href='/switchOFF'><button type='button'>Switch Off</button></a>"
                  +"</html>";






/*void showControlPage(WiFiClient client)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
}*/



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


                                                                                                                                                           
void setup() 
{
 pinMode(2,OUTPUT);
 int num,i;
 Serial.begin(115200);
 delay(10000);
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
server.begin();
Serial.println("Server mode started");
Serial.println("IP : ");
Serial.print(WiFi.localIP());
}

void loop() 
{
WiFiClient client;
client = server.available();
if(!client)
 return;
Serial.println("New client connected!");
while(!client.available())
 delay(1);
String req = client.readString();
Serial.println("Request : ");
Serial.print(req);
client.flush();
if(req.indexOf("/control") != -1)
 {
  client.println(htmlPage);
 }
else if(req.indexOf("/switchON") != -1)
 {
  val = 1;
  client.println(htmlPage);
 }
else if(req.indexOf("/switchOFF") != -1)
 {
 val = 0;
 client.println(htmlPage); 
 }
digitalWrite(2,val);



Serial.println("Connection closed"); 

}
