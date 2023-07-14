#define SDL_MAIN_HANDLED
#include <iostream>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>

void initOpenGLOptions()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main()
{
    // SDL / GL init
    SDL_GLContext glCtx;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Hello World", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    glCtx = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glCtx);
    SDL_PumpEvents();

    int status = gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);
    assert(status);

    initOpenGLOptions();

    // IMGUI init
    std::string glsl_version = "";
    glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    IMGUI_CHECKVERSION();
    ImGuiContext *imguiCtx = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    
    ImGui_ImplSDL3_InitForOpenGL(window, glCtx);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    bool shouldTerminate = false;
    SDL_Event event;

    while(!shouldTerminate)
    {
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
        }

        // IMGUI Begin
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // IMGUI CYCLE
        ImGui::SetCurrentContext(imguiCtx);
        ImGui::Begin("Settings");

        static int counter = 0;
        
        int sdl_width = 300, sdl_height = 300, controls_width = 0;
        controls_width = sdl_width;
        if ((controls_width /= 3) < 300) { controls_width = 300; }

        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(
            ImVec2(static_cast<float>(controls_width), static_cast<float>(sdl_height - 20)),
            ImGuiCond_Always
            );

        ImGui::Dummy(ImVec2(0.0f, 1.0f));
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Platform");
        ImGui::Text("%s", SDL_GetPlatform());
        ImGui::Text("CPU cores: %d", SDL_GetCPUCount());
        ImGui::Text("CPU cache size: %d", SDL_GetCPUCacheLineSize());
        ImGui::Text("RAM: %.2f GB", SDL_GetSystemRAM() / 1024.0f);
        if (ImGui::Button("Counter button"))
        {
            std::cout << "counter button clicked\n";
            counter++;
        }
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::End();

        // IMGUI END
        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Clean
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext(imguiCtx);

    return 0;
}