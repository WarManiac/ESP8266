FallBack

Ist da für da wenn der STA nicht vorhanden ist ein AP zustarten und<br>
in bestimmten Zeit abständen nach zu sehen ob der STA wieder errreichbar ist.<br>
<br>
Inizalieren: <br>
FallBack fallback = FallBack();<br>
<br>
Config:<br>
  ist gleich wie: https://www.arduino.cc/en/Reference/WiFiBegin<br>
  fallback.set_STA_begin(STA_ssid, STA_pass);<br>
  <br>
  ist gleich zu:http://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html<br>
  fallback.set_softAPConfig(AP_ip, AP_gateway, AP_subnet);<br>
  fallback.set_softAP(AP_ssid, AP_pass);<br>
  <br>
  hier sagt ihr wie lange der verbinungsversuch daueren darf zum STA<br>
  fallback.STA_verrbingung_max_zeit = 10000; //standart 10sec zum verbinden<br>
  <br>
  wie oft soll er versuchen<br>
  fallback.STA_MAX_Versuche = 3;           //standart max 3 versuche zum AP zuverbinden alle versuch fehlschlagen AP Modus<br>
  
  nach wieviel msec so nach dem STA gesehen werden.<br>
  Achtung AP wird aus gemacht!<br>
  fallback.AP_verrbingung_max_zeit = 60000; //standart 60sec im AP modus<br>
  <br>
  im loop:<br>
  void loop() {<br>
    fallback.wifi_status();<br>
    ...<br>
    ....<br>
    .....<br>
  }<br>
  
TODO:
  - Rückgabewert für fehlerhaft config
  - Rückgabewert/callback -> AP STA Änderung
  - Rückgabewert IP
