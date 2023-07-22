#pragma once

#include <vector>

class GUIWindow;

class GUIView
{
public:
    GUIView();
    ~GUIView();

    virtual void Render();
    virtual void ImGuiRender();

    virtual void OnAttach();
    virtual void OnDetach();

    void addSubview(GUIView *view);

    std::vector<GUIView*> subviews;

    GUIWindow *getWindow() { return window; }
    void setWindow(GUIWindow *window) { this->window = window; }

protected:
    GUIWindow *window = nullptr;
};