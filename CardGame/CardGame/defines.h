#pragma once
#include <random>
#include <stdlib.h>
#include <chrono>
#include <thread>

//delay occurs with sleep
inline void sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#define CANVAS_WIDTH 24.0f
#define CANVAS_HEIGHT 17.0f

#define ASSET_PATH ".\\assets\\"

#define CARD_HEIGHT 2.5f   //card's height in canvas
#define CARD_WIDTH 2.0f    //card's width in canvas

#define SETCOLOR(c, r, g, b) {c[0] = r; c[1] = g; c[2] = b;} 

//returns the distace of two points
inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}



