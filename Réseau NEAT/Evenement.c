#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#include "Constantes.h"

    int position_souris_x = 0;
    int position_souris_y = 0;

    int continuer = 1;


int pause(SDL_Surface *ecran)
{
    SDL_EnableKeyRepeat (10,10);
    SDL_Event Touche;

        SDL_Surface *cellule = NULL;
        SDL_Surface *cellule_pred = NULL;
        SDL_Surface *Obj = NULL;

        cellule = IMG_Load("Img/Cellule.png");
        cellule_pred = IMG_Load("Img/Cellule_predatrice.png");


    while (continuer)
    {
        int up = 0;
        int down = 0;
        int left = 0;
        int right = 0;

        SDL_PollEvent (&Touche);

        switch (Touche.type)
        {

                case SDL_KEYDOWN :

        if (Touche.key.keysym.sym == SDLK_ESCAPE)
        {
                SDL_FreeSurface(Obj);
                SDL_FreeSurface(cellule);

                continuer = 0;
        }
        if (Touche.key.keysym.sym == SDLK_UP)
        {
                up = 1;
        }
        if (Touche.key.keysym.sym == SDLK_DOWN)
        {
                down = 1;
        }
        if (Touche.key.keysym.sym == SDLK_LEFT)
        {
                left = 1;
        }
        if (Touche.key.keysym.sym == SDLK_RIGHT)
        {
                right = 1;
        }


                case SDL_MOUSEMOTION :

            position_souris_x =  (Touche.motion.x);
            position_souris_y = (Touche.motion.y);

        }



                                                            raffraichir_black (ecran);
                                                            Game_object (ecran, cellule, cellule_pred, Obj, &position_souris_x, &position_souris_y);






            SDL_Flip (ecran);


    }
}







raffraichir_black (SDL_Surface *ecran)
{
        SDL_Surface *Fond = NULL;
        SDL_Rect positionFond;
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        positionFond.x = 0;
        positionFond.y = 0;
        SDL_BlitSurface (Fond,NULL, ecran, &positionFond);

        SDL_FreeSurface(Fond);

}

