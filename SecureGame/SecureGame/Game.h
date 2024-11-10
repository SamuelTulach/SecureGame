#pragma once

class Game
{
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    TTF_Font* m_Font = nullptr;

    void RenderText(const char* text, int x, int y);
    void Tick();
public:
    bool Init();
    void Loop();
};