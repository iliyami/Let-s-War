
//Using SDL and standard IO
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "tank.h"
#include "Bullet.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 790;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();



//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Renders


//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Surface for loading png images (except map)
SDL_Surface* gSurface1 = NULL;
SDL_Surface* gSurface2 = NULL;

//The image we will load and show on the screen
SDL_Surface* gMap= NULL;

//Textures
SDL_Texture* gTexture1 = NULL, * gTexture2 = NULL;

//keyboard states
const Uint8 *state = SDL_GetKeyboardState(NULL);

//rects
SDL_Rect grect1; //Tank1 rect
SDL_Rect grect2; //Tank2 rect

//Events
SDL_Event e;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Let's war", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
		    gScreenSurface = SDL_GetWindowSurface( gWindow );
			gSurface1 = SDL_LoadBMP("tank1.bmp");
   			gTexture1 = SDL_CreateTextureFromSurface(gRenderer, gSurface1);
    		gSurface2 = SDL_LoadBMP("tank2.bmp");
  			gTexture2 = SDL_CreateTextureFromSurface(gRenderer, gSurface2);
    		//gSurface = IMG_Load("laser.png");
    		// glaser = SDL_CreateTextureFromSurface(gRenderer, gSurface);
	  		 gtank1.x = -1 * rand()%1280+1;
    		 gtank1.y = -1 * rand()%790+1;
			 //grect1 = {gtank1.x, gtank1.y, 1280, 790};
    		 do
    		 {
        	 	gtank2.x = -1 * rand()%1280+1;
        	 	gtank2.y = -1 * rand()%790+1;
    		 } while (gtank1.x == gtank2.x && gtank1.y == gtank2.y);
			 //grect2 = {gtank2.x,gtank2.y,1280,790};
		}
	}

	return success;
}

bool loadMedia(int cn)
{
	//Loading success flag
	bool success = true;

	//Load random image
    
 	if(cn==1)
    {gMap = SDL_LoadBMP("map1.bmp");}
    if(cn==2)
    {gMap = SDL_LoadBMP("map2.bmp");}
    if(cn==3)
    {gMap = SDL_LoadBMP("map3.bmp");}
	
	if( gMap == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "map.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

bool Tank(SDL_Event e, bool *quit)
{

SDL_PollEvent(&e);
    if (state[SDL_SCANCODE_LEFT])
        degree1 -= 0.2;
    if (state[SDL_SCANCODE_RIGHT])
        degree1 += 0.2;
    if (state[SDL_SCANCODE_A])
        degree2 -= 0.2;
    if (state[SDL_SCANCODE_D])
        degree2 += 0.2;

    if (degree1 > 180)
        degree1 = -180;
    if (degree1 < -180)
        degree1 = 180;
    if (degree2 > 180)
        degree2 = -180;
    if (degree2 < -180)
        degree2 = 180;
if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_KP_0)
    {
        if (gtank1.bullet <= 5)
        {
            gtank1.bullet++;
            gbullet1[gtank1.bullet - 1].lastTimeball = SDL_GetTicks();
            gbullet1[gtank1.bullet - 1].value = 1;
            gbullet1[gtank1.bullet - 1].x = gtank1.x + (25 * cos(-degree1 * 3.14 / 180));
            gbullet1[gtank1.bullet - 1].y = gtank1.y - (25 * sin(-degree1 * 3.14 / 180));
            gbullet1[gtank1.bullet - 1].xdelta = 0.1 * cos(-degree1 * 3.14 / 180);
            gbullet1[gtank1.bullet - 1].ydelta = 0.1 * sin(-degree1 * 3.14 / 180);
        }
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2)
    {
        if (gtank2.bullet <= 5)
        {
            gtank2.bullet++;
            gbullet2[gtank2.bullet - 1].lastTimeball = SDL_GetTicks();
            gbullet2[gtank2.bullet - 1].value = 1;
            gbullet2[gtank2.bullet - 1].x = gtank2.x + (25 * cos(-degree2 * 3.14 / 180));
            gbullet2[gtank2.bullet - 1].y = gtank2.y - (25 * sin(-degree2 * 3.14 / 180));
            gbullet2[gtank2.bullet - 1].xdelta = 0.1 * cos(-degree2 * 3.14 / 180);
            gbullet2[gtank2.bullet - 1].ydelta = 0.1 * sin(-degree2 * 3.14 / 180);
        }
    }
    if (e.type == SDL_QUIT)
    {
        *quit = true;
    }
    grect1 = {gtank1.x - 25, gtank1.y - 25, 50, 50};
    grect2 = {gtank2.x - 25, gtank2.y - 25, 50, 50};
    return true;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gMap );
	//SDL_FreeSurface( gSurface1);
	//SDL_FreeSurface( gSurface2 );
	gMap = NULL;
	//gSurface1 = NULL;
	//gSurface2 = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	
    srand(time(0));
    int cn=rand()%3+1;
	//Start up SDL and create window
    
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//For closing the program
		// bool quit=false;
		// SDL_Event e;

			//Load media
			if( !loadMedia(cn) )
			{
				printf( "Failed to load media!\n" );
			}
			else
			{
				//Apply the image
				SDL_BlitSurface( gMap, NULL, gScreenSurface, NULL );
				SDL_BlitSurface( gSurface1, &grect1, gScreenSurface, NULL );
				SDL_BlitSurface( gSurface2, &grect2, gScreenSurface, NULL );

				//Update the surface
				SDL_UpdateWindowSurface( gWindow );

				SDL_Delay(5000);
			}
			
			close();
	}


	return 0;
}

   

