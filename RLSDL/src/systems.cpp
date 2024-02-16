#include "systems.h"
extern Coordinator gCoordinator;
/////////////////////////////////RENDER SYSTEM/////////////////////////

void RenderSystem::Init(SDL_Renderer* renderer) {
    mRenderer = renderer;
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

void PlayerControlSystem::Init() {

}

void PlayerControlSystem::Update(float dt) {
    SDL_Event e;
    bool quit = false;
    while( SDL_PollEvent( &e ) != 0 ) {
		if( e.type == SDL_QUIT ) {
			quit = true;
		} else if(e.type == SDL_KEYDOWN) {
			switch(e.key.keysym.sym) {
				case SDLK_w:
				//position.Y -= 16;
				break;
				case SDLK_a:
				//position.X -= 16;
				break;
				case SDLK_s:
				//position.Y += 16;
				break;
				case SDLK_d:
				//position.X += 16;
				break;
			}
		}        
	}
}
