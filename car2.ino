#include <ESP8266WiFi.h>

const char* ssid = "SAKSHI";
const char* passward = "BRZIL@JIO";
WiFiServer server(80);
void setup() 
{
 pinMode(A0,OUTPUT);
 pinMode(D0,OUTPUT);
 pinMode(D1,OUTPUT);
 pinMode(D2,OUTPUT);
 pinMode(D3,OUTPUT);
 Serial.begin(115200);
 Serial.println();
 Serial.println();
 Serial.print("Connercting to");
 Serial.println(ssid);
 WiFi.begin(ssid,passward);
 while(WiFi.status()!=WL_CONNECTED
 {
  delay(500);
  Serial.print(".");
 }
 Serial.println(" ");
 Serial.println("WiFi connected");
 Serial.begin();
 Serial.println("Server started");
 Serial.println("WiFi.localIP()");
}
void loop() 
{
  WiFiClient.client=server.available();
  if(!client)
  {
    return;
  }
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
  String req=client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if(req.indexOf("/FORWARD")!=-1)
  {
   status_FORWARD=1;
   digitalWrite(D0,HIGH);
   digitalWrite(D2,HIGH);
   digitalWrite(D1,LOW);
   digitalWrite(D3,LOW);
   Serial.println("MOVING FORWARD");
  }
  else if(req.indexOf("/BACKWARD")!=-1)
  {
   status_BACKWARD=1;
   digitalWrite(D1,HIGH);
   digitalWrite(D3,HIGH);
   digitalWrite(D0,LOW);
   digitalWrite(D2,LOW);
   Serial.println("MOVING BACKWARD");
  }
  else if(req.indexOf("/RIGHT")!=-1)
  {
   status_RIGHT=1;
   analogWrite(A0,100);
   digitalWrite(D0,HIGH);
   digitalWrite(D2,HIGH);
   digitalWrite(D1,LOW);
   digitalWrite(D3,LOW);
   Serial.println("MOVING RIGHT");
  }
  else if(req.indexOf("/LEFT")!=-1)
  {
   status_LEFT=1;
   analogWrite(A0,50);
   digitalWrite(D0,HIGH);
   digitalWrite(D2,HIGH);
   digitalWrite(D1,LOW);
   digitalWrite(D3,LOW);
   Serial.println("MOVING LEFT");
  }
  String web ="HTTP/1.1 200 OK \r\n Content-Type:text/html\r\n";
  web+="<html>\r\n";
  web+="<body>\r\n";
  web+="<h1>CAR STATUS</h1>\r\n";
  web+="<p>\r\n";
  if(status_FORWARD==1)
  web+="car is moving forward\r\n";
  if(status_BACKWARD==1)
  web+="car is comming back\r\n";
  if(status_RIGHT==1)
  web+="car is taking right\r\n";
  if(status_LEFT==1)
  web+="car is taking left\r\n";
  web+="</p>\r\n";
  web+="</p>\r\n";
  web+="<a href=\"/FORWARD>\r\n";
  web+="<button>FORWARD</button>\r\n";
  web+="</a>\r\n";
  web+="</p>\r\n";
  web+="<a href=\"/BACKWARD>\r\n";
  web+="<button>BACKWARD</button>\r\n";
  web+="</a>\r\n";
  web+="</p>\r\n";
  web+="<a href=\"/RIGHT>\r\n";
  web+="<button>RIGHT</button>\r\n";
  web+="</a>\r\n";
  web+="</p>\r\n";
  web+="<a href=\"/LEFT>\r\n";
  web+="<button>LEFT</button>\r\n";
  web+="</a>\r\n";
  web+="</body>\r\n";
  web+="</html>\r\n";
  client.print(web);
}
