#include "fallback.h"


FallBack::FallBack() {
  STA_verrbingung_zeit=360000;
  AP_verrbingung_zeit =360000;
  }



int FallBack::wifi_status() {
  if (_STA == false && _AP == false)
  {
    Serial.println("Suche!");
    if (_scan_STA()) _STA = true; else _AP = true;
  }

  if (_STA == true)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      if (Server_Run == true)
      {
        Server_Run = false;
      }
      if ( millis() - STA_verrbingung_zeit >= STA_verrbingung_max_zeit )
      {
        if (STA_COUNTER <= STA_MAX_Versuche)
        {
          Serial.print("STA Verbindungsversuch! :");
          Serial.println(STA_COUNTER);
          STA();
          STA_verrbingung_zeit = millis();
          STA_COUNTER++;
        } else
        {
          _STA = false;
          _AP = true;
          STA_COUNTER = 0;
        }
      }
    } else
    {
      if (Server_Run == false)
      {
        Serial.println("STA Verbunden!");
        Serial.print("Start WebServer STA, IP : ");
        Serial.println(WiFi.localIP());
        A_IP=WiFi.localIP();
        Server_Run = true;
      }
    }
  }

  if (_AP == true)
  {
    if (WiFi.getMode() != WIFI_AP) WiFi.mode(WIFI_AP);
    if (Server_Run == false)
    {
      AP();
      Serial.println("AP gestart!");
      Serial.print("Start WebServer AP, IP : ");
      Serial.println(WiFi.softAPIP());
      A_IP=WiFi.softAPIP();
      Server_Run=true;
    }
    if (Server_Run == true)
    {
      if ( millis() - AP_verrbingung_zeit >= AP_verrbingung_max_zeit )
      {
        Serial.println("Suche STA nach!");
        WiFi.softAPdisconnect(true);
        WiFi.disconnect(true);
        Server_Run = false;
        _STA = false;
        _AP = false;
      }
    }
  }

  return -1;
}





int FallBack::AP() {
  WiFi.disconnect(true);
  WiFi.softAPdisconnect(true);
  if (WiFi.getMode() != WIFI_AP) WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(_AP_ip, _AP_gateway, _AP_subnet);
  WiFi.softAP(_AP_ssid, _AP_pass , _AP_channel , _AP_ssid_hidden );
  AP_verrbingung_zeit = millis();
  return -1;
}

int FallBack::STA() {
  WiFi.disconnect(true);
  WiFi.softAPdisconnect(true);
  if (WiFi.getMode() != WIFI_STA) WiFi.mode(WIFI_STA);
  WiFi.config(_STA_ip, _STA_gateway, _STA_subnet, _STA_dns1, _STA_dns2);
  WiFi.begin ( _STA_ssid, _STA_pass, _STA_channel, _STA_bssid, true);
  return -1;
}

bool FallBack::_scan_STA()
{
  if (WiFi.getMode() != WIFI_STA) WiFi.mode(WIFI_STA);
  int n = WiFi.scanNetworks();
  if (n == 0) return false;
  for (int i = 0; i < n; ++i)
    if (WiFi.SSID(i).equals(_STA_ssid)) return true;
  return false;
}

bool FallBack::set_softAP(const char* ssid, const char* passphrase , int channel , int ssid_hidden ) {
  _AP_ssid = ssid;
  _AP_pass = passphrase;
  _AP_channel = channel;
  _AP_ssid_hidden = ssid_hidden;
}
bool FallBack::set_softAPConfig(IPAddress local_ip, IPAddress gateway, IPAddress subnet) {
  _AP_ip = local_ip;
  _AP_gateway = gateway;
  _AP_subnet = subnet;
}

void FallBack::set_STA_begin(const char* ssid, const char *passphrase, int32_t channel, const uint8_t* bssid) {
  _STA_ssid = ssid;
  _STA_pass = passphrase;
  _STA_channel = channel;
  _STA_bssid = bssid;
}

void FallBack::set_STA_begin(char* ssid, char *passphrase, int32_t channel, const uint8_t* bssid) {
  return set_STA_begin((const char*) ssid, (const char*) passphrase, channel, bssid);
}

void FallBack::set_STA_config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = (uint32_t)0x00000000, IPAddress dns2 = (uint32_t)0x00000000)
{
  _STA_ip = local_ip;
  _STA_dns1 = dns1;
  _STA_dns2 = dns2;
  _STA_gateway = gateway;
  _STA_subnet = subnet;
}
