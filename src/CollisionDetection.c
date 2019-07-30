#include <stdio.h>
#include <math.h>
#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
void collisionDetect(GameState *game){
  //Checks if the player has collided with an enemy eye
  for(int i = 0; i < NUM_STARS;i++){
    if(collide2d(game->man.x,game->man.y,game->eye[i].x,game->eye[i].y,game->man.w,game->man.h,game->eye[i].w,game->eye[i].h))
    {

      game->man.alive = 0;

    }
  }

  // kills ze man if he goes off bounds
  if(game->man.y + game->man.h > 540){
    game->man.alive = 0;
  }

  //Check Player Collision with platform
  for (int i = 0; i < NUM_PLATFORMS; i++) {

    float mw = game->man.w,mh = game->man.h -13;
    float mx= game->man.x,my = game->man.y;
    float bx= game->platform[i].x,by = game->platform[i].y;
    float bw= game->platform[i].w,bh = game->platform[i].h;

    if(mx+mw/2 > bx && mx+mw/2<bx+bw)
    {
      //are we bumping our head?
      if(my < by+bh && my > by && game->man.dy < 0)
      {
        //correct y
        game->man.y = by+bh;
        my = by+bh;

        //bumped our head, stop any jump velocity
        game->man.dy = 0;
      }
    }
    if(mx+mw > bx && mx<bx+bw)
    {
      //are we landing on the ledge
      if(my+mh > by && my < by && game->man.dy > 0)
      {
        //correct y
        game->man.y = by-mh;
        my = by-mh;

        //landed on this ledge, stop any jump velocity
        if(game->man.isOnPlatform == 0)
        if(!game->soundMuted)
        Mix_PlayChannel(-1, game->land, 0);
        game->man.dy = 0;
        game->man.isOnPlatform = 1;
      }
    }

    if(my+mh > by && my<by+bh)
    {
      //rubbing against right edge
      if(mx < bx+bw && mx+mw > bx+bw && game->man.dx < 0)
      {
        //correct x
        game->man.x = bx+bw;
        mx = bx+bw;

        game->man.dx = 0;
      }
      //rubbing against left edge
      else if(mx+mw > bx && mx < bx && game->man.dx > 0)
      {
        //correct x
        game->man.x = bx-mw;
        mx = bx-mw;

        game->man.dx = 0;
      }
    }
  }

}

//useful utility function to see if two rectangles are colliding at all
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
  return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}
