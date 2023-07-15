#pragma once

#include <vector>

class GUIView
{
public:
    GUIView();
    ~GUIView();

    virtual void Render();
    virtual void ImGuiRender();

    std::vector<GUIView*> subviews;
};