#pragma once
#ifndef _TEXTRENDERER_H
#define _TEXTRENDERER_H
#include <string>
#include <SDL_ttf.h>

class TextRenderer
{
public:
	TextRenderer(SDL_Renderer* renderer);
	~TextRenderer();
	void Render(int x, int y);
	bool LoadFont(const std::string path, int fontSize, const std::string message, SDL_Color color);
private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Rect textRect;
	TTF_Font* font;
};
#endif

