#pragma once

#include <string>
#include "GUIView.hpp"

class LoginView : public GUIView
{
public:
    void ImGuiRender() override;

    std::string getLogin()
    {
        return std::string(loginBuffer);
    }

    std::string getPassword()
    {
        return std::string(passwordBuffer);
    }
    
private:
    char loginBuffer[128];
    char passwordBuffer[128];

};