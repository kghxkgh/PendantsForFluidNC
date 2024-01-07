// Copyright (c) 2023 Mitch Bradley
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once


#include "ArduinoOTA.h"

void init_ota();
void init_wifi();
void init_ota_handler();
void stop_wifi();
void stop_ota_handler();
void init_time();
void get_ntp_time();
void printLocalTime();