#include <iostream>
#include <SDL3/SDL.h>
#include "GUIView.hpp"
#include "GUIWindow.hpp"

GUIWindow::GUIWindow(const char *title, int windowWidth, int windowHeight, uint32_t windowFlags)
{
    window = SDL_CreateWindow(title, windowWidth, windowHeight, windowFlags);
    renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);
    mainView = new GUIView();
    mainView->setWindow(this);
    SDL_GetWindowSizeInPixels(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
}

GUIWindow::~GUIWindow()
{
    if (mainView != nullptr)
        delete mainView;

    SDL_DestroyWindow(window);
}

void GUIWindow::Render()
{
    if (mainView != nullptr)
        mainView->Render();
}

void GUIWindow::ImGuiRender()
{
    if (mainView != nullptr)
        mainView->ImGuiRender();
}
