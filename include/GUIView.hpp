#pragma once

#include <vector>

class GUIView
{
public:
    GUIView();
    ~GUIView();

    virtual void Render();
    virtual void ImGuiRender();

    void addSubview(GUIView *view);

    std::vector<GUIView*> subviews;
};