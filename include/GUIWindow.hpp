#pragma once

#include <SDL3/SDL.h>

class GUIView;

class GUIWindow
{
public:
    GUIWindow(const char *title, int windowWidth, int windowHeight, uint32_t windowFlags);
    ~GUIWindow();

    void MakeKey(SDL_GLContext&);
    void Render();
    void ImGuiRender();

    SDL_Window *getSDLWindow() const { return window; }

    GUIView *mainView;

private:
    SDL_Window *window;
    
    int frameBufferWidth;
    int frameBufferHeight;
};