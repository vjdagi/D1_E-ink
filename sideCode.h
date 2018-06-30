String temp = "00";
String hum = "00";
String tempout = "00";
String radio = "";
String track = "";
String cur = "";
int val = -1;
int vall = -2;
int timeold;
int up = 1;
String h = "0";
String m = "0";
int settings = 0;

String getInfo(String url){
   HTTPClient http;
   http.begin(url);  
   http.addHeader("Content-Type", "text/plain");  
   int httpCode = http.GET();  
   String t =  http.getString();
   http.end();
   if (t == "NULL")
    t = "";
   return t;
  }

String need0(int i){
  String st ="";
  if (i <= 9) st = "0";
  return st + i;
  }
