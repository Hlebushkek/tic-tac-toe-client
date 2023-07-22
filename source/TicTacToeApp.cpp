#include <SDL3/SDL_image.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include "TicTacToeApp.hpp"

TicTacToeApp *TicTacToeApp::application = nullptr;

TicTacToeApp::TicTacToeApp()
{
    InitWindow("TicTacToe", 800, 600, SDL_WINDOW_RESIZABLE);
    // InitGLAD();
    // InitGL();
    InitIMGUI();
    InitClient();
}

TicTacToeApp::~TicTacToeApp()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext(imguiContext);
}

void TicTacToeApp::Run()
{
    while(!this->appShouldTerminate)
        this->Update();
}

void TicTacToeApp::Update()
{
    UpdateInput();

    UpdateNet();

    mainWindow->Render();

    SDL_Renderer *renderer = mainWindow->getSDLRenderer();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::SetCurrentContext(imguiContext);
    {
        ImGui::ShowMetricsWindow();
        mainWindow->ImGuiRender();
    }
    ImGui::Render();

    SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderClear(renderer);

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
}

void TicTacToeApp::UpdateInput()
{
    while (SDL_PollEvent(&tempEvent))
    {
        ImGui_ImplSDL3_ProcessEvent(&tempEvent);

        if (tempEvent.type == SDL_EVENT_QUIT)
        {
            this->appShouldTerminate = true;
        }
        else if (tempEvent.type == SDL_EVENT_KEY_DOWN)
        {
            switch (this->tempEvent.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                client.pingServer();
                break;
            }
        }
    }
}

void TicTacToeApp::UpdateNet()
{
    if (client.isConnected())
    {
        if (!client.incoming().empty())
        {
            auto msg = client.incoming().pop_front().msg;

            switch (msg.header.id)
            {
            case TicTacToeMessage::ServerPing:
                std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
                std::chrono::system_clock::time_point timeThen;
                msg >> timeThen;
                std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
				break;
            }
        }
    }
}

// INIT

void TicTacToeApp::InitWindow(const char *title, int windowWidth, int windowHeight, uint32_t windowFlags)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    mainWindow = new GUIWindow(title, windowWidth, windowHeight, windowFlags);
}

void TicTacToeApp::InitGLAD()
{
    int status = gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);
    assert(status);
}

void TicTacToeApp::InitGL()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_TEXTURE_2D);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void TicTacToeApp::InitIMGUI()
{
    IMGUI_CHECKVERSION();
    imguiContext = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(mainWindow->getSDLWindow(), mainWindow->getSDLRenderer());
    ImGui_ImplSDLRenderer3_Init(mainWindow->getSDLRenderer());
}

void TicTacToeApp::InitClient()
{
    client.connect("127.0.0.1", 60000);
}
