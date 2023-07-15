#pragma once

#include <iostream>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>

#include "GUIWindow.hpp"

class TicTacToeApp
{
public:
    TicTacToeApp();
    ~TicTacToeApp();

    void Run();
    void Update();

    GUIWindow *getMainWindow() const { return mainWindow; }

private:
    void UpdateInput();

private:
    void InitWindow(const char *title, int windowWidth, int windowHeight, uint32_t windowFlags);
    void InitGLAD();
    void InitGL();
    void InitIMGUI();

private:
    static TicTacToeApp *application;

    bool appShouldTerminate = false;

    SDL_Event tempEvent;

    SDL_GLContext glContext;
    ImGuiContext* imguiContext;

    GUIWindow *mainWindow;

};