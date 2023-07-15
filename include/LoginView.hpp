#pragma once

#include <string>
#include "GUIView.hpp"

class LoginView : public GUIView
{
public:
    void ImGuiRender() override;

private:
    char loginBuffer[128];
    char passwordBuffer[128];

};