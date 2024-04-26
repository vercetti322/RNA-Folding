#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>

class TableRenderer {
public:
    TableRenderer(SDL_Renderer* renderer, TTF_Font* font, int numRows, int numCols, int startX, int startY, int cellWidth, int cellHeight);
    ~TableRenderer();

    void setCellValue(int row, int col, int value);
    void render();

private:
    SDL_Renderer* m_renderer;
    TTF_Font* m_font;
    int m_numRows;
    int m_numCols;
    int m_startX;
    int m_startY;
    int m_cellWidth;
    int m_cellHeight;
    std::vector<std::vector<int>> m_table;
};
