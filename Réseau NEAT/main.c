#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#include "Constantes.h"

int pause(SDL_Surfaceecran);


int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *Fond = NULL;
    SDL_Rect positionFond;

    positionFond.x = 0;
    positionFond.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode (LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Algo", NULL);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface (Fond,NULL, ecran, &positionFond);

    SDL_Flip(ecran);

                                                            pause(ecran);


    SDL_FreeSurface(Fond);
    SDL_FreeSurface(ecran);
    SDL_Quit();

    return EXIT_SUCCESS;
}
