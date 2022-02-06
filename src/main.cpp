#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.hpp"
#include "Input.hpp"
#include "Colors.hpp"
#include "Object.hpp"

#define TARGET_FPS 60
#define SECOND 1000.0f

int main(int argc, char* argv[])
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl init failed with error: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    int imgInitted = IMG_Init(imgFlags);

    if((imgInitted&imgFlags) != imgFlags)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl img init failed with error: %s", IMG_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Jumping", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    
    if(window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create window failed with error: %s", SDL_GetError());
        return EXIT_FAILURE; 
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create renderer failed with error: %s", SDL_GetError());
        return EXIT_FAILURE;         
    }

    Object* object = new Object(50, 50, WINDOW_WIDTH / 2, WINDOW_HEIGHT);

    float startFrame = 0;
    float lastFrame = 0;
    float frameTime = 0;
    float deltaTime = 1.5f;

    while(Input::Instance()->Listen())
    {
        startFrame = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, White.r, White.g, White.b, White.a);
        SDL_RenderClear(renderer);

        object->update(deltaTime);
        object->draw(renderer);

        SDL_RenderPresent(renderer);
        
        
        frameTime = startFrame - lastFrame;
        lastFrame = startFrame;

        deltaTime = frameTime * (TARGET_FPS / SECOND);
        
        if (deltaTime > 1.5f)
            deltaTime = 1.5f;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}