#include <SDL3/SDL.h>
#include <imgui.h>
#include "LinksView.hpp"    

void LinksView::ImGuiRender()
{
    ImGui::BeginChild("Links", ImVec2(100.0f, 100.0f), true);
    {
        ImGui::Dummy(ImVec2(0.0f, 1.0f));
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Social");
        ImGui::Text("GitHub:");
        ImGui::Text("Our Team: ");
        GUIView::ImGuiRender();
    }
    ImGui::EndChild();
}
