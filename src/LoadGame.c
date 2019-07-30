#include <stdio.h>
#include <SDL2/SDL.h>
#include "Game.h"

void loadGame(GameState *game){

  //Load images and create rendering textures from them
  game->eye->eye_tex = createTex(game->renderer,"files/images/eye.png");
  game->man.man_tex[0] = createTex(game->renderer,"files/images/man1.png");
  game->man.man_tex[1] = createTex(game->renderer,"files/images/man2.png");
  game->platform->plat_tex = createTex(game->renderer,"files/images/platform.png");
  game->man.FIRE = createTex(game->renderer,"files/images/fire.png");
  game->menu.menuTex = createTex(game->renderer, "files/images/menu.png");
  game->menu.musicTex = createTex(game->renderer, "files/images/music.png");
  game->menu.soundTex = createTex(game->renderer, "files/images/sound.png");
  game->menu.nomusicTex = createTex(game->renderer, "files/images/nomusic.png");
  game->menu.nosoundTex = createTex(game->renderer, "files/images/nosound.png");


  //set Eye Values;
  for (int i = 0; i < NUM_STARS; i++) {
    game->eye[i].x = random()%50000+1000;
    game->eye[i].y = random()%300;
    game->eye[i].w= 64;
    game->eye[i].h = 64;
  }
    game->bgMusic = NULL;
    game->bgMusic = Mix_LoadMUS("files/sounds/music.wav");
    game->die = NULL;
    game->die = Mix_LoadWAV("files/sounds/die.wav");
    game->jump = NULL;
    game->jump = Mix_LoadWAV("files/sounds/jump.wav");
    game->land = NULL;
    game->land = Mix_LoadWAV("files/sounds/land.wav");
    game->gameover = NULL;
    game->gameover = Mix_LoadWAV("files/sounds/gameover.wav");


  //Load Fonts
  game->text.size = 48;
  game->text.font = TTF_OpenFont("files/fonts/Crazy-Pixel.ttf", game->text.size);
  if(!game->text.font){
    printf("Cannot find font file!\n\n");
    SDL_Quit();
    exit(1);
  }
  game->menu.StartGame.text.size = 48;
  game->menu.StartGame.text.font = TTF_OpenFont("files/fonts/Crazy-Pixel.ttf", game->menu.StartGame.text.size);
  if(!game->menu.StartGame.text.font){
    printf("Cannot find font file!\n\n");
    SDL_Quit();
    exit(1);
  }



  //set Player values
  game->man.alive = 1;
  game->man.lives = 3;
  game->man.aniFrame = 0;
  game->man.x = 300;
  game->man.y = 200;
  game->man.w = 36;
  game->man.h = 40;
  game->man.dy = 0;
  game->man.dx = 0;
  game->man.isOnPlatform =0;


  //sets platform values
  for (int i = 0; i < NUM_PLATFORMS; i++) {
    game->platform[i].x = random()%30000;
    game->platform[i].y = random()%540;
    game->platform[i].w = 256;
    game->platform[i].h = 64;
  }
  game->platform[0].x = 250;
  game->platform[0].y = 300;
  game->platform[0].w = 256;
  game->platform[0].h = 64;


  //sets game variables
  game->Scrollx = 0;
  game->time = 0;
  game->statusState = STATUS_STATE_MENU;
  game->text.label = NULL;
  game->deathCountdown = 0;

  //sets menu variables
  game->menu.StartGame.x = 960/2-250/2;
  game->menu.StartGame.y = 750/2-50/2;
  game->menu.StartGame.w = 250;
  game->menu.StartGame.h = 50;
  game->menu.menuClose = 0;
  game->menu.StartGame.r = 255;
  game->menu.StartGame.g = 255;
  game->menu.StartGame.b = 255;
  game->menu.StartGame.text.label = NULL;
  game->menu.StartGame.mouseOver = 0;
  game->musicMuted = 1;
  game->soundMuted = 0;
  game->menu.Music.x = 870;
  game->menu.Music.y = 10;
  game->menu.Music.w = 25;
  game->menu.Music.h = 25;
  game->menu.Sound.x = 800;
  game->menu.Sound.y = 10;
  game->menu.Sound.w = 25;
  game->menu.Sound.h = 25;
  init_status_menu(game);
}
