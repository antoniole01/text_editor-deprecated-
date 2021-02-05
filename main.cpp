#include <iostream>

#include <sdl.h>
#include <sdl_ttf.h>

#include "c:\z\_MI\Window.h"
#include "c:\z\_MI\LTexture.h"
#include "c:\z\_MI\defines.h"
#include "c:\z\_MI\colors.h"
#include "c:\z\_MI\drawFontSolid.h"
#include "c:\z\_MI\drawshapes.h"

#undef main

SDL_Renderer*  renderer;
SDL_Window*    window;
SDL_Event      e;

SDL_Texture*	solidTexture;
SDL_Texture*	text;
SDL_Rect			solidRect;
TTF_Font*		gFont;

LTexture gcmap;
SDL_Rect gMapSpriteClips[ 1 ];

float FPS     = 1000 / 33.3f;
bool  running = true;

static int         letter = 0;
static std::string s;
const char*        c = s.c_str() ;
char               cstring[1000];

#define k(a,b)																			\
			if(letter < a){ if(SPACE) { b[letter] = ' '; letter++; } }	\
         if(letter < a){ if(A_KEY) { b[letter] = 'a'; letter++; } }	\
         if(letter < a){ if(B_KEY) { b[letter] = 'b'; letter++; } }	\
         if(letter < a){ if(C_KEY) { b[letter] = 'c'; letter++; } }	\
         if(letter < a){ if(D_KEY) { b[letter] = 'd'; letter++; } }	\
         if(letter < a){ if(E_KEY) { b[letter] = 'e'; letter++; } }	\
         if(letter < a){ if(F_KEY) { b[letter] = 'f'; letter++; } }	\
         if(letter < a){ if(G_KEY) { b[letter] = 'g'; letter++; } }	\
         if(letter < a){ if(H_KEY) { b[letter] = 'h'; letter++; } }	\
         if(letter < a){ if(I_KEY) { b[letter] = 'i'; letter++; } }	\
         if(letter < a){ if(J_KEY) { b[letter] = 'j'; letter++; } }	\
         if(letter < a){ if(K_KEY) { b[letter] = 'k'; letter++; } }	\
         if(letter < a){ if(L_KEY) { b[letter] = 'l'; letter++; } }	\
         if(letter < a){ if(M_KEY) { b[letter] = 'm'; letter++; } }	\
         if(letter < a){ if(N_KEY) { b[letter] = 'n'; letter++; } }	\
         if(letter < a){ if(O_KEY) { b[letter] = 'o'; letter++; } }	\
         if(letter < a){ if(P_KEY) { b[letter] = 'p'; letter++; } }	\
         if(letter < a){ if(Q_KEY) { b[letter] = 'q'; letter++; } }	\
         if(letter < a){ if(R_KEY) { b[letter] = 'r'; letter++; } }	\
         if(letter < a){ if(S_KEY) { b[letter] = 's'; letter++; } }	\
         if(letter < a){ if(T_KEY) { b[letter] = 't'; letter++; } }	\
         if(letter < a){ if(U_KEY) { b[letter] = 'u'; letter++; } }	\
         if(letter < a){ if(V_KEY) { b[letter] = 'v'; letter++; } }	\
         if(letter < a){ if(W_KEY) { b[letter] = 'w'; letter++; } }	\
         if(letter < a){ if(X_KEY) { b[letter] = 'x'; letter++; } }	\
         if(letter < a){ if(Y_KEY) { b[letter] = 'y'; letter++; } }	\
         if(letter < a){ if(Z_KEY) { b[letter] = 'z'; letter++; } }	\

bool loadMedia()
{
	bool success = true;
	if(!gcmap.loadFromFile("c:/z/_MI/data/font/cmap2.png"))  {printf("Failed!\n");success = false;}
	return success;
}

int draw_char(char c, int x, int y)
{
	char *map[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
						"abcdefghijklmnopqrstuvwxyz",
						"!@#$%^&*()_+{}|:\"<>?,.;'-=",
						"0123456789"};
	
	for(int i = 0; i < 4; i++)
	{
		for(unsigned int j = 0; j < strlen(map[i]); j++)
		{
			if(c == map[i][j])
			{
				gMapSpriteClips[ 0 ].x = 20*j;
				gMapSpriteClips[ 0 ].y = 20*i;
				gMapSpriteClips[ 0 ].w = 20;
				gMapSpriteClips[ 0 ].h = 20;
				gcmap.render(x,y,1,1,gMapSpriteClips);	
				return(0);
			}
		}
	}
	return 0;
}

void draw_string(char s[], int x, int y)
{
	for(unsigned int i = 0; i < strlen(s); i++)
	{
		draw_char(s[i],x,y);
		x += 20;
	}
}

void input()
{ 
   if(POLLEVENT)
   {
      if(QUIT){exit(0);}
		if(DOWNPRESS)
		{
			if(RIGHT) {letter++;}
			if(LEFT)  {letter--;}
			if(BACKSPACE) { cstring[letter] = ' '; letter--; cstring[letter] = ' '; }

		}
      if(UPPRESS)
      {
         if(ESCAPE) {exit(0);}
			k(20,cstring)
			
      }
   }
}

bool       blinking  = false;
static int blink     = 0;
static int blinkhold = 0;

const int SCREEN_WIDTH  = 800/2;
const int SCREEN_HEIGHT = 600/2;

void draw_alphabet()
{
   draw_string("ABCDEFGHIJKLMNOPQRS", 0, 0);
	draw_string("TUVWXYZ", 0, 20);

	draw_string("abcdefghijklmnopqrs", 0, 40);
	draw_string("tuvwxyz", 0, 60);
}

void sdl_font()
{
	drawFontSolid(0,0,0,0,0,c,WHITE,"c:/z/_MI/data/font/arial.ttf",18);
}

void blink_cursor()
{
	if(blinking)
	{
		drawFillRect((20*letter),0,20,20,CYAN);
	}
}

void draw()
{
	SDL_SetRenderDrawColor(renderer,BLACK);
	SDL_RenderClear(renderer);  
	
	drawFillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,PURPLE);
	
	drawFillRect( 0,0,10,10,GRAY );//test alpha

	blink_cursor();
	sdl_font();
	//draw_alphabet();
	
	draw_string(cstring, 0, 0);

	if( letter <   0  ){ letter = 0;    }
	if( letter > 20-1 ){ letter = 20-1; }

	SDL_RenderPresent(renderer);
}

void update()
{
	SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS,"0");
	
	int blinkspeeda = 15;
	int blinkspeedb = 15;
	if(blink > blinkspeeda)
	{
		blinkhold++;
		if(blinkhold > blinkspeedb)
		{
			blinkhold = 0;
			blink = 0;
		}
		blinking = false;
	}
	else
	{
		blinking = true;
	}
	blink++;
	
	SDL_Delay(1000/33);
	//SDL_Delay(1000/33);
}

int main()
{
	init_Window(200,200,SCREEN_WIDTH,SCREEN_HEIGHT,3,1);
	loadMedia();
	
	while(running)
	{
		input();
		draw();
		update();;
	}
		
	return(0);
}
