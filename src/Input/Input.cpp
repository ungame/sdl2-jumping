#include "Input.hpp"

#include <SDL2/SDL.h>

Input* Input::_input = nullptr;

Input::Input()
{
    _keyboard = SDL_GetKeyboardState(nullptr);
    _mouse = 0;
}

bool Input::Listen()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return false;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
           _keyboard = SDL_GetKeyboardState(nullptr);
           break;

        case SDL_MOUSEBUTTONDOWN:
            _mouse = event.button.button;
            break;

        case SDL_MOUSEBUTTONUP:
            _mouse = 0;

        default:
            break;
        }
    }

    return true;
}

bool Input::IsKeyDown(SDL_Scancode key)
{
    return _keyboard[key] == 1;
}

bool Input::IsMouseKeyDown(MouseKey key)
{
    if(key == MouseKey::BUTTON_LEFT)
        return _mouse == SDL_BUTTON_LEFT;

    if(key == MouseKey::BUTTON_RIGHT)
        return _mouse == SDL_BUTTON_RIGHT;

    return false;     
}