#include <Arduino.h>

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <ESPmDNS.h>
#define ESP_RESET ESP.restart()
#else
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#define ESP_RESET ESP.reset()
#endif

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Use WiFi Manager to configure the WiFi (including storing SSID and PASSWORD)
#define USE_WIFI_MANAGER

// Use a static IP instead of using DHCP
// #define USE_STATIC_IP

#ifndef USE_WIFI_MANAGER
#define WIFI_SSID "XXXXXXXX"
#define WIFI_PASSWORD "************"
#endif

#ifdef USE_STATIC_IP
IPAddress ip(192, 168, 0, 123);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
#endif

/*
 * Over-the-air support
 */
void ota_setup()
{
  Serial.println("OTA Booting");

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP_RESET;
  }

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("Esp");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]()
                     {
		String type;
		if (ArduinoOTA.getCommand() == U_FLASH)
			type = "sketch";
		else // U_SPIFFS
			type = "filesystem";

		// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
		Serial.println("Start updating " + type); });
  ArduinoOTA.onEnd([]()
                   { Serial.println("\nEnd"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });
  ArduinoOTA.onError([](ota_error_t error)
                     {
		Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
		else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
		else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
		else if (error == OTA_END_ERROR) Serial.println("End Failed"); });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

/*
 * Handle OTA request if there is one.
 */
void ota_handler()
{
  ArduinoOTA.handle();
}

/*
 * WiFi Manager support.
 * Connect to a registred SSID (stored in eeprom) or enable the hotspot mode to provide a configuration page.
 */
void wifimanager_setup(String ordre)
{
  // Initialisation WiFiManager
  WiFiManager wifiManager;

  if (ordre == "Reset")
  {
    // Reset SSID et Pwd
    wifiManager.resetSettings();
    Serial.println("Reset Ok.");
    ESP_RESET;
  }
  else
  {
    /*
    Récupère ssid et pass de l'eeprom et essai de se connecter
    Si connexion impossible, démarrage en point d'accès. Ici ssid => "AutoConnectAP-ESP"
    et reste en attente de configuration
    */
    wifiManager.autoConnect("AutoConnectAP-ESP");
    // ou pour générer ssid => nom ESP + ChipID
    // wifiManager.autoConnect();

    // Connexion au WiFi Ok
    Serial.println("Connected.");
  }
}

/*
 * WiFi support.
 * If no connection is made within timeout, ESP gets resettet.
 */
void wifi_setup(ulong timeout)
{
  Serial.println("Wifi setup");

#ifdef USE_WIFI_MANAGER
  wifimanager_setup("Run");
#else
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.mode(WIFI_STA);
#endif

#ifdef USE_STATIC_IP
  WiFi.config(ip, gateway, subnet);
#endif

  unsigned long connect_start = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");

    if (millis() - connect_start > timeout)
    {
      Serial.println();
      Serial.print("Tried ");
      Serial.print(timeout);
      Serial.print("ms. Resetting ESP now.");
      ESP_RESET;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

unsigned long last_wifi_check_time = 0;

/*
 * Check WiFi connectivity at a regular interval (timeout) and reconnect to it if required.
 */
void wifi_reconnect_on_timeout(ulong timeout)
{
  unsigned long now = millis();

  if (now - last_wifi_check_time > timeout)
  {
    Serial.print("Checking WiFi... ");
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("WiFi connection lost. Reconnecting...");
      wifi_setup(timeout);
    }
    else
    {
      Serial.println("OK");
    }
    last_wifi_check_time = now;
  }
}