#include <iostream>
#include <SDL3/SDL_image.h>
#include "ImGuiImageTextButton.hpp"
#include "GUIWindow.hpp"
#include "GUIButton.hpp"

GUIButton::GUIButton(std::string title, std::string imagePath)
    : m_title(title), m_imagePath(imagePath), GUIView()
{
    
}

GUIButton::~GUIButton()
{
    SDL_DestroyTexture(texture);
}

void GUIButton::OnAttach()
{
    if (m_imagePath.empty())
        return;

    SDL_Surface* loadedSurface = IMG_Load(m_imagePath.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", m_imagePath.c_str(), IMG_GetError());
    }
    else
    {
        SDL_Renderer* renderer = window->getSDLRenderer();
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", m_imagePath.c_str(), SDL_GetError());
        }

        SDL_DestroySurface(loadedSurface);
    }
}

void GUIButton::ImGuiRender()
{
    if (!texture)
    {
        if (ImGui::Button(m_title.c_str()))
            buttonAction(this);
    }
    else
    {
        if (ImGui::ImageButtonWithText(reinterpret_cast<ImTextureID>(texture), m_title.c_str()))
            buttonAction(this);
    }
}