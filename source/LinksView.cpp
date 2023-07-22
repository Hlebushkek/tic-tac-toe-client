#include <imgui.h>
#include "LinksView.hpp"

void LinksView::ImGuiRender()
{
    ImGui::BeginChild("Links", ImVec2(128.0f, 128.0f), true);
    {
        ImGui::Dummy(ImVec2(0.0f, 1.0f));
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Social");
        GUIView::ImGuiRender();
    }
    ImGui::EndChild();
}
