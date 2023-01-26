// #define BLUEWIN
// #define TV55
// #define DENWIN01
// #define DENWIN02
// #define FIBO256
// #define BIGDENWIN
// #define LAUNDRYWIN
 #define DECKWINS
// #define DECKWIN01
// #define DECKWIN02

#ifndef ssid
  #define ssid "This"               // capable no-internet router
  #define pass "JorTor16"
  //#define ssid "MyAltice 5f7bb3"  // incapable internet router
  //#define pass "sienna-735-886"
#endif

#define BLUEWIN_W    32
#define BLUEWIN_H    128
#define TV55_W       0
#define TV55_H       128
#define DENWIN01_W   32
#define DENWIN01_H   128
#define DENWIN02_W   32
#define DENWIN02_H   128
#define FIBO256_W    0
#define FIBO256_H    128
#define BIGDENWIN_W  32
#define BIGDENWIN_H  128
#define LAUNDRYWIN_W 32
#define LAUNDRYWIN_H 128
#define DECKWIN01_W  32
#define DECKWIN01_H  128
#define DECKWIN02_W  32
#define DECKWIN02_H  128

#if defined(BLUEWIN)
  #define HOSTNAME "Blue Window"
  #define DATA_PIN       D4
  #define LED_TYPE  WS2812B
  #define COLOR_ORDER   GRB
  #define NUM_LED       224
  #define NUM_STRIPS      1
  #define NUM_LEDS NUM_LED * NUM_STRIPS
  #define MILLI_AMPS   4200
  #define HAS_MAP         1
  #define PUSHPULLDELAY   0
  #define XOFFSET         0
  #define YOFFSET        96
  #define BAND            0
  
#elif defined(TV55)
  #define HOSTNAME   "TV55"
  #define DATA_PIN       6
  #define LED_TYPE WS2812B
  #define COLOR_ORDER  GRB
  #define NUM_LED      229
  #define NUM_STRIPS     1
  #define NUM_LEDS NUM_LED * NUM_STRIPS
  #define MILLI_AMPS  4200
  #define HAS_MAP        1
  #define PUSHPULLDELAY  0
  #define XOFFSET BLUEWIN_W
  #define YOFFSET       32
  #define BAND           0
  
#elif defined(DENWIN01)
  #define HOSTNAME "Den Window 01"
  #define DATA_PIN       D4
  #define LED_TYPE  WS2812B
  #define COLOR_ORDER   GRB
  #define NUM_LED       134
  #define NUM_STRIPS      1
  #define NUM_LEDS NUM_LED * NUM_STRIPS
  #define MILLI_AMPS   1800
  #define HAS_MAP         1
  #define PUSHPULLDELAY   8
  #define XOFFSET BLUEWIN_W + TV55_W
  #define YOFFSET       164
  #define BAND            1
  
#elif defined(DENWIN02)
  #define HOSTNAME "Den Window 02"
  #define DATA_PIN       D4
  #define LED_TYPE  WS2812B
  #define COLOR_ORDER   GRB
  #define NUM_LED       134
  #define NUM_STRIPS      1
  #define NUM_LEDS NUM_LED * NUM_STRIPS
  #define MILLI_AMPS   1800
  #define HAS_MAP         1
  #define PUSHPULLDELAY   8
  #define XOFFSET BLUEWIN_W + TV55_W + DENWIN01_W + FIBO256_W
  #define YOFFSET       164
  #define BAND            2
  
#elif defined(FIBO256)
  #define HOSTNAME "Fibo-256"
  #define DATA_PIN       D5
  #define LED_TYPE  WS2812B
  #define COLOR_ORDER   GRB
  #define NUM_LED       256
  #define NUM_STRIPS      1
  #define NUM_LEDS NUM_LED * NUM_STRIPS
  #define MILLI_AMPS   7200
  #define HAS_MAP         1
  #define PUSHPULLDELAY   0
  #define XOFFSET BLUEWIN_W + TV55_W + DENWIN01_W >> 1
  #define YOFFSET       200
  #define BAND            9
  
#elif defined(BIGDENWIN)
  #define HOSTNAME "Big Den Window"
  #define DATA_PIN       D4
  #define LED_TYPE  WS2812B
  #define COLOR_ORDER   GRB
  #define NUM_LED       282
  #define NUM_STRIPS      1
  #define NUM_LEDS NUM_LED * NUM_STRIPS
  #define MILLI_AMPS   7200
  #define HAS_MAP         1
  #define PUSHPULLDELAY   0
  #define XOFFSET BLUEWIN_W + TV55_W + DENWIN01_W + FIBO256_W + DENWIN02_W
  #define YOFFSET         0
  #define BAND            3
  
#elif defined(LAUNDRYWIN)
  #define HOSTNAME "Laundry Window"
  #define DATA_PIN       D4
  #define LED_TYPE  WS2812B
  #define COLOR_ORDER   GRB
  #define NUM_LED       190
  #define NUM_STRIPS      1
  #define NUM_LEDS NUM_LED * NUM_STRIPS
  #define MILLI_AMPS   2000
  #define HAS_MAP         1
  #define PUSHPULLDELAY   6
  #define XOFFSET BLUEWIN_W + TV55_W + DENWIN01_W + FIBO256_W + DENWIN02_W + BIGDENWIN_W
  #define YOFFSET        96
  #define BAND            4
  
#elif defined(DECKWINS)
  #define HOSTNAME "Deck Windows"
  #define DATA_PIN       6
  #define DATA_PIN_2     7
  #define LED_TYPE  WS2812B
  #define COLOR_ORDER   GRB
  #define NUM_LED       282
  #define NUM_STRIPS      2
  #define NUM_LEDS NUM_LED * NUM_STRIPS
  #define MILLI_AMPS  10000
  #define HAS_MAP         1
  #define PUSHPULLDELAY   0
  #define XOFFSET BLUEWIN_W + TV55_W + DENWIN01_W + FIBO256_W + DENWIN02_W + BIGDENWIN_W + LAUNDRYWIN_W
  #define YOFFSET         0
  #define BAND            5
  
#elif defined(DECKWIN01)
  #define HOSTNAME "Deck Window 01"
  #define DATA_PIN       D4
  #define LED_TYPE  WS2812B
  #define COLOR_ORDER   GRB
  #define NUM_LED       282
  #define NUM_STRIPS      1
  #define NUM_LEDS NUM_LED * NUM_STRIPS
  #define MILLI_AMPS   4200
  #define HAS_MAP         1
  #define PUSHPULLDELAY   0
  #define XOFFSET BLUEWIN_W + TV55_W + DENWIN01_W + FIBO256_W + DENWIN02_W + BIGDENWIN_W + LAUNDRYWIN_W
  #define YOFFSET         0
  #define BAND            5
  
#elif defined(DECKWIN02)
  #define HOSTNAME "Deck Window 02"
  #define DATA_PIN       D4
  #define LED_TYPE  WS2812B
  #define COLOR_ORDER   GRB
  #define NUM_LED       282
  #define NUM_STRIPS      1
  #define NUM_LEDS NUM_LED * NUM_STRIPS
  #define MILLI_AMPS   4200
  #define HAS_MAP         1
  #define PUSHPULLDELAY   0
  #define XOFFSET BLUEWIN_W + TV55_W + DENWIN01_W + FIBO256_W + DENWIN02_W + BIGDENWIN_W + LAUNDRYWIN_W + DECKWIN01_W
  #define YOFFSET         0
  #define BAND            6
  
#endif

//#if HAS_MAP
  #include "Map.h"
//#endif

IPAddress multicast(224, 0, 1, 3);

IPAddress gateIP(192, 168, 137, 1);  
IPAddress  subIP(255, 255, 255, 0);

IPAddress masterP(192, 168, 137, 223);
#if defined(BLUEWIN)
  IPAddress ip(192, 168, 137, 231);
#elif defined(TV55)
  IPAddress ip(192, 168, 137, 232);
#elif defined(DENWIN01)
  IPAddress ip(192, 168, 137, 233);
#elif defined(DENWIN02)
  IPAddress ip(192, 168, 137, 234);
#elif defined(FIBO256)
  IPAddress ip(192, 168, 137, 235);
#elif defined(BIGDENWIN)
  IPAddress ip(192, 168, 137, 236);
#elif defined(LAUNDRYWIN)
  IPAddress ip(192, 168, 137, 237);
#elif defined(DECKWIN01)
  IPAddress ip(192, 168, 137, 238);
#elif defined(DECKWIN02)
  IPAddress ip(192, 168, 137, 239);
#elif defined(DECKWINS)
  IPAddress ip(192, 168, 137, 240);
#endif

unsigned int udpPort = 8888;
