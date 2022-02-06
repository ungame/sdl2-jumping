#include "Object.hpp"
#include "Input.hpp"
#include "Colors.hpp"
#include "Window.hpp"
#include "Time.hpp"

#include <SDL2/SDL.h>
#include <math.h>
#include <chrono>

Object::Object(int width, int height, int x, int y)
{
    _width = width;
    _height = height;
    _x = x - (width / 2);
    _y = y - height;

    _jumpForce = JUMP_FORCE;
    _isGround = true;
    _jumpStartedAt = nullptr;
}

void Object::update(float deltaTime)
{
    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_SPACE) && _isGround)
    {
        _isGround = false;
        _jumpStartedAt = new Time();

        SDL_Log("Jump started at %s. X=%lf, Y=%lf, JumpForce=%lf, DeltaTime=%f", _jumpStartedAt->toString().c_str(), _x, _y, _jumpForce, deltaTime);
    }

    if(!_isGround)
    {
        SDL_Log("Jumping. X=%lf, Y=%lf, JumpForce=%lf, DeltaTime=%f", _x, _y, _jumpForce, deltaTime);
        
        _y -= _jumpForce * deltaTime;
        _jumpForce -= (GRAVITY * deltaTime);
    }   

    bool isWalkRight = Input::Instance()->IsKeyDown(SDL_SCANCODE_D) || Input::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT);

    if(isWalkRight)
    {
        _x += WALK_SPEED * deltaTime;
    }
    
    bool isWalkLeft = Input::Instance()->IsKeyDown(SDL_SCANCODE_A) || Input::Instance()->IsKeyDown(SDL_SCANCODE_LEFT);

    if(isWalkLeft)
        _x -= WALK_SPEED * deltaTime;

    
    if((_x + _width) > WINDOW_WIDTH)
        _x = WINDOW_WIDTH - _width;

    if((_y + _height) > WINDOW_HEIGHT)
    {
        _y = WINDOW_HEIGHT - _height;
        _jumpForce = JUMP_FORCE;
        _isGround = true;
   

        double elapsed = Time::since(_jumpStartedAt);
        SDL_Log("End Jump. X=%lf, Y=%lf, JumpForce=%lf, DeltaTime=%f, Elapsed=%lf", _x, _y, _jumpForce, deltaTime, elapsed);

        _jumpStartedAt = nullptr;
        // _quit();
    }

    if(_y < 0)
        _y = 0;

    if(_x < 0)
        _x = 0;
}

void Object::draw(SDL_Renderer* renderer)
{
    SDL_Rect object = { (int) _x, (int) _y, _width, _height };
    SDL_SetRenderDrawColor(renderer, Black.r, Black.g, Black.b, Black.a);
    SDL_RenderFillRect(renderer, &object);
}