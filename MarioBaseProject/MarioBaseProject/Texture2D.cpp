#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}
Texture2D::~Texture2D()
{
	
	//free up memory
	Free();
	m_renderer = nullptr;
	
}
bool Texture2D::LoadFromFile(std::string path)
{
	//remove memory used for previous texture
	Free();

	//load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0XFF, 0XFF));
		//create the texture from the pixels on the surface
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
		if (m_texture == nullptr)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		else
		{
			m_width = p_surface->w;
			m_height = p_surface->h;
		}
		//remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}
	return m_texture != nullptr;
}
void Texture2D::Free()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}
void Texture2D::Render(Vector2D new_postition, SDL_RendererFlip flip, double angle)
{
	//set where to render the texture
	SDL_Rect renderLocation = { new_postition.x,new_postition.y,m_width,m_height};
	//render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, NULL, &renderLocation, 0, NULL, flip);
}
void Texture2D::Render(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angle)
{
	//render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, &src_rect, &src_dest, angle, nullptr, flip);
}
