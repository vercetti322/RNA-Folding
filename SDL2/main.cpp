#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "window_renderer.h"
#include "text_renderer.h"
#include "table_renderer.h"

int main() {
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // initialize SDL_ttf
    if (TTF_Init() < 0) {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create window and renderer
    SDL_Window* window = initWindow("SDL Text", 1280, 960);
    SDL_Renderer* renderer = initRenderer(window);

    // Load the font
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSerif.ttf", 30); // Reduced font size
    if (font == nullptr) {
        std::cerr << "Font loading failed: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Create text renderer for upper quadrant
    TextRenderer textRenderer(renderer, font);
    textRenderer.setText("ABSBSBD");
    textRenderer.setPosition(200, 200);
    textRenderer.setColor({0, 0, 0, 255});

    // Create table renderers for lower quadrants
    int tableWidth = 8; // Reduced table size
    int tableHeight = 8; // Reduced table size
    int tableCellSize = 50; // Reduced cell size
    int thirdQuadX = 120; // Position of the first table in the third quadrant
    int thirdQuadY = 380; // Position of the first table in the third quadrant
    int fourthQuadX = 760; // Position of the second table in the fourth quadrant
    int fourthQuadY = 380; // Position of the second table in the fourth quadrant

    TableRenderer table1(renderer, font, tableWidth, tableHeight, thirdQuadX, thirdQuadY, tableCellSize, tableCellSize);
    TableRenderer table2(renderer, font, tableWidth, tableHeight, fourthQuadX, fourthQuadY, tableCellSize, tableCellSize);

    bool quit = false;

    // Event loop
    while (!quit) {
        // Handle events
        handleEvents(quit);

        // Render upper quadrant content (text)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        textRenderer.render();

        // Render lower quadrant content (tables)
        table1.render();
        table2.render();

        // Update the window
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}



