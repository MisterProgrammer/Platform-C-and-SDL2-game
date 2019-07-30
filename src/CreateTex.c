#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "Game.h"

//Function to create a Texture without having the surface cum all over you
SDL_Texture *createTex(SDL_Renderer *renderer,char *file){
  SDL_Surface *image;
  SDL_Texture *tex;
  image = IMG_Load(file);
  if(image == NULL){
    printf("This file ain't it chief");
    SDL_Quit();
    exit(1);
  }

  tex = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  return tex;
}
