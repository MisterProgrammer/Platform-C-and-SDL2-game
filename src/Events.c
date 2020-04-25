#include <stdio.h>
#include "Game.h"
#include <SDL2/SDL.h>
#include <math.h>

void processEvents(GameState *game){
  int mousex,mousey;
  SDL_Event event;
  //get filthy keyboard input *FILTHYYY*
  while(SDL_PollEvent(&event)){
    switch(event.type){

      case SDL_WINDOWEVENT_CLOSE:
      if(game->window){
        SDL_DestroyWindow(game->window);
        game->done = 1;
        break;
      }
      case SDL_MOUSEMOTION:

      break;
      //press down key events
      case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        game->done = 1;
        break;
        case SDLK_UP:
        if (game->man.isOnPlatform){
          game->man.dy = -8;
          if(game->man.isOnPlatform == 1){ //plays jump sound effect if he is on platform
          if(!game->soundMuted){
            Mix_PlayChannel(-1, game->jump, 0);
          }
          }
          game->man.isOnPlatform = 0;
        }
        break;
      }
      break;
      case SDL_QUIT:
      game->done = 1;
      break;
    }
  }
  //Gets some of that sweet mouse input and calcultes if it's inside the button
  // and if it is and it has been clicked IT GOES MENU CLOSE OH YEAH BABY FUCK ME IN THE ASS
  SDL_GetMouseState(&mousex, &mousey);
  if(game->statusState == STATUS_STATE_MENU){
    if(collide2d(game->menu.StartGame.x, game->menu.StartGame.y, mousex, mousey, game->menu.StartGame.w, game->menu.StartGame.h, 0, 0)){
      game->menu.StartGame.mouseOver = 1;
      SDL_PumpEvents();
      if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        game->menu.menuClose = 1;
      }
    }else{
      game->menu.StartGame.mouseOver = 0;
    }
  }

  //Gets some of that sweet mouse input and calcultes if it's inside the button
  // and if it is and it has been clicked IT GOES MENU CLOSE OH YEAH BABY FUCK ME IN THE ASS
  SDL_GetMouseState(&mousex, &mousey);
  if(game->statusState == STATUS_STATE_MENU){
    if(collide2d(game->menu.Music.x,game->menu.Music.y, mousex, mousey, game->menu.Music.w, game->menu.Music.h, 0, 0)){
      SDL_PumpEvents();
      if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if(game->musicMuted){
          game->musicMuted = 0;
          SDL_Delay(100);
        }else if(!game->musicMuted){
          game->musicMuted = 1;
          SDL_Delay(100);
        }
      }
    }
  }

  //Gets some of that sweet mouse input and calcultes if it's inside the button
  // and if it is and it has been clicked IT GOES MENU CLOSE OH YEAH BABY FUCK ME IN THE ASS
  SDL_GetMouseState(&mousex, &mousey);
  if(game->statusState == STATUS_STATE_MENU){
    if(collide2d(game->menu.Sound.x,game->menu.Sound.y, mousex, mousey, game->menu.Sound.w, game->menu.Sound.h, 0, 0)){
      SDL_PumpEvents();
      if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if(game->soundMuted){
          game->soundMuted = 0;
          SDL_Delay(100);
        }else if(!game->soundMuted){
          game->soundMuted = 1;
          SDL_Delay(100);
        }
      }
    }
  }


  //Get SMOOOOOOTHHHH keyboard input
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_UP])
  {
    game->man.dy -= 0.2f;

  }
  if(state[SDL_SCANCODE_LEFT]){
    game->man.dx -= 5;
    if(game->man.dx < -6){ //limits Player speed to fabs 6
      game->man.dx = -6;
    }
  }else if(state[SDL_SCANCODE_RIGHT]){
    game->man.dx  += 5;
    if(game->man.dx > 6){  //limits Player speed to 6
      game->man.dx = 6;
    }
  }else{
    game->man.dx *= 0.8;  //slows down player
    if(fabs(game->man.dx) < 0.05){ //sets player speed to 0 if close to it
      game->man.dx = 0;

    }
  }
}



void process(GameState *game)
{
  //Play Background Music
  if(!game->musicMuted){
    Mix_ResumeMusic();
  if( Mix_PlayingMusic() == 0 ){
    Mix_PlayMusic(game->bgMusic, -1);
  }
}else {
  Mix_PauseMusic();
}

  game->time++;  //time variable add per frame

  //Changes Status state to Game mode after 250 frames
  if(game->time > 300 && game->statusState != STATUS_STATE_GAMEOVER && game->statusState != STATUS_STATE_MENU){
    shutdown_status_lives(game);
    game->statusState = STATUS_STATE_GAME;
  }

  //Shutdowns the games
  if(game->time > 250 && game->statusState == STATUS_STATE_GAMEOVER){  //Closes game after 300 frames
    shutdown_status_gameover(game);
  }

  //Closes the menu and opens the state lives
  if(game->menu.menuClose){
    shutdown_status_menu(game);
    init_status_lives(game);
    game->statusState = STATUS_STATE_LIVES;
    game->menu.menuClose = 0;
  }

  //only does game processing if ingame
  if(game->statusState == STATUS_STATE_GAME ){

    if(game->man.alive){

      game->man.x += game->man.dx;   // Change position based on
      game->man.y += game->man.dy;   // current velocity components.
      game->man.dy += GRAVITY;

      //Updates Scrollx variable for updating objects based on player position
      game->Scrollx = -game->man.x + 450;
      if(game->Scrollx > 0)
      game->Scrollx = 0;

      //changes animation of player based on current velocity
      if(game->man.dx != 0 && game->man.isOnPlatform){
        if(game->time %23 == 0){
          if(game->man.aniFrame == 0){
            game->man.aniFrame = 1;
          }
          else{
            game->man.aniFrame = 0;
          }
        }
      }else{
        game->man.aniFrame = 0;
      }

      //changes animation of player if he is airborne
      if(game->man.isOnPlatform != 1){
        game->man.aniFrame = 1;
      }

    }

  }

  //Checks if the player has died and if so starts *deathCountdown* uhhhh and also plays the annoying
  //fucking death sound
  if(!game->man.alive && game->deathCountdown <= 0 && game->statusState != STATUS_STATE_GAMEOVER){

    game->deathCountdown = 120;
    if(!game->soundMuted)
    Mix_PlayChannel(-1, game->die, 0);

  }

  //Does the whole countdown process and removes a life from ze man and resets to the STATUS STATE LIVES
  //Also checks if the man has no more lives and if so *GAMEOVER*
  if(game->deathCountdown > 0 && game->statusState != STATUS_STATE_GAMEOVER){
    game->deathCountdown--;
    if(game->deathCountdown <= 0){
      game->man.lives--;
      if(game->man.lives >= 1){

        //goes back to the lives screen
        init_status_lives(game);
        game->statusState = STATUS_STATE_LIVES;
        game->time = 0;

        //reset
        game->man.alive = 1;
        game->man.x = 300;
        game->man.y = 200;
        game->man.dx = 0;
        game->man.dy = 0;
        game->man.isOnPlatform = 0;

      }else{

        init_status_gameover(game);
        Mix_PauseMusic();
        if(!game->soundMuted)
        Mix_PlayChannel(-1, game->gameover, 0);
        game->statusState = STATUS_STATE_GAMEOVER;
        game->time = 0;

      }
    }
  }



}
