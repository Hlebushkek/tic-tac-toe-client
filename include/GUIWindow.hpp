#pragma once

#include <SDL3/SDL.h>

class GUIView;

class GUIWindow
{
public:
    GUIWindow(const char *title, int windowWidth, int windowHeight, uint32_t windowFlags);
    ~GUIWindow();

    void Render();
    void ImGuiRender();

    SDL_Window *getSDLWindow() const { return window; }
    SDL_Renderer *getSDLRenderer() const { return renderer; }

    GUIView *mainView = nullptr;

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    
    int frameBufferWidth;
    int frameBufferHeight;
};