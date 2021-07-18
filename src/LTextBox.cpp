/* LTextBox.cpp	-	Heather Crawford	-	07-08-2021
*
* This is a text box that holds a text message and rect, with color and texture.
*/
#include "BaseGame.hpp"

#include "LTextBox.hpp"
#include "SDLError.hpp"
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

		create_surface();

		setRectCenter();
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

	/**
	 * @brief Creates the SDL_Surface from the saved font, text, and color.
	 * 
	 * @return true if successful, false if not.
	 */
	bool LTextBox::create_surface()
	{
		// as TTF_RenderText_Solid could only be used on
		// SDL_Surface then you have to create the surface first
		message_surface = TTF_RenderText_Solid(font, text.c_str(), color);
		if (message_surface == NULL)
		{
			error("TTF_RenderText_Solid failed", TTF);
			return false;
		}
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


	/**
	 * @brief Sets the text box to the center of the screen, center axis.
	 * 
	 */
	void LTextBox::setRectCenter()
	{
		SDL_Point surf_size = getSurfaceSize();
		SDL_Point win_size = LilyEngine::instance->getWindowSize();
		int bx = (win_size.x / 2) - (surf_size.x / 2);
		int by = (win_size.y / 2) - (surf_size.y / 2);
		SDL_Rect center_rect = SDL_Rect{ bx, by, surf_size.x, surf_size.y };
		setRect(center_rect);
	}
	
	void LTextBox::setSize(SDL_Point point) 
	{
		setSize(point.x, point.y);
	}
	
	void LTextBox::setSize(int width, int height) 
	{
		SDL_Rect new_rect = getRect();
		new_rect.w = width;
		new_rect.h = height;
		setRect(new_rect);
	}
	
	SDL_Point LTextBox::getSize() 
	{
		return SDL_Point{box.w, box.h};
	}

	void LTextBox::setPosition(SDL_Point newPos)
	{
		SDL_Rect new_rect = getRect();
		new_rect.x = newPos.x;
		new_rect.y = newPos.y;
		setRect(new_rect);
	}
	SDL_Point LTextBox::getPosition()
	{
		return SDL_Point{box.x, box.y};
	}
	
	/**
	 * @brief Get's the width and height of the text surface.
	 * 
	 * @return SDL_Point with width and height of the text surface.
	 */
	SDL_Point LTextBox::getSurfaceSize() 
	{
		return SDL_Point{message_surface->w, message_surface->h};
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
