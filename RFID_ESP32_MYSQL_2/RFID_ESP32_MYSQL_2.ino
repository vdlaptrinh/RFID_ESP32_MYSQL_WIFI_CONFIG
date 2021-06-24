#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <EEPROM.h>
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define ON_Board_LED 2
//Variables
unsigned char udataTTL[4];
char dataTTL[8];
int  dataIdx;

long tagID;

int statusCode;
const char* ssid = "text";
const char* passphrase = "text";
String st;
String content;
 
int BUZZ = 23;
int LED1 = 22;
int LED2 = 21;
//int redLed = D0;
//int blueLed = D4;

long temp=0, last=0;
 
 
//Function Decalration
bool testWifi(void);
void launchWeb(void);
void setupAP(void);
 
//Establishing Local server at port 80 whenever required
WebServer server(80);

void setup()
{
  Serial.begin(115200);  // start serial to PC
  Serial2.begin(19200);    // start serial to RFID reader
  //Serial.println("Serial Ready");
  pinMode(BUZZ, OUTPUT); 
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT);
  //pinMode(blueLed, OUTPUT); 
  //pinMode(redLed, OUTPUT);
  pinMode(ON_Board_LED, OUTPUT);
  digitalWrite(ON_Board_LED, HIGH);
  dataIdx = 0;
  tagID = 0;

  Serial.println("Disconnecting previously connected WiFi");
  //WiFi.disconnect();
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.println("Startup");
 
  //Read EEPROM for SSID and pass
  Serial.println("Reading EEPROM ssid");
 
  String esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");
 
  String epass = "";
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);
 
 
  WiFi.begin(esid.c_str(), epass.c_str());
  if (testWifi())
  {
    Serial.println("Succesfully Connected!!!");
    
    Serial.println(WiFi.localIP());
    for (int i=0;i<3;i++){
      digitalWrite(ON_Board_LED, LOW);
      delay(250);
      digitalWrite(ON_Board_LED, HIGH);
      delay(250);
    }
    return;
  }
  else
  {
    Serial.println("Turning the HotSpot On");
    launchWeb();
    setupAP();// Setup HotSpot
  }
 
  Serial.println();
  Serial.println("Waiting.");
  
  while ((WiFi.status() != WL_CONNECTED))
  {
    Serial.print(".");
    delay(100);
    server.handleClient();
  }
  
}

void loop()
{
   if( Serial2.available() ) {
    udataTTL[dataIdx++] = Serial2.read();
   }
   if(dataIdx == 4) 
   {
     digitalWrite(BUZZ, HIGH);
     delay(150);
     digitalWrite(BUZZ, LOW);
     XuLyMaThe();
     Send_Data_PHP(String(tagID));
   }
}

void Send_Data_PHP(String Num)
{
  digitalWrite(ON_Board_LED, LOW);
  WiFiClient client;
  HTTPClient http;
  http.begin(client,"http://192.168.20.113:80//RFID2/getUID.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String httpRequestData = "MaThe=" + String(Num) + "";
  // Send HTTP POST request về databasephp
  int httpResponseCode = http.POST(httpRequestData);
  String payload = http.getString();
  // nếu đưa dữ liệu thành công httpResponseCode == 200
  // nếu không đưa dữ liệu dc httpResponseCode == -1
  //if (httpResponseCode == 200)
  //{
    //String payload = http.getString();
    Serial.println(httpRequestData);
    Serial.println(httpResponseCode);
    Serial.println(payload);
    //if(payload.indexOf("A1B") >= 0)
    //{
    //  Serial.println("BLE LED");
    //  digitalWrite(LED1, HIGH);
    //  digitalWrite(LED2, LOW);
      //trangthairelay1 = 1;
    //}
    //else if(payload.indexOf("A0B") >= 0)
    //{
    //  Serial.println("RED LED");
   //   digitalWrite(LED1, LOW);
   //   digitalWrite(LED2, HIGH);
      //trangthairelay1 = 0;
   // }
  //}
  //else
  //{
  //  Serial.println("Không gửi dữ liệu được ");
  //}
  http.end();
  //=================================================================================
  digitalWrite(ON_Board_LED, HIGH);
}

 
 
//-------- Fuctions used for WiFi credentials saving and connecting to it which you do not need to change 
bool testWifi(void)
{
  int c = 0;
  Serial.println("Waiting for Wifi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}
 
void launchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}
 
void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);
 
    st += ")";
    st += (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
  WiFi.softAP("ESP_Wifi_Config", "12345678");
  Serial.println("softap");
  launchWeb();
  Serial.println("over");
}
 
void createWebServer()
{
 {
    server.on("/", []() {
 
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
      content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
      content += ipStr;
      content += "<p>";
      content += st;
      content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    server.on("/scan", []() {
      //setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
 
      content = "<!DOCTYPE HTML>\r\n<html>go back";
      server.send(200, "text/html", content);
    });
 
    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");
 
        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.print("Wrote: ");
          Serial.println(qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
        EEPROM.commit();
 
        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
        //ESP.reset();
        ESP.restart();
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);
 
    });
  } 
}
void XuLyMaThe()
{
     // unsigned char to char
     for( int i = 0; i < 8; i+=2 )
     {
       dataTTL[i] = 0x30 + udataTTL[i/2] / 16;
       if( dataTTL[i] > 0x39 ) dataTTL[i] += 7;  // 大於 ASCII '9' 就要變成英文 A(0x41)
       dataTTL[i+1] = 0x30 + udataTTL[i/2] % 16;
       if( dataTTL[i+1] > 0x39 ) dataTTL[i+1] += 7;

     }

     
     String id = dataTTL;
 
    // 轉成 16 進位資料並比對
    String hexCode = "0x" + id.substring( 0, 8 );
    //Serial.print("HEX Code: ");
    //Serial.print( hexCode );
    
    // 轉換為 10 進位資料並比對
    char buf[11];  // 包括前方的 0x 共 10 個位元 + 空白字元
    hexCode.toCharArray( buf, sizeof(buf) );
    tagID = strtol( buf,  NULL, 0 );
    //Serial.print( "Decimal: " );
    Serial.println( tagID );
    dataIdx = 0;
}
