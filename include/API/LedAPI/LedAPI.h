#pragma once
#include "../API.h"
#include "FastLED.h"
#include <vector>

class LedAPI;

class LedAPI{
public:
	std::vector<CRGB> leds;
	LedAPI();

	void show();
	
};