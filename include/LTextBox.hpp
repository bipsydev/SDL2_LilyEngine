/* LTextBox.hpp	-	Heather Crawford	-	07-08-2021
*
* This is a text box that holds a text message and rect, with color and texture.
*/
#pragma once
#ifndef _SDL2_LTEXTBOX_H_
#define _SDL2_LTEXTBOX_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

/*
* Creates a Text box message out of an LFont, holds message texture, rect, and parent font.
*/
class LTextBox
{
private:
	TTF_Font* font;
	std::string text;
	SDL_Rect box;
	SDL_Color color;

	SDL_Surface* message_surface = nullptr;
	SDL_Texture* message_texture = nullptr;

public:
	LTextBox(TTF_Font* font, std::string text, SDL_Color color = { 0xFF, 0xFF, 0xFF });
	~LTextBox();

	void setText(std::string newText);
	std::string getText();

	void setColor(SDL_Color newColor);
	SDL_Color getColor();

	void setRect(SDL_Rect newBox);
	SDL_Rect getRect();

	void setFont(TTF_Font* newFont);
	TTF_Font* getFont();

	bool render(SDL_Renderer* renderer);

private:
	bool create_texture(SDL_Renderer* renderer);

};


#endif /* _SDL2_LTEXTBOX_H_ */