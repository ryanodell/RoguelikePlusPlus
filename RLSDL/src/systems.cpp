#include "systems.h"
extern Coordinator gCoordinator;
/////////////////////////////////RENDER SYSTEM/////////////////////////

void RenderSystem::Init(SDL_Renderer* renderer) {
    mCamera = gCoordinator.CreateEntity();
    // gCoordinator.AddComponent(mCamera, Camera {
    //     .Position = Vec2(),
    //     .Zoom = 1.0f
    // });
}


void RenderSystem::Update(float dt) {

}
/////////////////////////////////RENDER SYSTEM/////////////////////////