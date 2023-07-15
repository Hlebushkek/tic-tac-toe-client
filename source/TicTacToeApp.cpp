#include "TicTacToeApp.hpp"

TicTacToeApp *TicTacToeApp::application = nullptr;

TicTacToeApp::TicTacToeApp()
{
    InitWindow("TicTacToe", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    InitGLAD();
    InitGL();
    InitIMGUI();
}

TicTacToeApp::~TicTacToeApp()
{
    ImGui::DestroyContext(imguiContext);
    SDL_GL_DeleteContext(glContext);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
}

void TicTacToeApp::Run()
{
    while(!this->appShouldTerminate)
        this->Update();
}

void TicTacToeApp::Update()
{
    glClearColor(0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdateInput();

    mainWindow->Render();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    {
        mainWindow->ImGuiRender();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //Clean
    SDL_GL_SwapWindow(mainWindow->getSDLWindow());
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
    }
}

// INIT

void TicTacToeApp::InitWindow(const char *title, int windowWidth, int windowHeight, uint32_t windowFlags)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    mainWindow = new GUIWindow(title, windowWidth, windowHeight, windowFlags);

    glContext = SDL_GL_CreateContext(mainWindow->getSDLWindow());

    mainWindow->MakeKey(glContext);
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

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void TicTacToeApp::InitIMGUI()
{
    std::string glsl_version = "";
    glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    IMGUI_CHECKVERSION();
    imguiContext = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    
    ImGui_ImplSDL3_InitForOpenGL(mainWindow->getSDLWindow(), glContext);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}