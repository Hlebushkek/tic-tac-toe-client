#include <imgui.h>
#include "GUIButton.hpp"

void GUIButton::ImGuiRender()
{
    if (ImGui::Button(title))
    {
        buttonAction(this);
    }
}