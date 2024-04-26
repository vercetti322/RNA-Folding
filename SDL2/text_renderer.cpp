#include "text_renderer.h"

TextRenderer::TextRenderer(SDL_Renderer* renderer, TTF_Font* font)
    : m_renderer(renderer), m_font(font), m_texture(nullptr) { }

TextRenderer::~TextRenderer() 
{
    if (m_texture != nullptr)
        SDL_DestroyTexture(m_texture);
}

void TextRenderer::setText(const std::string& text) { m_text = text; }

void TextRenderer::setPosition(int x, int y) 
{
    m_dstRect.x = x;
    m_dstRect.y = y;
}

void TextRenderer::setColor(SDL_Color color) { m_color = color; }

void TextRenderer::render() {
    // Render text to surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);
    if (textSurface == nullptr) 
    {
        std::cerr << "Text rendering failed: " << TTF_GetError() << std::endl;
        return;
    }

    // Create texture from surface
    m_texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    if (m_texture == nullptr) 
    {
        std::cerr << "Texture creation failed: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    // Get the dimensions of the text
    m_dstRect.w = textSurface -> w;
    m_dstRect.h = textSurface -> h;

    // Free the surface
    SDL_FreeSurface(textSurface);

    // Copy texture to renderer
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_dstRect);
}
