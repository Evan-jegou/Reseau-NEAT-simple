#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#include "Constantes.h"




Sigmoid (double *valeur)
{
    double valeur_prim = 1 / (1 + exp(-*valeur));
    *valeur = valeur_prim;
}



Linear (double *valeur)
{
    double valeur_prim = *valeur;
    *valeur = valeur_prim;
}



Square (double *valeur)
{
    double valeur_prim = (*valeur * *valeur);
    *valeur = valeur_prim;
}



Sinus (double *valeur)
{
    double valeur_prim = sin(*valeur);
    *valeur = valeur_prim;
}


Absolute (double *valeur)
{
    double valeur_prim = fabs(*valeur);
    *valeur = valeur_prim;
}


Reluctant (double *valeur)
{
    double valeur_prim = 0;

    if (*valeur > 0)
    {
        valeur_prim = *valeur;
    }
    else
    {
        valeur_prim = 0;
    }

    *valeur = valeur_prim;
}


Gaussian (double *valeur)
{
    double valeur_prim = exp(-(*valeur * *valeur));
    *valeur = valeur_prim;
}

