#include <stdio.h>
#include <SDL2/SDL.h>

#include <time.h>
#include <stdlib.h>
#include "Game.h"

int main(int argc, char *argv[]){
  GameState Game;
  Game.done = 0;

  //Initializes SDL Library
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  srandom(time(NULL)); // "Seeds" the random number generator for eye and platform values

  //Creates a window/renderer and assigns it to to window/renderer
  Game.window = SDL_CreateWindow("Game window", 960*2.5,
  SDL_WINDOWPOS_CENTERED, 960, 540, 0);
  Game.renderer = SDL_CreateRenderer(Game.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  //Initializes TTF font system
  TTF_Init();

  //Initialize the mixer
  Mix_OpenAudio( 44100 , MIX_DEFAULT_FORMAT, 2, 2048);
printf("%s\n", SDL_GetError());
  loadGame(&Game);

  //main Game Loop
  while(!Game.done){
    processEvents(&Game);
    process(&Game);
    collisionDetect(&Game);
    render(&Game);
  }

  //cleanup
  Mix_FreeMusic(Game.bgMusic);
  Mix_FreeChunk(Game.land);
  Mix_FreeChunk(Game.jump);
  Mix_FreeChunk(Game.die);
  SDL_DestroyTexture(Game.eye->eye_tex);
  SDL_DestroyTexture(Game.man.man_tex);
  SDL_DestroyTexture(Game.platform->plat_tex);
  SDL_DestroyTexture(Game.man.FIRE);
  if(Game.text.label != NULL)
    SDL_DestroyTexture(Game.text.label);
  SDL_DestroyWindow(Game.window);
  SDL_DestroyRenderer(Game.renderer);
  TTF_CloseFont(Game.text.font);
	Mix_CloseAudio();
  TTF_Quit();
  SDL_Quit();
  return 0;
}
