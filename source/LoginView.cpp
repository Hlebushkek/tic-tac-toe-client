#include <iostream>
#include <SDL3/SDL.h>
#include <imgui.h>
#include "LoginView.hpp"    

void LoginView::ImGuiRender()
{
    ImGui::Begin("Login");
    {
        ImGui::Dummy(ImVec2(0.0f, 1.0f));
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Login");
        ImGui::InputText("Username", loginBuffer, 128);
        ImGui::InputText("Password", passwordBuffer, 128, ImGuiInputTextFlags_Password);
        
        GUIView::ImGuiRender();
    }
    ImGui::End();
}
