#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>

#include "Time.hpp"

#define GRAVITY 1.0f
#define WALK_SPEED 4.0f
#define JUMP_FORCE 20.0f

class Object
{
    public:
        Object(int width, int height, int x, int y);
        void update(float deltaTime);
        void draw(SDL_Renderer* renderer);

    private:
        float _x, _y;
        int _width, _height;
        float _jumpForce;
        bool _isGround;
        Time* _jumpStartedAt;

        void _quit()
        {
            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
        }
};

#endif