#ifndef SYSTEMS_H
#define SYSTEMS_H
#include <SDL.h>
#include "core/ecs.h"
#include "components.h"

class RenderSystem : public System {
public:
    void Init(SDL_Renderer* renderer);
    void Update(float dt);
private:
    Entity mCamera;
    SDL_Renderer* mRenderer;
    SpriteBatch mSpriteBatch;
};


#endif