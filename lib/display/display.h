#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <lvgl.h>
#include <ui.h>
#include <TFT_eSPI.h>

 //Object constructors
// TFT_eSPI tft = TFT_eSPI();

 /*Set to your screen resolution and rotation*/
#define TFT_HOR_RES   320
#define TFT_VER_RES   240
#define TFT_ROTATION  LV_DISPLAY_ROTATION_0

// Function prototypes
static uint32_t my_tick(void);
void display_setup();
void display_loop();


#endif //DISPLAY_H_