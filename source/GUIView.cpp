#include "GUIView.hpp"

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
