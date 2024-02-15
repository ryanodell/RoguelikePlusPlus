#include "backend.h"
#include "systems.h"
#include "math/vecs.h"

Coordinator gCoordinator;

///////////////////////////GAME////////////////////////////////////////
Game::Game(int width, int height, const char* windowTitle) : 
            mWidth(width), 
            mHeight(height), 
            mWindowTitle(windowTitle) {    
}
Game::~Game() {
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    mWindow = NULL;
    mRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

static std::shared_ptr<RenderSystem> renderSystem;

bool Game::Init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::LogError("There was an error initializing SDL || SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    mWindow = SDL_CreateWindow(mWindowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        mWidth, mHeight, SDL_WINDOW_SHOWN);
    if(mWindow == NULL) {
        Logger::LogError("Failed to initialize Window | SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    mRenderer = SDL_CreateRenderer(mWindow, 01, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(mRenderer == NULL) {
        Logger::LogError("Failed to initialize SDL Renderer | SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		Logger::LogError("SDL_Image could not be initialized. SDL_Image Error: %s\n", IMG_GetError());
        return false;
	}
    gCoordinator.Init();
    gCoordinator.RegisterComponent<Renderable>();
    gCoordinator.RegisterComponent<Camera>();
    gCoordinator.RegisterComponent<Player>();

    renderSystem = gCoordinator.RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(gCoordinator.GetComponentType<Renderable>());
        // signature.set(gCoordinator.GetComponentType<Camera>());
        // signature.set(gCoordinator.GetComponentType<Player>());
        gCoordinator.SetSystemSignature<RenderSystem>(signature);
    }
    renderSystem->Init(mRenderer);

    return true;
}

void Game::Run() {
    TextureManager textureManager;
    textureManager.Init(mRenderer);
    Texture2D* tex = textureManager.LoadTexture("../assets/curses_square_16x16.png");
    float tileSize = 16;
     SDL_Rect grassRect { 5 * tileSize, 0, tileSize, tileSize };
    int cols = 25;
    int rows = 15;
    for(int y = 0; y < rows; y++) {
        for(int x = 0; x < cols; x++) {
            //Entity tmp = gCoordinator.CreateEntity();
            gCoordinator.AddComponent(gCoordinator.CreateEntity(), Renderable{
                .Texture = tex,
                .Position =  Vec2(x * tileSize, y * tileSize), 
                .SourceRectangle = grassRect,
                .Color = Vec4(255, 255, 255, 0)
            });
        }
    }

    bool quit = false;
	SDL_Event e;
	while( !quit ) {
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
        renderSystem->Update(0.0f);
	}
}
///////////////////////////END GAME////////////////////////////////////////