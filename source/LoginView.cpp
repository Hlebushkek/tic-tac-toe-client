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
        // ImGui::Text("Username");
        ImGui::InputText("Username", loginBuffer, 128);
        // ImGui::Text("Password");
        ImGui::InputText("Password", passwordBuffer, 128, ImGuiInputTextFlags_Password);
        if (ImGui::Button("Login In"))
        {
            std::cout << "Login in with credentials: " << loginBuffer << " " << passwordBuffer << std::endl;
        }
        GUIView::ImGuiRender();
    }
    ImGui::End();
}
