// Copyright (c) 2023 - Barton Dring
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#include <Arduino.h>
#include "Scene.h"
#include "Ota.h"

class OtaScene : public Scene {
private:
    int selection = 0;
    bool ota_handler_active;
    
public:
    
    OtaScene() : Scene("OTA") {}

    void onDialButtonPress() { pop_scene(); }

    void onGreenButtonPress() {
        // wifi on
        if (selection == 0) {
            init_wifi();
        }   
    
        // update new firmware now
        if (selection == 1 && WiFi.status() == WL_CONNECTED) {
            init_ota_handler();
            ota_handler_active = true;
        }
        reDisplay();
    }

    void onRedButtonPress() {
        if (selection == 0) {
            stop_wifi();
        }
    
        if (selection == 1) {
            stop_ota_handler();
            ota_handler_active = false;
        }
        reDisplay();
    }
   
    void onTouchRelease(int x, int y) {
        // Rotate through the items to be adjusted.
        rotateNumberLoop(selection, 1, 0, 1);
        reDisplay();
    }

    void onEncoder(int delta) {}
        
    void reDisplay() {
        drawBackground(BLACK);
        drawMenuTitle(current_scene->name());
        drawStatus();

        String grnText, redText;

        // if (state == Idle || state != Idle) {
        if (state == Idle) {
            int    x      = 40;
            int    y      = 62;
            int    width  = display.width() - (x * 2);
            int    height = 30;
            int    pitch  = 40;  // for spacing of buttons
            Stripe button(x, y, width, height, TINY);

            // wifi
            if (WiFi.status() != WL_CONNECTED) {
                button.draw("wifi", selection == 0);
            } else {
                String strIP = WiFi.localIP().toString();
                button.draw(strIP, selection == 0);
            }
 
            // ota handler
            if (ota_handler_active) {
                button.draw("OTA enabled", selection == 1);
            } else {
                button.draw("Enable OTA", selection == 1);
            }

            switch (selection) {
                case 0:
                    if (WiFi.status() != WL_CONNECTED) {
                    grnText = "wifi-on";
                    } else {
                    redText = "wifi-off";
                    }
                    break;
                case 1:
                    if (WiFi.status() == WL_CONNECTED) {
                        if (ota_handler_active) {
                            grnText = "";
                            redText = "Disable";
                            break;
                        } else {
                            grnText = "Enable";
                            redText = "";
                            break;
                        }
                    } else {
                        grnText = "";
                        redText = "";
                    }
            }
        } 
        
        drawButtonLegends(redText, grnText, "Back");
        showError();  // only if one just happened
        refreshDisplay();
    }
};
OtaScene otaScene;
