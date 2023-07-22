#pragma once

#include <iostream>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <imgui.h>

#include "GUIWindow.hpp"
#include "TicTacToeClient.hpp"

class TicTacToeClient;

class TicTacToeApp
{
public:
    TicTacToeApp();
    ~TicTacToeApp();

    void Run();
    void Update();

    GUIWindow *getMainWindow() const { return mainWindow; }

    TicTacToeClient &getClient() { return client; }

private:
    void UpdateInput();
    void UpdateNet();

private:
    void InitWindow(const char *title, int windowWidth, int windowHeight, uint32_t windowFlags);
    void InitGLAD();
    void InitGL();
    void InitIMGUI();
    void InitClient();

private:
    static TicTacToeApp *application;

    TicTacToeClient client;

    bool appShouldTerminate = false;

    SDL_Event tempEvent;

    ImGuiContext* imguiContext;

    GUIWindow *mainWindow;

};