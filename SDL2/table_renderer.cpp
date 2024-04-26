#include "table_renderer.h"
#include "text_renderer.h"

TableRenderer::TableRenderer(SDL_Renderer* renderer, TTF_Font* font, int numRows, int numCols, int startX, int startY, int cellWidth, int cellHeight)
    : m_renderer(renderer), m_font(font), m_numRows(numRows), m_numCols(numCols), m_startX(startX), m_startY(startY), m_cellWidth(cellWidth), m_cellHeight(cellHeight) {
    // Initialize table with initial values (0s)
    m_table.resize(numRows, std::vector<int>(numCols, 0));
}

TableRenderer::~TableRenderer() {}

void TableRenderer::setCellValue(int row, int col, int value) 
{
    if (row >= 0 && row < m_numRows && col >= 0 && col < m_numCols) 
    {
        m_table[row][col] = value;
    }
}

void TableRenderer::render() 
{
    for (int i = 0; i < m_numRows; ++i) 
    {
        for (int j = 0; j < m_numCols; ++j) 
        {
            // Calculate position of cell
            int posX = m_startX + j * m_cellWidth;
            int posY = m_startY + i * m_cellHeight;

            // Render cell background (if needed)
            SDL_Rect cellRect = {posX, posY, m_cellWidth, m_cellHeight};
            SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(m_renderer, &cellRect);

            // Render text within cell
            std::string cellText = std::to_string(m_table[i][j]);
            TextRenderer cellRenderer(m_renderer, m_font);
            cellRenderer.setText(cellText);
            cellRenderer.setPosition(posX, posY);
            cellRenderer.setColor({0, 0, 0, 255});
            cellRenderer.render();
        }
    }
}
