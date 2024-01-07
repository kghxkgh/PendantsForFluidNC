#include <system.h>
#include <Ota.h>
#include <WiFi.h>
#include "time.h"
#include <ArduinoOTA.h>

#include <secrets.h> // this just contains the define lines that follow for ssid & pass
 
#ifndef ssid
#define ssid "my_wifi"
#define pass "my_password"
#endif


/* clang-format: off */
void init_ota() {
    ArduinoOTA
                .onStart([]() {
                String type;
                if (ArduinoOTA.getCommand() == U_FLASH)
                    type = "sketch";
                ///else // U_SPIFFS
                ///   type = "filesystem";

                // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
                ///Serial.println("Start updating " + type);
                })
                .onEnd([]() {
                })
                .onProgress([](unsigned int progress, unsigned int total) {
                int progress_percent = (progress / (total / 100));
                })
                .onError([](ota_error_t error) {
                if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
                else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
                else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
                else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
                else if (error == OTA_END_ERROR) Serial.println("End Failed");
                });
}

void init_wifi() {
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, pass);
    }
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    }  
}

void stop_wifi() {
    if (WiFi.status() == WL_CONNECTED) {
            WiFi.disconnect();
            WiFi.mode(WIFI_OFF);
    }
}

void init_ota_handler() {
    ArduinoOTA.setHostname("fluiddial");
    ArduinoOTA.begin();
}

void stop_ota_handler() {
    ArduinoOTA.end();
}

