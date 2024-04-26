#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class TextRenderer 
{
public:
    TextRenderer(SDL_Renderer* renderer, TTF_Font* font);
    ~TextRenderer();

    void setText(const std::string& text);
    void setPosition(int x, int y);
    void setColor(SDL_Color color);
    void render();

private:
    SDL_Renderer* m_renderer;
    TTF_Font* m_font;
    std::string m_text;
    SDL_Color m_color;
    SDL_Texture* m_texture;
    SDL_Rect m_dstRect;
};
