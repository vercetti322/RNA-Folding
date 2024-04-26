#include "window_renderer.h"

SDL_Window* initWindow(const char* title, int width, int height) 
{
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
    return window;
}

SDL_Renderer* initRenderer(SDL_Window* window) 
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
    return renderer;
}

void handleEvents(bool& quit) 
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_QUIT)
            quit = true;
    }
}
