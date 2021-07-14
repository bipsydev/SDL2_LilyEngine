/* SDLError.cpp	-	Heather Crawford	-	07-08-2021
*
* Use this to log errors in SDL. error(message, error_type) will display your message along with the SDL error of specified type.
*/

#include "SDLError.hpp"
#include <string>

/// <summary>
/// report an error to the console, with relevant SDL module error, and pause the console to read.
/// </summary>
/// <param name="message">Your message of the error.</param>
/// <param name="error_type">Optional, specify ErrorType SDL or TTF to report error from that module. Defaults to NoneError.</param>
void error(std::string message, ErrorType error_type)
{
	std::string sdl_message;
	switch (error_type) {
	case SDL:
		sdl_message = SDL_GetError();
		break;
	case TTF:
		sdl_message = TTF_GetError();
		break;
	default:
		sdl_message = "Unknown";
	}
	std::cout << message << std::endl;
	if (error_type != NoneError)
		std::cout << errorString[error_type] << " Error: " << sdl_message << std::endl;
	system("pause");
}