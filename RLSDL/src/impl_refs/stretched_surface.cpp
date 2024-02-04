#include <SDL.h>
#include <windows.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Surface* imageSurface = NULL;
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

SDL_Surface* loadSurface(const char* path) {
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError() );
	} else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, 0 );
		if( optimizedSurface == NULL ) {
			printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	return optimizedSurface;
}

bool loadMedia(const char* path) {
	imageSurface = loadSurface(path);
	if(imageSurface == NULL) {
		printf("THere was an error loading %s. SDL Error: %s\n", path, SDL_GetError());
		return false;
	}
	return true;
}

void close() {
	SDL_FreeSurface(imageSurface);
	imageSurface = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL Could not be initialized. SDL Error: %s\n", SDL_GetError());
		return false;
	} else {
		window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		} else {
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return true;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	printf("Test");
	if(!init()) {
		printf("Failed to initialize\n");
		return -1;
	} else {
		if(!loadMedia("../assets/curses_square_16x16.bmp")) {
			printf("Failed to load media\n");
			return -1;
		} else {
			//Original
			// SDL_BlitSurface(imageSurface, NULL, screenSurface, NULL);

			//Updated:
			SDL_Rect rect;
			rect.x = 0;
			rect.y = 0;
			rect.w = SCREEN_WIDTH;
			rect.h = SCREEN_HEIGHT;
			SDL_BlitScaled(imageSurface, NULL, screenSurface, &rect);
 			SDL_UpdateWindowSurface(window);
			SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
		}
	}
    return 0;
}