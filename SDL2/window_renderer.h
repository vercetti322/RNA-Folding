#pragma once

#include <iostream>
#include <SDL2/SDL.h>

SDL_Window* initWindow(const char* title, int width, int height);
SDL_Renderer* initRenderer(SDL_Window* window);
void handleEvents(bool& quit);
