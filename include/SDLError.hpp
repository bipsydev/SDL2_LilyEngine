/* SDLError.hpp	-	Heather Crawford	-	07-08-2021
*
* #include this to log errors in SDL. error(message, error_type) will display your message along with the SDL error of specified type.
* ErrorType enum is used to enumerate the type of error and display relavent information from that subsystem.
*/
#pragma once
#ifndef _SDL2_ERROR_H_
#define _SDL2_ERROR_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>
#include <map>


/// <summary>
/// Enumeration of all SDL error types, NoneError being 0.
/// </summary>
enum ErrorType { NoneError, SDL, TTF };

/// <summary>
/// Map of ErrorType to display string.
/// </summary>
static std::map< ErrorType, std::string > errorString = {
   {NoneError, "None"},
   {SDL, "SDL"},
   {TTF, "SDL_TTF"}
};

/// <summary>
/// report an error to the console, with relevant SDL module error, and pause the console to read.
/// </summary>
/// <param name="message">Your message of the error.</param>
/// <param name="error_type">Optional, specify ErrorType SDL or TTF to report error from that module. Defaults to NoneError.</param>
void error(std::string message, ErrorType error_type = NoneError);


#endif /* _SDL2_ERROR_H_ */