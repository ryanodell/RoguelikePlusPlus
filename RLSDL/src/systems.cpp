#include "systems.h"
extern Coordinator gCoordinator;
/////////////////////////////////RENDER SYSTEM/////////////////////////

void RenderSystem::Init(SDL_Renderer* renderer) {
    mCamera = gCoordinator.CreateEntity();
    mSpriteBatch = SpriteBatch(renderer);
    // gCoordinator.AddComponent(mCamera, Camera {
    //     .Position = Vec2(),
    //     .Zoom = 1.0f
    // });
}


void RenderSystem::Update(float dt) {
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    mSpriteBatch.Begin();
    for (auto const& entity : mEntities) {
        
    }
    mSpriteBatch.End();
    SDL_RenderPresent(mRenderer);
}
/////////////////////////////////RENDER SYSTEM/////////////////////////