#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <SDL.h>
#include "backend.h"
#include "math/vecs.h"

class Texture2D;

struct Renderable {    
    Texture2D* Texture;
    Vec2 Position;
    SDL_Rect SourceRectangle;
    Vec4 Color;
    // Renderable(Texture2D* texture, Vec2 position, SDL_Rect sourceRect, Vec4 color) 
    //     : Texture(texture), Position(position), SourceRectangle(sourceRect), Color(color) { }
};

struct Player { };

struct Camera { 
    Vec2 Position;
    float Zoom;
};

#endif