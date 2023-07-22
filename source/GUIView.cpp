#include <iostream>
#include "GUIView.hpp"
#include "GUIWindow.hpp"

GUIView::GUIView()
{
    
}

GUIView::~GUIView()
{

}

void GUIView::Render()
{
    for (auto subview : this->subviews)
        subview->Render();
}

void GUIView::ImGuiRender()
{
    for (auto subview : this->subviews)
        subview->ImGuiRender();
}

void GUIView::OnAttach()
{

}

void GUIView::OnDetach()
{

}

void GUIView::addSubview(GUIView *view)
{
    view->setWindow(window);
    view->OnAttach();
    this->subviews.emplace_back(view);
}
