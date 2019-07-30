#include <stdio.h>
#include "Game.h"

// MENU STATUS
void init_status_menu(GameState *game){
  SDL_Color white = {255,255,255,255};

  SDL_Surface *tmp = TTF_RenderText_Blended(game->menu.StartGame.text.font, "Start Game", white);
  game->menu.StartGame.text.label = SDL_CreateTextureFromSurface(game->renderer, tmp);game->menu.StartGame.text.w = tmp->w;
  game->menu.StartGame.text.h = tmp->h;
  SDL_FreeSurface(tmp);
}

void draw_status_menu(GameState *game){

  //Draws The Menu Background based on a screenshot of the game
  SDL_Rect background = {0,0,980 ,560};
  SDL_RenderCopy(game->renderer, game->menu.menuTex , NULL, &background);


  SDL_Rect music = {game->menu.Music.x,game->menu.Music.y,game->menu.Music.w,game->menu.Music.h};
  if(game->musicMuted){
    SDL_RenderCopy(game->renderer, game->menu.nomusicTex , NULL, &music);
  }else{
    SDL_RenderCopy(game->renderer, game->menu.musicTex , NULL, &music);
  }


  SDL_Rect sound = {game->menu.Sound.x,game->menu.Sound.y,game->menu.Sound.w,game->menu.Sound.h};
  if(game->soundMuted){
    SDL_RenderCopy(game->renderer, game->menu.nosoundTex , NULL, &sound);
  }else{
      SDL_RenderCopy(game->renderer, game->menu.soundTex , NULL, &sound);
  }

  //Creates a startgame button
  SDL_Rect StartButton = {game->menu.StartGame.x,game->menu.StartGame.y,game->menu.StartGame.w,game->menu.StartGame.h};

  //when mouse is over that button,button goes from gray to blue
  if(game->menu.StartGame.mouseOver){
    game->menu.StartGame.r = 90;
    game->menu.StartGame.g = 160;
    game->menu.StartGame.b = 160;
  }else {
    game->menu.StartGame.r = 90;
    game->menu.StartGame.g = 90;
    game->menu.StartGame.b = 90;

  }


  //Renders the StartButton
  SDL_SetRenderDrawColor(game->renderer, game->menu.StartGame.r, game->menu.StartGame.g, game->menu.StartGame.b, 255);
  SDL_RenderFillRect(game->renderer, &StartButton);


  //Renders Text
  SDL_Rect textRect = {960/2-game->menu.StartGame.text.w/2,750/2-game->menu.StartGame.text.h/2,game->menu.StartGame.text.w,game->menu.StartGame.text.h};
  SDL_RenderCopy(game->renderer, game->menu.StartGame.text.label , NULL, &textRect);

}

void shutdown_status_menu(GameState *game){

  //destroys the textures from the menu
  SDL_DestroyTexture(game->menu.menuTex);
  game->menu.menuTex = NULL;
  SDL_DestroyTexture(game->menu.StartGame.text.label);
  game->menu.StartGame.text.label = NULL;

}

// LIVES STATUS
void init_status_lives(GameState *game){

  //creates a string for the text
  char str[128] = "";

  //inserts the lives variable into the string
  sprintf(str, "x %u",game->man.lives);

  //Initializes the text for the lives
  SDL_Color white = {255,255,255,255};
  SDL_Surface *tmp = TTF_RenderText_Blended(game->text.font, str, white);
  game->text.label = SDL_CreateTextureFromSurface(game->renderer, tmp);
  game->text.w = tmp->w;
  game->text.h = tmp->h;
  SDL_FreeSurface(tmp);
}
void draw_status_lives(GameState *game){
  //renders BackgroundColor
  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderClear(game->renderer);

  //Renders the man image
  SDL_Rect Player = {900/2-game->man.w*3/2,540/2-game->man.h*3/2,game->man.w*3,game->man.h*3};
  SDL_RenderCopy(game->renderer, game->man.man_tex[game->man.aniFrame], NULL, &Player);

  //Renders Text
  SDL_Rect textRect = {1070/2-game->text.w/2,550/2-game->text.h/2,game->text.w,game->text.h};
  SDL_RenderCopy(game->renderer, game->text.label , NULL, &textRect);

}
void shutdown_status_lives(GameState *game){
  SDL_DestroyTexture(game->text.label);
  game->text.label = NULL;
}

// GAME OVER STATUS
void init_status_gameover(GameState *game){

  //Initializes the text for the gameover
  SDL_Color white = {255,255,255,255};
  SDL_Surface *tmp = TTF_RenderText_Blended(game->text.font, "GameOver", white);
  game->text.label = SDL_CreateTextureFromSurface(game->renderer, tmp);
  game->text.w = tmp->w;
  game->text.h = tmp->h;
  SDL_FreeSurface(tmp);
}

void draw_status_gameover(GameState *game){
  //renders BackgroundColor
  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderClear(game->renderer);

  //Renders Text
  SDL_Rect textRect = {960/2-game->text.w/2,540/2-game->text.h/2,game->text.w,game->text.h};
  SDL_RenderCopy(game->renderer, game->text.label , NULL, &textRect);

}

void shutdown_status_gameover(GameState *Game){
  Game->done = 1;
}
