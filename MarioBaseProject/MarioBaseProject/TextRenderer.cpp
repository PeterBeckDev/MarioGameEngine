#include "TextRenderer.h"
#include <iostream>

TextRenderer::TextRenderer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	
}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::Render(int x, int y)
{
	textRect.x = x;
	//textRect.w = x;
	textRect.y = y;
	//textRect.h = y;
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &textRect);
	if (SDL_RenderCopy(m_renderer, m_texture, nullptr, &textRect) == 0)
	{
	}
}

bool TextRenderer::LoadFont(const std::string path, int fontSize, const std::string message, SDL_Color color)
{
	font = TTF_OpenFont(path.c_str(),fontSize);
	
	if (!font)
	{
		std::cout << "Could not load font.\n";
		return false;
	}

	
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, message.c_str(), color);
	if (!text_surface)
	{
		std::cout << "Could not load surface: \n" << TTF_GetError();
		return false;
	}
	m_texture = SDL_CreateTextureFromSurface(m_renderer,text_surface);
	if (!m_texture)
	{
		std::cout << "Could not load texture: \n" << TTF_GetError();
		return false;
	}

	
	TTF_CloseFont(font);
	font = nullptr;
	SDL_FreeSurface(text_surface);
	text_surface = nullptr;
	if (SDL_QueryTexture(m_texture, nullptr, nullptr, &textRect.w, &textRect.h) != 0)
	{
		return false;
	}
	 
	 return m_texture;

	
}