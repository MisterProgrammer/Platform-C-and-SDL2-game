#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "Game.h"

void renderEyes(GameState *gamestate);
void renderMan(GameState *gamestate);
void renderPlatforms(GameState *gamestate);
void renderProgressBar(GameState *gamestate);

void render(GameState *gamestate){

  switch(gamestate->statusState){
    //renders menu state
    case STATUS_STATE_MENU:
    draw_status_menu(gamestate);
    break;
    //renders lives state
    case STATUS_STATE_LIVES:
    draw_status_lives(gamestate);
    break;
    //renders game state
    case STATUS_STATE_GAME:

        //renders BackgroundColor
        SDL_SetRenderDrawColor(gamestate->renderer, 135, 206, 235, 255);
        SDL_RenderClear(gamestate->renderer);
        //Renders Objects
        renderEyes(gamestate);
        renderPlatforms(gamestate);
        renderMan(gamestate);
        //Renders Progress Bar
        renderProgressBar(gamestate);

    break;
    //renders gameover state
    case STATUS_STATE_GAMEOVER:
      draw_status_gameover(gamestate);
    break;

  }
  //updates the screen with previously rendered stuff
  SDL_RenderPresent(gamestate->renderer);
}



void renderEyes(GameState *gamestate){

  //Renders the Illuminati background
  for (int i = 0; i < NUM_STARS; i++){
    SDL_Rect eye = {gamestate->Scrollx+gamestate->eye[i].x,gamestate->eye[i].y,gamestate->eye[i].w,gamestate->eye[i].h};
    SDL_RenderCopy(gamestate->renderer, gamestate->eye->eye_tex, NULL, &eye);
  }

}
void renderPlatforms(GameState *gamestate){
  //Renders all the platforms
  for (int i = 0; i < NUM_PLATFORMS; i++){
    SDL_Rect Platform = {gamestate->Scrollx+gamestate->platform[i].x,gamestate->platform[i].y,
      gamestate->platform[i].w,gamestate->platform[i].h};
      SDL_RenderCopy(gamestate->renderer, gamestate->platform->plat_tex, NULL, &Platform);
    }

  }

  void renderMan(GameState *gamestate){

    //Renders the man player
    SDL_Rect Player = {gamestate->Scrollx+gamestate->man.x,gamestate->man.y,gamestate->man.w,gamestate->man.h};
    SDL_RenderCopy(gamestate->renderer, gamestate->man.man_tex[gamestate->man.aniFrame], NULL, &Player);

    //Renders flame if dead
    if(!gamestate->man.alive){
      SDL_Rect Player = {gamestate->Scrollx+gamestate->man.x,gamestate->man.y,gamestate->man.w,gamestate->man.h};
      SDL_RenderCopyEx(gamestate->renderer, gamestate->man.FIRE, NULL, &Player, 0, NULL, (gamestate->time%20 < 10));
    }

  }
  void renderProgressBar(GameState *gamestate){
    //Renders backgroundBar
    SDL_SetRenderDrawColor(gamestate->renderer, 90, 90, 90, 255);
    SDL_Rect Bar_back = {960/2-300/2,10,300,50};
    SDL_RenderFillRect(gamestate->renderer, &Bar_back);
    //Renders the animated Progress Bar
    SDL_SetRenderDrawColor(gamestate->renderer, 255, 255, 255, 255);
    SDL_Rect Progress_Bar = {960/2-300/2,10,300*(gamestate->man.x/30000),50};
    SDL_RenderFillRect(gamestate->renderer, &Progress_Bar);
  }
