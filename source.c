#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

#define win_w 1920
#define win_h 1080

/*
menu principal 0
menu option    1
menu joueur    2/3
menu quiz      4/5
menu score     6
menu save      7/8
*/



void SDL_Exitwitherror(const char *msg) {
    SDL_Log("erreur : %s > %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}




    	
    
    
void initialisation(app* app) {
    // Basic SDL Init
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Exitwitherror("SDL_Init fail");
    }

    // Mixer Init
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        SDL_Exitwitherror("initialisation son echouee");

    
    if (TTF_Init()==-1)
    	SDL_Exitwitherror("initialisation du text echouee ");

    // Logic control
    app->running = 1;
    

    srand(time(NULL));

    // Window Creation
    app->window = SDL_CreateWindow(
        "Atelier SDL2 - Scenario 1",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        win_w, win_h,
        SDL_WINDOW_FULLSCREEN
    );

    if (!app->window) SDL_Exitwitherror("Erreur SDL_CreateWindow");

    // Renderer Creation - Use app->window, not 'window'
    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED );
    if (!app->renderer) SDL_Exitwitherror("Erreur Renderer");

    // Image Init
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) SDL_Exitwitherror("Erreur image");

    }





void creation(app *app) {
    app->p1.surface = IMG_Load("src/player_d_1.png");
    if (!app->p1.surface) SDL_Exitwitherror("Erreur IMG_Load");

    app->p1.tx.text_d_1 = SDL_CreateTextureFromSurface(app->renderer, app->p1.surface);
    SDL_FreeSurface(app->p1.surface);
    
    app->p1.surface = IMG_Load("src/player_d_2.png");
    if (!app->p1.surface) SDL_Exitwitherror("Erreur IMG_Load");

    app->p1.tx.text_d_2 = SDL_CreateTextureFromSurface(app->renderer, app->p1.surface);
    SDL_FreeSurface(app->p1.surface);
    
    app->p1.surface = IMG_Load("src/player_d_3.png");
    if (!app->p1.surface) SDL_Exitwitherror("Erreur IMG_Load");

    app->p1.tx.text_d_3 = SDL_CreateTextureFromSurface(app->renderer, app->p1.surface);
    SDL_FreeSurface(app->p1.surface);
    
    
    
    
    app->p1.surface = IMG_Load("src/player_g_1.png");
    if (!app->p1.surface) SDL_Exitwitherror("Erreur IMG_Load");

    app->p1.tx.text_g_1 = SDL_CreateTextureFromSurface(app->renderer, app->p1.surface);
    SDL_FreeSurface(app->p1.surface);
    
    app->p1.surface = IMG_Load("src/player_g_2.png");
    if (!app->p1.surface) SDL_Exitwitherror("Erreur IMG_Load");

    app->p1.tx.text_g_2 = SDL_CreateTextureFromSurface(app->renderer, app->p1.surface);
    SDL_FreeSurface(app->p1.surface);
    
    app->p1.surface = IMG_Load("src/player_g_3.png");
    if (!app->p1.surface) SDL_Exitwitherror("Erreur IMG_Load");

    app->p1.tx.text_g_3 = SDL_CreateTextureFromSurface(app->renderer, app->p1.surface);
    SDL_FreeSurface(app->p1.surface);
    
    
    
    // Rect logic - corrected variable names
    SDL_QueryTexture(app->p1.tx.text_d_1, NULL, NULL, &app->p1.srcRect.w, &app->p1.srcRect.h);
    SDL_QueryTexture(app->p1.tx.text_d_2, NULL, NULL, &app->p1.srcRect.w, &app->p1.srcRect.h);
    SDL_QueryTexture(app->p1.tx.text_d_3, NULL, NULL, &app->p1.srcRect.w, &app->p1.srcRect.h);
    
    SDL_QueryTexture(app->p1.tx.text_g_1, NULL, NULL, &app->p1.srcRect.w, &app->p1.srcRect.h);
    SDL_QueryTexture(app->p1.tx.text_g_2, NULL, NULL, &app->p1.srcRect.w, &app->p1.srcRect.h);
    SDL_QueryTexture(app->p1.tx.text_g_3, NULL, NULL, &app->p1.srcRect.w, &app->p1.srcRect.h);
    
    app->p1.srcRect.x = 0;
    app->p1.srcRect.y = 0;

    app->p1.dstRect.w = app->p1.srcRect.w+20;
    app->p1.dstRect.h = app->p1.srcRect.h;
    app->p1.dstRect.x = 480;
    app->p1.dstRect.y = 540;
    
    
    app->p1.state = 0;
    
    
    
    
    app->p1.score.font=TTF_OpenFont("src/ka1.ttf",50);
    if(app->p1.score.font==NULL) SDL_Exitwitherror("erreur chargement police");
    
    app->p1.score.color.r = 0;
    app->p1.score.color.g = 255;
    app->p1.score.color.b = 255;
    app->p1.score.color.a = 255;
    
    app->p1.score.textSurface = TTF_RenderText_Solid(app->p1.score.font,"0001235",app->p1.score.color);
    if(app->p1.score.textSurface==NULL) SDL_Exitwitherror("erreur creation surface de txt");
    
    app->p1.score.textTexture = SDL_CreateTextureFromSurface(app->renderer, app->p1.score.textSurface);
    
    SDL_FreeSurface(app->p1.score.textSurface);
    
    SDL_QueryTexture(app->p1.score.textTexture,
                 NULL,
                 NULL,
                 &app->p1.score.textPosition.w,
                 &app->p1.score.textPosition.h);
    
    app->p1.score.textPosition.x= 1620;
    app->p1.score.textPosition.y= 150;
    
    
    app->p1.health.surface = IMG_Load("src/fheart.png");
    if (!app->p1.health.surface) SDL_Exitwitherror("Erreur IMG_Load");

    app->p1.health.fheart = SDL_CreateTextureFromSurface(app->renderer, app->p1.health.surface);
    SDL_FreeSurface(app->p1.health.surface);
    
    app->p1.health.surface = IMG_Load("src/eheart.png");
    if (!app->p1.health.surface) SDL_Exitwitherror("Erreur IMG_Load");

    app->p1.health.eheart = SDL_CreateTextureFromSurface(app->renderer, app->p1.health.surface);
    SDL_FreeSurface(app->p1.health.surface);
    
    
    
    // Rect logic - corrected variable names
        
    
    app->p1.health.srcRect.x = 0;
    app->p1.health.srcRect.y = 0;
    
    app->p1.health.srcRect.w = 120;
    app->p1.health.srcRect.h = 112;

    app->p1.health.dstRect.w = 120;
    app->p1.health.dstRect.h = 120;
    app->p1.health.dstRect.x = 1470;
    app->p1.health.dstRect.y = 20;

    // Keep srcRect at 64x64 (do NOT query texture dimensions here)

    app->p1.health.amount=2;
}





void gestion_event(app* app, int* x, int* y) {
     while (SDL_PollEvent(&app->event)) {
          if (app->event.type == SDL_QUIT) {app->running = 0;}
          SDL_GetMouseState(x, y);
  
          if (app->event.type == SDL_KEYDOWN) {
              if (app->event.key.keysym.sym == SDLK_ESCAPE) {
              app->running = 0;
              }
              
              if (app->event.key.keysym.sym == SDLK_d) { 
                  app->p1.dstRect.x+=7;
                  app->p1.state++;
                  app->p1.dir=1;
                  if(app->p1.state>12)app->p1.state=(int)app->p1.state/12;
                }
              if (app->event.key.keysym.sym == SDLK_s) { 
                  app->p1.dstRect.y+=7;
                  app->p1.state++;
                  if(app->p1.state>12)app->p1.state=(int)app->p1.state/12;
                }
              if (app->event.key.keysym.sym == SDLK_q) { 
                  app->p1.dstRect.x-=7;
                  app->p1.state++;
                  app->p1.dir=0;
                  if(app->p1.state>12)app->p1.state=(int)app->p1.state/12;
                }
              if (app->event.key.keysym.sym == SDLK_z) { 
                  app->p1.dstRect.y-=7;
                  app->p1.state++;
                  if(app->p1.state>12)app->p1.state=(int)app->p1.state/12;
                }
               
            }
        }
}






void affichage(app* app, int x, int y) {
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
    if(app->p1.dir==1){
    if(app->p1.state<4){
    SDL_RenderCopy(app->renderer, app->p1.tx.text_d_1, &app->p1.srcRect, &app->p1.dstRect);
     }
      
    else if(app->p1.state<8){
    SDL_RenderCopy(app->renderer, app->p1.tx.text_d_2, &app->p1.srcRect, &app->p1.dstRect);
     }
      
    else if(app->p1.state<=12){
    SDL_RenderCopy(app->renderer, app->p1.tx.text_d_3, &app->p1.srcRect, &app->p1.dstRect);
     }
  }else if(app->p1.dir!=1){
  if(app->p1.state<4){
    SDL_RenderCopy(app->renderer, app->p1.tx.text_g_1, &app->p1.srcRect, &app->p1.dstRect);
     }
      
    else if(app->p1.state<8){
    SDL_RenderCopy(app->renderer, app->p1.tx.text_g_2, &app->p1.srcRect, &app->p1.dstRect);
     }
      
    else if(app->p1.state<=12){
    SDL_RenderCopy(app->renderer, app->p1.tx.text_g_3, &app->p1.srcRect, &app->p1.dstRect);
     }
  
  
  
  }
    SDL_RenderCopy(app->renderer,app->p1.score.textTexture,NULL,&app->p1.score.textPosition);
    
    // Render full hearts using temporary rect
    SDL_Rect heartRect = app->p1.health.dstRect;
    for(int i=0; i<app->p1.health.amount; i++){
        SDL_RenderCopy(app->renderer, app->p1.health.fheart, &app->p1.health.srcRect, &heartRect);
        heartRect.x += 150;
    }

    for(int i=0; i<3 - app->p1.health.amount; i++){
        SDL_RenderCopy(app->renderer, app->p1.health.eheart, &app->p1.health.srcRect, &heartRect);
        heartRect.x += 150;
    }
    
    SDL_RenderPresent(app->renderer);
}







void quitter(app* app) {
 
    //app->cm=-1;
    //free_menu(app,app->cm);
    //Mix_CloseAudio();
    /*
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    IMG_Quit();
    SDL_Quit(); */
}




/*
void damage(player* p1, int dmg){
  p1->health-=dmg;
}
*/
