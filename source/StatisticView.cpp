#include <SDL3/SDL.h>
#include <imgui.h>
#include "StatisticView.hpp"    

void StatisticView::ImGuiRender()
{
    ImGui::BeginChild("Statistic", ImVec2(250.0f, 130.0f), true);
    {
        static int counter = 0;
        
        ImGui::Dummy(ImVec2(0.0f, 1.0f));
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Platform");
        ImGui::Text("%s", SDL_GetPlatform());
        ImGui::Text("CPU cores: %d", SDL_GetCPUCount());
        ImGui::Text("CPU cache size: %d", SDL_GetCPUCacheLineSize());
        ImGui::Text("RAM: %.2f GB", SDL_GetSystemRAM() / 1024.0f);
        if (ImGui::Button("Counter button"))
        {
            counter++;
        }
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        GUIView::ImGuiRender();
    }
    ImGui::EndChild();
}