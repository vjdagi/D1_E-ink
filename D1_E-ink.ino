#include <GxEPD.h>
#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <ESP8266HTTPClient.h>
#include <GxGDEW027W3/GxGDEW027W3.cpp>

#include "IMG_0001.h"
#include "sideCode.h"
#include "Config.h"
#include "Web.h"

#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

#if defined(ESP8266)

// generic/common.h
//static const uint8_t SS    = 15; // D8
//static const uint8_t MOSI  = 13; // D7
//static const uint8_t MISO  = 12; // D6
//static const uint8_t SCK   = 14; // D5

GxIO_Class io(SPI, /*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2); // arbitrary selection of D3(=0), D4(=2), selected for default of GxEPD_Class
GxEPD_Class display(io /*RST=D4*/ /*BUSY=D2*/); // default selection of D4(=2), D2(=4)

#elif defined(ESP32)

// pins_arduino.h, e.g. LOLIN32
//static const uint8_t SS    = 5;
//static const uint8_t MOSI  = 23;
//static const uint8_t MISO  = 19;
//static const uint8_t SCK   = 18;

GxIO_Class io(SPI, /*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16); // arbitrary selection of 17, 16
GxEPD_Class display(io, /*RST=*/ 16, /*BUSY=*/ 4); // arbitrary selection of (16), 4

#else

// pins_arduino.h, e.g. AVR
//#define PIN_SPI_SS    (10)
//#define PIN_SPI_MOSI  (11)
//#define PIN_SPI_MISO  (12)
//#define PIN_SPI_SCK   (13)

GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9); // arbitrary selection of 8, 9 selected for default of GxEPD_Class
GxEPD_Class display(io /*RST=9*/ /*BUSY=7*/); // default selection of (9), 7

#endif

WiFiServer server(80);

void setup()
{
  setTime(0,0,0,1,1,2016);
  timeold = minute();
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");

  display.init(115200);
  Serial.println("setup done");
  Serial.print("Connecting to...");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Wi-Fi connected successfully");
  server.begin();
}

void loop()
{
  if (timeold == minute() - 5 && second() <= 5 || minute() == 5 && second() <= 5)
  { 
    up = 1;
    timeold = minute();
  }
  
  WiFiClient client = server.available();

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  if(WiFi.status()== WL_CONNECTED && up == 1){ 
    temp = getInfo(URL_temp);
    hum = getInfo(URL_hum);
    tempout = getInfo(URL_tempout);
    radio = getInfo(URL_radio);
    track = getInfo(URL_track);
    cur = getInfo(URL_cur);
  }
  
  String s = Head();
  
  if (req.indexOf("/info") != -1) val = -1;
  else if (req.indexOf("/elena") != -1) val = 0;
  else if (req.indexOf("/time") != -1) val = 1;
  else if (req.indexOf("/set") != -1) val = 2;
  else if (req.indexOf("/end") != -1) val = 3;
  else if (req.indexOf("/hplus") != -1) val = 4;
  else if (req.indexOf("/hmin") != -1) val = 5;
  else if (req.indexOf("/mplus") != -1) val = 6;
  else if (req.indexOf("/mmin") != -1) val = 7;

  if(vall != val || up == 1) {
    if (val == -1){
      radioinfo("Sensor", &FreeMonoBold9pt7b);
      s += "info";
      vall = val;}
    else if (val == 0){
      elena("Sensor", &FreeMonoBold9pt7b);
      s += "elena";
      vall = val;}
    else if (val == 1){
      timeinfo("Sensor", &FreeMonoBold24pt7b);
      s += "time";
      vall = val;}
    else if (val == 2){
      settings = 1;
      val = -2;
      vall = val;}
    else if (val == 3){
      settings = 0;
      val = -2;
      vall = val;}
    else if (val == 4){
      adjustTime(3600);
      val = -2;
      vall = val;}
    else if (val == 5){
      adjustTime(-3600);
      val = -2;
      vall = val;}
    else if (val == 6){
      adjustTime(60);
      val = -2;
      vall = val;}
    else if (val == 7){
      adjustTime(-60);
      val = -2;
      vall = val;}
    h = need0(hour());
    m = need0(minute());
    up = 0;
    }
    
  client.flush();
  if(settings == 0) s += Ending();
  else {
    s += h + ":" + m ;
    s += setting();
    }
  
  client.print(s);
  Serial.println(hour());
  Serial.println(minute());
  Serial.println(second());
}

void radioinfo(const char name[], const GFXfont* f)
{
  display.setRotation(3);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println("Tempature:");
  display.println("Outside:  " + tempout + "C");
  display.println("Inside:   " + temp + "C");
  display.println("Humidity: " + hum + "%");
  display.println(cur);
  display.println("-----------------------");
  display.println(radio);
  display.println(track);
  display.drawExampleBitmap(gImage_IMG_0001, 190, 3, 71, 71, GxEPD_BLACK);
  display.update();
  delay(5000);
}

void elena(const char name[], const GFXfont* f)
{
  display.setRotation(3);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  display.drawExampleBitmap(gImage_IMG_0002, 0, 0, 264, 173, GxEPD_BLACK);
  display.update();
  delay(5000);
}

void timeinfo(const char name[], const GFXfont* f)
{
  display.setRotation(3);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println(" " + tempout + "C");
  //display.println(temp + "C/" + hum + "%");
  display.println("---------");
  display.println("  " + h + "\:" + m );
  display.drawExampleBitmap(gImage_IMG_0001, 190, 3, 71, 71, GxEPD_BLACK);
  display.update();
  delay(5000);
}


