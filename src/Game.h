#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
//sets global variables
#define GRAVITY 0.35f
#define NUM_STARS 200
#define NUM_PLATFORMS 250

//Defines status states
enum  statusState{
  STATUS_STATE_MENU,STATUS_STATE_LIVES,STATUS_STATE_GAME,STATUS_STATE_GAMEOVER
};

typedef struct{
  TTF_Font *font;
  int size;
  SDL_Texture *label;
  int w,h;
}Text;

typedef struct {
  int x,y,w,h;
  int r,g,b;
  int mouseOver;
  Text text;
}Button;


typedef struct {
  Button StartGame;
  Button Music;
  Button Sound;
  //Menu Background,images and variables
  SDL_Texture *menuTex,*soundTex,*musicTex,*nosoundTex,*nomusicTex;
  int menuClose;
}Menu;
typedef struct
{
  float x, y, w,h;
  float dx,dy;
  int isOnPlatform;
  short lives;
  int alive;
  char *name;
  SDL_Texture *man_tex[2],*FIRE;
  int aniFrame;
} Man;

typedef struct{
  int x,y,w,h;
  SDL_Texture *eye_tex;
}Eye;

typedef struct{
  int x,y,w,h;
  SDL_Texture *plat_tex;
}Platform;


typedef struct {
  int done;
  //Players
  Man man;
  //background
  Eye eye[NUM_STARS];
  //Plataformas
  Platform platform[NUM_PLATFORMS];
  //Scroll variable
  float Scrollx;
  Text text;
  SDL_Renderer *renderer;
  SDL_Window *window;
  Menu menu;
  //frame and status
  int time;
  int statusState,deathCountdown;
  //Sounds
  Mix_Music *bgMusic;
  Mix_Chunk *jump,*die,*land,*gameover;
  int soundMuted,musicMuted;
}GameState;

void init_status_menu(GameState *game);
void draw_status_menu(GameState *game);
void shutdown_status_menu(GameState *game);
void init_status_lives(GameState *game);
void draw_status_lives(GameState *game);
void shutdown_status_lives(GameState *game);
void init_status_gameover(GameState *game);
void draw_status_gameover(GameState *game);
void shutdown_status_gameover(GameState *Game);
void loadGame(GameState *game);
SDL_Texture *createTex(SDL_Renderer *renderer,char *file);
void render(GameState *gamestate);
void processEvents(GameState *game);
void collisionDetect(GameState *game);
void process(GameState *game);
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);
