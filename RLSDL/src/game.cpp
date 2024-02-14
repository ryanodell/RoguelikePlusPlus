#include "backend.h"

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
    //gCoordinator.RegisterComponent<Renderable>();
    //gCoordinator.RegisterComponent<Camera>();
    gCoordinator.RegisterComponent<Player>();

    return true;
}

void Game::Run() {
    SpriteBatch spriteBatch = SpriteBatch(mRenderer);
    TextureManager textureManager;
    textureManager.Init(mRenderer);
    Texture2D* tex = textureManager.LoadTexture("../assets/curses_square_16x16.png");
    bool quit = false;
	SDL_Event e;
    Vector2D position = Vector2D(16, 32);
    float scale = 2.5f;
    float tileSize = 16;
    SDL_Rect grassRect { 5 * tileSize, 0, tileSize, tileSize };
    int cols = 25;
    int rows = 15;
    Vector2D tile1 = Vector2D(0 * tileSize, 0 * tileSize);
    Vector2D tile2 = Vector2D(1 * tileSize, 0 * tileSize);
    Vector2D tile3 = Vector2D(2 * tileSize, 0 * tileSize);

    Vector2D tile4 = Vector2D(0 * tileSize, 1 * tileSize);
    Vector2D tile5 = Vector2D(0 * tileSize, 2 * tileSize);
    Vector2D tile6 = Vector2D(0 * tileSize, 3 * tileSize);
	while( !quit ) {
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				quit = true;
			} else if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_w:
					position.Y -= 16;
					break;
					case SDLK_a:
					position.X -= 16;
					break;
					case SDLK_s:
					position.Y += 16;
					break;
					case SDLK_d:
					position.X += 16;
					break;
				}
			}        
		}
        SDL_RenderClear(mRenderer);
        SDL_Rect playerRect { 16, 0, 16, 16 };
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
        SDL_Color color = { 225, 255, 225 };
        SDL_Color grassColor = { 150, 160, 24 };
        
        spriteBatch.Begin();
        for(int y = 0; y < rows; y++) {
            for(int x = 0; x < cols; x++) {
                if(position.X == x * tileSize && position.Y == y * tileSize) {
                    continue;;
                }
                spriteBatch.Draw(tex, Vector2D(x * tileSize, y * tileSize), grassRect, grassColor);
            }
        }
        spriteBatch.Draw(tex, position, playerRect, color);
        spriteBatch.End();        
		SDL_RenderPresent(mRenderer);
	}
}
///////////////////////////END GAME////////////////////////////////////////