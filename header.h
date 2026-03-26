#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
typedef struct{
  SDL_Texture *text_d_1;
  SDL_Texture *text_d_2;
  SDL_Texture *text_d_3;
  SDL_Texture *text_g_1;
  SDL_Texture *text_g_2;
  SDL_Texture *text_g_3;
}textures;

typedef struct{
  SDL_Surface *surface;
  SDL_Texture *fheart;
  SDL_Texture *eheart;
  SDL_Rect srcRect;
  SDL_Rect dstRect;
  int amount;
}health;

typedef struct{
  TTF_Font *font;
  SDL_Surface *textSurface;
  SDL_Texture *textTexture;
  SDL_Rect textPosition;
  SDL_Color color;
}score;


typedef struct{
  int state; 
  textures tx;
  SDL_Surface *surface;
  SDL_Rect srcRect; 
  SDL_Rect dstRect;
  score score;
  health health;
  int dir;
}player;



typedef struct{
  SDL_Window *window ;
  SDL_Renderer *renderer ;
  SDL_Event event;
  player p1;
  int running;
}app;






void SDL_Exitwitherror(const char *msg);
void quitter(app* app);
void affichage(app* app, int x, int y);
void gestion_event(app* app,int* x, int* y);
void creation(app *app);
void initialisation(app* app);
void quitter_score(app *app);
//void damage(player* p1, int dmg);

#endif // HEADER_H_INCLUDED
