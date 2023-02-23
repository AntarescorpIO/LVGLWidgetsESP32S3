/*******************************************************************************
 * Touch libraries:
 * FT6X36: https://github.com/strange-v/FT6X36.git
 * GT911: https://github.com/TAMCTec/gt911-arduino.git
 * XPT2046: https://github.com/PaulStoffregen/XPT2046_Touchscreen.git
 ******************************************************************************/

/* uncomment for GT911 */
 #define TOUCH_GT911
 #define TOUCH_GT911_SCL 20 
 #define TOUCH_GT911_SDA 19
 #define TOUCH_GT911_INT 0
 #define TOUCH_GT911_RST 38
 #define TOUCH_GT911_ROTATION ROTATION_INVERTED 
// Please fill below values from Arduino_GFX Example - TouchCalibration
bool touch_swap_xy = false;
int16_t touch_map_x1 = 0;
int16_t touch_map_x2 = 800;
int16_t touch_map_y1 = 0;
int16_t touch_map_y2 = 480;

int16_t touch_max_x = 0, touch_max_y = 0;
int16_t touch_raw_x = 0, touch_raw_y = 0;
int16_t touch_last_x = 0, touch_last_y = 0;


#include <Wire.h>
#include <TAMC_GT911.h>
TAMC_GT911 ts = TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, 4096, 4096);



void touch_init(int max_x, int max_y)
{
  touch_max_x = max_x;
  touch_max_y = max_y;

  Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
  ts.begin();
  ts.setRotation(TOUCH_GT911_ROTATION);

}

bool touch_has_signal()
{

  return true;

}

bool touch_touched()
{


  ts.read();
  if (ts.isTouched)
  {
    touch_raw_x = ts.points[0].x;
    touch_raw_y = ts.points[0].y;
    
    if (touch_swap_xy)
    {
      touch_last_x = map(touch_raw_y, touch_map_x1, touch_map_x2, 0, touch_max_x);
      touch_last_y = map(touch_raw_x, touch_map_y1, touch_map_y2, 0, touch_max_y);
    }
    else
    {
      touch_last_x = map(touch_raw_x, touch_map_x1, touch_map_x2, 0, touch_max_x);
      touch_last_y = map(touch_raw_y, touch_map_y1, touch_map_y2, 0, touch_max_y);
    }
    return true;
  }

  return false;
}

bool touch_released()
{
  return true;

}
