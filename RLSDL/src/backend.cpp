#include "backend.h"

// ///////////////////////////GAME////////////////////////////////////////
// Game::Game(int width, int height, const char* windowTitle) : 
//             mWidth(width), 
//             mHeight(height), 
//             mWindowTitle(windowTitle) {    
// }
// Game::~Game() {
//     SDL_DestroyWindow(mWindow);
//     SDL_DestroyRenderer(mRenderer);
//     mWindow = NULL;
//     mRenderer = NULL;
//     IMG_Quit();
//     SDL_Quit();
// }
// bool Game::Init() {
//     if(SDL_Init(SDL_INIT_VIDEO) < 0) {
//         Logger::LogError("There was an error initializing SDL || SDL_Error: %s\n", SDL_GetError());
//         return false;
//     }
//     mWindow = SDL_CreateWindow(mWindowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
//         mWidth, mHeight, SDL_WINDOW_SHOWN);
//     if(mWindow == NULL) {
//         Logger::LogError("Failed to initialize Window | SDL_Error: %s\n", SDL_GetError());
//         return false;
//     }
//     mRenderer = SDL_CreateRenderer(mWindow, 01, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//     if(mRenderer == NULL) {
//         Logger::LogError("Failed to initialize SDL Renderer | SDL_Error: %s\n", SDL_GetError());
//         return false;
//     }
//     SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//     int imgFlags = IMG_INIT_PNG;
// 	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
// 		Logger::LogError("SDL_Image could not be initialized. SDL_Image Error: %s\n", IMG_GetError());
//         return false;
// 	}
//     return true;
// }

// void Game::Run() {
//     SpriteBatch spriteBatch = SpriteBatch(mRenderer);
//     TextureManager textureManager;
//     textureManager.Init(mRenderer);
//     Texture2D* tex = textureManager.LoadTexture("../assets/curses_square_16x16.png");
//     bool quit = false;
// 	SDL_Event e;
//     Vector2D position = Vector2D(16, 32);
//     float scale = 2.5f;
//     float tileSize = 16;
//     SDL_Rect grassRect { 5 * tileSize, 0, tileSize, tileSize };
//     int cols = 25;
//     int rows = 15;
//     Vector2D tile1 = Vector2D(0 * tileSize, 0 * tileSize);
//     Vector2D tile2 = Vector2D(1 * tileSize, 0 * tileSize);
//     Vector2D tile3 = Vector2D(2 * tileSize, 0 * tileSize);

//     Vector2D tile4 = Vector2D(0 * tileSize, 1 * tileSize);
//     Vector2D tile5 = Vector2D(0 * tileSize, 2 * tileSize);
//     Vector2D tile6 = Vector2D(0 * tileSize, 3 * tileSize);
// 	while( !quit ) {
// 		while( SDL_PollEvent( &e ) != 0 ) {
// 			if( e.type == SDL_QUIT ) {
// 				quit = true;
// 			} else if(e.type == SDL_KEYDOWN) {
// 				switch(e.key.keysym.sym) {
// 					case SDLK_w:
// 					position.Y -= 16;
// 					break;
// 					case SDLK_a:
// 					position.X -= 16;
// 					break;
// 					case SDLK_s:
// 					position.Y += 16;
// 					break;
// 					case SDLK_d:
// 					position.X += 16;
// 					break;
// 				}
// 			}        
// 		}
//         SDL_RenderClear(mRenderer);
//         SDL_Rect playerRect { 16, 0, 16, 16 };
//         SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
//         SDL_Color color = { 225, 255, 225 };
//         SDL_Color grassColor = { 150, 160, 24 };
        
//         spriteBatch.Begin();
//         for(int y = 0; y < rows; y++) {
//             for(int x = 0; x < cols; x++) {
//                 if(position.X == x * tileSize && position.Y == y * tileSize) {
//                     continue;;
//                 }
//                 spriteBatch.Draw(tex, Vector2D(x * tileSize, y * tileSize), grassRect, grassColor);
//             }
//         }
//         spriteBatch.Draw(tex, position, playerRect, color);
//         spriteBatch.End();        
// 		SDL_RenderPresent(mRenderer);
// 	}
// }
// ///////////////////////////END GAME////////////////////////////////////////

///////////////////////////TEXTURE2D////////////////////////////////////////
Texture2D::Texture2D(SDL_Texture* texture, int width, int height) 
    : mInternalTexture(texture), mWidth(width), mHeight(height) { }

Texture2D::~Texture2D() {
    if(mInternalTexture != NULL) {
        SDL_DestroyTexture(mInternalTexture);
        mInternalTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
///////////////////////////END TEXTURE2D////////////////////////////////////////

///////////////////////////TEXTUREMANAGER////////////////////////////////////////
void TextureManager::Init(SDL_Renderer *renderer) {
    mRenderer = renderer;
}

Texture2D* TextureManager::LoadTexture(const char* name) {
    auto it = mTextureCache.find(name);
    if(it == mTextureCache.end()) {
        if(_loadTextureCache(name) == false) {            
             Logger::LogError("Failed to load %s into the texture cache\n", name);            
            return nullptr;
        } 
    }
    return mTextureCache[name].get();
}
bool TextureManager::_loadTextureCache(const char *name) {
    SDL_Texture* newTexture;
    SDL_Surface* loadedSurface = IMG_Load(name);
    if(loadedSurface == NULL) {
        Logger::LogError("Failed to load surface | IMG_Error: %s\n", IMG_GetError());
        return false;
    } else {
        SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
        Uint32 magentaColor = SDL_MapRGB(formattedSurface->format, 255, 0, 255);
        SDL_SetColorKey(formattedSurface, SDL_TRUE, magentaColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, formattedSurface);
        if(texture == NULL) {
            Logger::LogError("Failed to create texture from surface | SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        mTextureCache[name] = std::make_shared<Texture2D>(texture, loadedSurface->w, loadedSurface->h);
        SDL_FreeSurface(loadedSurface);
        SDL_FreeSurface(formattedSurface);        
    }
    return true;
}

///////////////////////////END TEXTUREMANAGER////////////////////////////////////////

/////////////////////////////// RENDERER/////////////////////////////////////////////
Renderer::Renderer(SDL_Renderer *renderer) : mRenderer(renderer) { }

void Renderer::Draw(Texture2D *texture, float x, float y, SDL_Rect rec, SDL_Color color) {
    SDL_SetTextureColorMod(texture->GetInternalTexture(), color.r, color.g, color.b);
     SDL_Rect dst = {x, y, rec.w, rec.h };
    //*2 to double the size
    //SDL_Rect dst = {x, y, rec.w * 2, rec.h * 2};
    SDL_RenderCopy(mRenderer, texture->GetInternalTexture(), &rec, &dst);
}
void Renderer::Draw(Texture2D *texture, Vector2D position, SDL_Rect rec, SDL_Color color) {
    Draw(texture, position.X, position.Y, rec, color);
}
void Renderer::Draw(Texture2D *texture, Vector2D position, SDL_Rect rec, float scale, SDL_Color color) {
    SDL_SetTextureColorMod(texture->GetInternalTexture(), color.r, color.g, color.b);
    SDL_Rect dst = {position.X * scale, position.Y * scale, rec.w * scale, rec.h * scale };
    SDL_RenderCopy(mRenderer, texture->GetInternalTexture(), &rec, &dst);
}
////////////////////////////////END RENDERER////////////////////////////////////////

Camera2D::Camera2D() : Position(0.0f, 0.0f), Zoom(1.0f) { }
Camera2D::Camera2D(Vector2D position, float zoom) : Position(position), Zoom(zoom) { }
Camera2D::~Camera2D() { }
////////////////////////////////VECTOR2D////////////////////////////////////////////
Vector2D::Vector2D(float x, float y) : X(x), Y(y) { }
////////////////////////////////END VECTOR2D////////////////////////////////////////

////////////////////////////////SPRITEBATCH///////////////////////////////////////////////
SpriteBatch::SpriteBatch(SDL_Renderer *renderer, size_t batchSize)  : mRenderer(renderer), mMaxBatchSize(batchSize) {
    mBatch.reserve(mMaxBatchSize);
}

SpriteBatch::~SpriteBatch() { }

void SpriteBatch::Begin(const Camera2D &cam) {

}

void SpriteBatch::Begin() {
}

void SpriteBatch::Draw(Texture2D *texture, Vector2D position, SDL_Rect rec, SDL_Color color) {
    if(mBatch.size() > mMaxBatchSize) {
        flush();
    }
    mBatch.push_back({ texture, position, rec, color });
}

void SpriteBatch::End() {
    
    flush();
}

void SpriteBatch::flush() {
    //Loop And Draw
    for(int i = 0; i < mBatch.size(); i++) {
        SpriteBatchItem sprite = mBatch[i];        
        SDL_SetTextureColorMod(sprite.Texture, sprite.Color.r, sprite.Color.g, sprite.Color.b);
        SDL_Rect dst = {sprite.X, sprite.Y, sprite.SourceRect.w, sprite.SourceRect.h };
        SDL_RenderCopy(mRenderer, sprite.Texture, &sprite.SourceRect, &dst);
    }
    //Clear
    mBatch.clear();
}

////////////////////////////////END SPRITEBATCH////////////////////////////////////////////

//////////////////////////////////SpriteBatchItem////////////////////////////////////////////
SpriteBatchItem::SpriteBatchItem(Texture2D *texture, Vector2D position, SDL_Rect src, SDL_Color color) {
    Texture = texture->GetInternalTexture();
    X = position.X;
    Y = position.Y;
    SourceRect = src;
    Color = color;
}

////////////////////////////////END SpriteBatchItem////////////////////////////////////////////





















//Version 1 before spriteBatching
// void Game::Run() {
//     Renderer rend = Renderer(mRenderer);
//     TextureManager textureManager;
//     textureManager.Init(mRenderer);
//     Texture2D* tex = textureManager.LoadTexture("../assets/curses_square_16x16.png");
//     bool quit = false;
// 	SDL_Event e;
//     Vector2D position = Vector2D(16, 32);
//     float scale = 2.5f;
//     float tileSize = 16;
//     SDL_Rect grassRect { 5 * tileSize, 0, tileSize, tileSize };
//     Vector2D tile1 = Vector2D(0 * tileSize, 0 * tileSize);
//     Vector2D tile2 = Vector2D(1 * tileSize, 0 * tileSize);
//     Vector2D tile3 = Vector2D(2 * tileSize, 0 * tileSize);

//     Vector2D tile4 = Vector2D(0 * tileSize, 1 * tileSize);
//     Vector2D tile5 = Vector2D(0 * tileSize, 2 * tileSize);
//     Vector2D tile6 = Vector2D(0 * tileSize, 3 * tileSize);
// 	while( !quit ) {
// 		while( SDL_PollEvent( &e ) != 0 ) {
// 			if( e.type == SDL_QUIT ) {
// 				quit = true;
// 			} else if(e.type == SDL_KEYDOWN) {
// 				switch(e.key.keysym.sym) {
// 					case SDLK_w:
// 					position.Y -= 16;
// 					break;
// 					case SDLK_a:
// 					position.X -= 16;
// 					break;
// 					case SDLK_s:
// 					position.Y += 16;
// 					break;
// 					case SDLK_d:
// 					position.X += 16;
// 					break;
// 				}
// 			}        
// 		}
//         SDL_RenderClear(mRenderer);
//         SDL_Rect rect { 16, 0, 16, 16 };
//         SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
//         SDL_Color color = { 225, 255, 225 };
//         SDL_Color grassColor = { 150, 160, 24 };
//         //rend.Draw(tex, 16, 32, rect, color);
//         rend.Draw(tex, tile1, grassRect, scale, grassColor);
//         rend.Draw(tex, tile2, grassRect, scale, grassColor);
//         rend.Draw(tex, tile3, grassRect, scale, grassColor);
//         rend.Draw(tex, tile4, grassRect, scale, grassColor);
//         rend.Draw(tex, tile5, grassRect, scale, grassColor);
//         rend.Draw(tex, tile6, grassRect, scale, grassColor);
//         rend.Draw(tex, position, rect, scale, color);
        
// 		SDL_RenderPresent(mRenderer);
// 	}
// }