String Head(){
    String s = "HTTP/1.1 200 OK\r\n";
    s += "Content-Type: text/html\r\n\r\n";
    s += "<!DOCTYPE HTML>\r\n<html>\r\n";
    s += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    s += "<link rel=\"icon\" href=\"data:image/x-icon;base64,AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAAAAgAAAAAAAAAAAAAAAEAAAAAAAAADm5uYA39/fAOjo6AD///8Aurq6APz8/ADX19cAZGRkAOfn5wBGRkYA6+vrAAAAAAAAAAAAAAAAAAAAAAAAAAAAMzMzMzMzMzMzMzM5kzMzMzMzM5qpMzMzMzM5SqSTMzMzM5NKpGkzMzM5NKqgRpMzM5M0qqpGaTM3M0qqqhRmk3MzRERERGZpdERKqqqEREk3M1SqqkZmkzNzNKqiRmkzMzdzSqRnczMzMzd3d3MzMzMzMzMzMzMzMzMzMzMzMzMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\">";
    s += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background-color: #77878A;}";
    s += ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;";
    s += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
    s += ".button2 {background-color: #77878A;}</style></head>";
    s += "<body>";
    return s;
  }

String setting(){
  String s = ""; 
  s += "<p><a href=\"/hplus\"><button class=\"button\">h+</button></a><a href=\"/hmin\"><button class=\"button\">h-</button></a>";
  s += "<p><a href=\"/mplus\"><button class=\"button\">m+</button></a><a href=\"/mmin\"><button class=\"button\">m-</button></a>";
  s += "<p><a href=\"/end\"><button class=\"button\">end</button></a></p>";
  s += "</html>\n";
  return s;
  }

String Ending(){
  String s = ""; 
  s += "<p><a href=\"/info\"><button class=\"button\">Info</button></a><a href=\"/time\"><button class=\"button\">Time</button></a>";
  s += "<p><a href=\"/elena\"><button class=\"button\">Elana</button></a><a href=\"/set\"><button class=\"button\">set</button></a>";
  s += "</html>\n";
  return s;
  }

