#pragma once

#include <functional>
#include <string>
#include "GUIView.hpp"

class GUIButton : public GUIView
{
public:
    void ImGuiRender() override;
    
    void setButtonAction(std::function<void(GUIView*)> action)
    {
        buttonAction = action;
    }

    const char *title = "Button";

private:
    std::function<void(GUIView*)> buttonAction;

};