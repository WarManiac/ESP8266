#include <ESP8266WiFi.h>

class FallBack;

class FallBack {
  private:
    bool _STA                               = false;
    bool _AP                                = false;
    bool _scan_STA();
    const char* _STA_ssid                   = "Eingeben";
    const char* _STA_pass                   = "Eingeben";
    const char* _AP_ssid                    = "";
    const char* _AP_pass                    = "";
    IPAddress                               _AP_ip;
    IPAddress                               _AP_gateway;
    IPAddress                               _AP_subnet;
    int _AP_channel;
    int _AP_ssid_hidden;
    int _AP_max_connection;
    IPAddress                                _STA_ip;
    IPAddress                                _STA_dns1;
    IPAddress                                _STA_dns2;
    IPAddress                                _STA_gateway;
    IPAddress                                _STA_subnet;
    int32_t _STA_channel;
    const uint8_t* _STA_bssid;
    unsigned long STA_verrbingung_zeit;
    int STA_COUNTER                          = 0;
    unsigned long AP_verrbingung_zeit;
    
    int STA();
    int AP();

  public:
    FallBack();
    bool Server_Run = false;
    unsigned long STA_verrbingung_max_zeit   =  10000;
    unsigned long AP_verrbingung_max_zeit    =  60000;
    int STA_MAX_Versuche= 3;
    int wifi_status();

    bool set_softAP(const char* ssid, const char* passphrase = NULL, int channel = 1, int ssid_hidden = 0);
    bool set_softAPConfig(IPAddress local_ip, IPAddress gateway, IPAddress subnet);

    void set_STA_config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1, IPAddress dns2);
    void set_STA_begin(const char* ssid, const char *passphrase = NULL, int32_t channel = 0, const uint8_t* bssid = NULL);
    void set_STA_begin(char* ssid, char *passphrase = NULL, int32_t channel = 0, const uint8_t* bssid = NULL);

    IPAddress A_IP;
};

