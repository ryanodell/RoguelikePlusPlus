#include "systems.h"
extern Coordinator gCoordinator;
/////////////////////////////////RENDER SYSTEM/////////////////////////

void RenderSystem::Init(SDL_Renderer* renderer) {
    mRenderer = renderer;
    // gCoordinator.AddComponent(mCamera, Camera {
    //     .Position = Vec2(),
    //     .Zoom = 1.0f
    // });
}


void RenderSystem::Update(float dt) {
    SDL_Color grassColor = { 150, 160, 24 };
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    for (auto const& entity : mEntities) {
        auto const& renderable = gCoordinator.GetComponent<Renderable>(entity);
        SDL_SetTextureColorMod(renderable.Texture->GetInternalTexture(), renderable.Color.X, renderable.Color.Y, renderable.Color.Z);
        SDL_Rect dst = {renderable.Position.X, renderable.Position.Y, renderable.SourceRectangle.w, renderable.SourceRectangle.h };
        SDL_RenderCopy(mRenderer, renderable.Texture->GetInternalTexture(), &renderable.SourceRectangle, &dst);
        //SDL_RenderPresent(mRenderer);
    }
    SDL_RenderPresent(mRenderer);
}
/////////////////////////////////RENDER SYSTEM/////////////////////////