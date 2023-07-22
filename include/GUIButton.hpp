#pragma once

#include <functional>
#include <string>
#include "GUIView.hpp"

class GUIButton : public GUIView
{
public:
    GUIButton(std::string title = "Button", std::string imagePath = "");
    ~GUIButton();

    void OnAttach() override;

    void ImGuiRender() override;
    
    void setButtonAction(std::function<void(GUIView*)> action)
    {
        buttonAction = action;
    }

private:
    SDL_Texture *texture = nullptr;
    std::string m_title = "Button";
    std::string m_imagePath = "";

    std::function<void(GUIView*)> buttonAction;

};