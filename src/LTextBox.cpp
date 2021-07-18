/* LTextBox.cpp	-	Heather Crawford	-	07-08-2021
*
* This is a text box that holds a text message and rect, with color and texture.
*/
#include "LTextBox.hpp"
#include <iostream>

namespace LilyEngine
{

	/*
	* LTextBox - holds surface & texture for text box message created based on font passed.
	*/

	LTextBox::LTextBox(TTF_Font* font, std::string text, SDL_Color color)
	{
		LTextBox::font = font;
		LTextBox::text = text;
		LTextBox::color = color;

		// as TTF_RenderText_Solid could only be used on
		// SDL_Surface then you have to create the surface first
		message_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	}

	LTextBox::~LTextBox()
	{
		// free our resources
		SDL_FreeSurface(message_surface);
		SDL_DestroyTexture(message_texture);
	}


	bool LTextBox::render(SDL_Renderer* renderer)
	{
		// if we need to make the texture,
		if (message_texture == nullptr)
		{
			// give it the renderer here
			bool success = create_texture(renderer);
			if (!success) return false;
		}
		// draw the texture
		SDL_RenderCopy(renderer, message_texture, NULL, &box);

		return true;
	}

	bool LTextBox::create_texture(SDL_Renderer* renderer)
	{
		// now you can convert it into a texture using the renderer
		message_texture = SDL_CreateTextureFromSurface(renderer, message_surface);
		if (message_texture == NULL) {
			return false;
		}
		else {
			return true;
		}
	}

	/*
	* Getters and Setters
	*/

	void LTextBox::setText(std::string newText) { text = newText; }
	std::string LTextBox::getText() { return text; }

	void LTextBox::setColor(SDL_Color newColor) { color = newColor; }
	SDL_Color LTextBox::getColor() { return color; }

	void LTextBox::setRect(SDL_Rect newBox) { box = newBox; }
	SDL_Rect LTextBox::getRect() { return box; }

	void LTextBox::setFont(TTF_Font* newFont) { font = newFont; }
	TTF_Font* LTextBox::getFont() { return font; }

}
