// Copyright (c) 2023 - Barton Dring
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#include <Arduino.h>
#include "Scene.h"

extern Scene otaScene;

class ExtraScene : public Scene {
private:
    int selection = 0;    

public:

    
    ExtraScene() : Scene("more") {}

    void onDialButtonPress() { pop_scene(); }

    void onGreenButtonPress() {
        // restart pendant
        if (selection == 0) {
            ESP.restart();
            while (1) {}
        }     
    
        // display the OTA scene to allow update
        if (selection == 1) {
            activate_scene(&otaScene);
            return;
        }

        reDisplay();
    }

    void onRedButtonPress() {
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

        if (state == Idle) {
            int    x      = 40;
            int    y      = 62;
            int    width  = display.width() - (x * 2);
            int    height = 30;
            int    pitch  = 40;  // for spacing of buttons
            Stripe button(x, y, width, height, TINY);

            
            button.draw("restart pendant", selection == 0);
            
            button.draw("OTA Fw update", selection == 1);

            switch (selection) {
                case 0:
                    grnText = "RESTART";
                    redText = "";
                    break;
                case 1:
                    grnText = "OTA menu";
                    redText = "";
                    break;
            }
        } 
        
        drawButtonLegends(redText, grnText, "Back");
        showError();  // only if one just happened
        refreshDisplay();
    }
};
ExtraScene extraScene;
