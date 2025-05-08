#pragma once

#define FULLSCREEN

// if FULLSCREEN defined use full monitor resolutions
#ifdef FULLSCREEN

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#else

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 900

#endif

#define REFRESH_RATE 60
#define REFRESH_RATE_DELAY 1000 / REFRESH_RATE