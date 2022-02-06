#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

enum MouseKey { 
    NONE,
    BUTTON_LEFT, 
    BUTTON_RIGHT 
};

class Input {
    
    public:
        bool Listen();
        bool IsKeyDown(SDL_Scancode key);
        bool IsMouseKeyDown(MouseKey key);
        static inline Input* Instance() { return _input = _input != nullptr ? _input : new Input(); }

    private:
        Input();
        static Input* _input;
        const Uint8* _keyboard;
        Uint8 _mouse;

};

#endif