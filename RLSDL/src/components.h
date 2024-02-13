#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <SDL.h>
#include "backend.h"
#include "math/vecs.h"

struct Renderable {    
    Texture2D* Texture;
    Vec2 Position;
    SDL_Rect SourceRectangle;
    Vec4 Color;
};

struct Player { };

struct Camera { 
    Vec2 Position;
    float Zoom;
};

#endif