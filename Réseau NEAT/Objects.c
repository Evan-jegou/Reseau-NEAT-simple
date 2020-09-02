#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#include "Constantes.h"

    int Ini_obj = 0;

    int nb_life = 0;
    int Nb_reini_cell = 0;

    int Object [NB_TYPE_OBJECT + 1][MAX_OBJECT + 1] = {0};

    double Object_x [NB_TYPE_OBJECT + 1][MAX_OBJECT + 1] = {0};
    double Object_y [NB_TYPE_OBJECT + 1][MAX_OBJECT + 1] = {0};
    double Object_vx [NB_TYPE_OBJECT + 1][MAX_OBJECT + 1] = {0};
    double Object_vy [NB_TYPE_OBJECT + 1][MAX_OBJECT + 1] = {0};

    double Energie_Obj [NB_TYPE_OBJECT + 1][MAX_OBJECT + 1] = {0};
    double Taille_Obj [NB_TYPE_OBJECT + 1][MAX_OBJECT + 1] = {0};



int Game_object (SDL_Surface *ecran, SDL_Surface *cellule, SDL_Surface *cellule_pred, SDL_Surface *Obj, int *position_souris_x, int *position_souris_y)
{
    nb_life = 0;
                                                            initialisation_objects ();
                                                            show_object (ecran, cellule, cellule_pred, Obj);

    if (Ini_obj == 1)
    {
        int type = 0;

        while (type != NB_TYPE_OBJECT)
        {
            type = type + 1;
            int num_obj = 0;

            while (num_obj != MAX_OBJECT)
            {
                num_obj = num_obj + 1;
                int mouse_on_obj = 0;

                if (Object [type][num_obj] == 1)
                {

                Object_x [type][num_obj] = Object_x [type][num_obj] + Object_vx [type][num_obj];
                Object_y [type][num_obj] = Object_y [type][num_obj] + Object_vy [type][num_obj];

                Object_vx [type][num_obj] = Object_vx [type][num_obj] - Object_vx [type][num_obj] * FACTEUR_INERTIE;
                Object_vy [type][num_obj] = Object_vy [type][num_obj] - Object_vy [type][num_obj] * FACTEUR_INERTIE;


                if ((*position_souris_x >= (Object_x [type][num_obj] - (Taille_Obj [type][num_obj] / 2))) && (*position_souris_x <= (Object_x [type][num_obj] + (Taille_Obj [type][num_obj] / 2)))   &&   (*position_souris_y >= (Object_y [type][num_obj] - (Taille_Obj [type][num_obj] / 2))) && (*position_souris_y <= (Object_y [type][num_obj] + (Taille_Obj [type][num_obj] / 2))))
                {
                    mouse_on_obj = 1;
                }

                                                            Prison (&type, &num_obj);
                                                            Cellules (ecran, Obj, &type, &num_obj, &mouse_on_obj);
                                                            Oeuf (&type, &num_obj);
                }
            }
        }
    }

        if (nb_life == 0)
        {
                                                            Reinitialisation_cellule ();
                                                            reinitialisation_gen ();
                                                            reinitialisation_network ();
        }
}


recup_variable (int *type, int *num_obj, int *actif)
{
    *actif = Object [*type][*num_obj];
}

recup_variable_pos (double *x, double *y, int *type, int *num_obj)
{
    *x = Object_x [*type][*num_obj];
    *y = Object_y [*type][*num_obj];
}

recup_variable_V (double *Vx, double *Vy, int *type, int *num_obj)
{
    *Vx = Object_vx [*type][*num_obj];
    *Vy = Object_vy [*type][*num_obj];
}

recup_taille (double *taille, int *type, int *num_obj)
{
    *taille = Taille_Obj [*type][*num_obj];
}

modif_variable_V (double *vx, double *vy, int *type, int *num_obj)
{
    Object_vx [*type][*num_obj] = *vx;
    Object_vy [*type][*num_obj] = *vy;
}




int initialisation_objects ()
{
    if (Ini_obj == 0)
    {
        int type = 0;

        while (type != NB_TYPE_OBJECT)
        {
            type = type + 1;
            int num_obj = 0;

            if (type == TYPE_CELL_SOUCHE)
            {
                while (num_obj != 10)
                {
                    num_obj = num_obj + 1;
                    double pos_x = rand()%LARGEUR_FENETRE;
                    double pos_y = rand()%HAUTEUR_FENETRE;
                                                                    Add_Object (&type, &pos_x, &pos_y);
                }
            }

            if (type == TYPE_FOOD)
            {
                while (num_obj != 50)
                {
                    num_obj = num_obj + 1;

                    double pos_x = rand()%LARGEUR_FENETRE;
                    double pos_y = rand()%HAUTEUR_FENETRE;
                                                                    Add_Object (&type, &pos_x, &pos_y);
                }
            }
        }

        Ini_obj = 1;
    }
}




initialisation_specifique (int *type, int *num_obj)
{

    if (*type == TYPE_CELL || *type == TYPE_CELL_SOUCHE)
    {
        Energie_Obj [*type][*num_obj] = ENERGIE_NAISSANCE_CELL;
        Taille_Obj [*type][*num_obj] = 12;
                                                                    Add_network_obj (type, num_obj);
                                                                    Add_gen_cell (type, num_obj);
    }

    else if (*type == TYPE_OEUF)
    {
        Energie_Obj [*type][*num_obj] = 0;
        Taille_Obj [*type][*num_obj] = 4;
                                                                    Add_network_obj (type, num_obj);
                                                                    Add_gen_egg (type, num_obj);
    }

    else if (*type == TYPE_FOOD)
    {
        Energie_Obj [*type][*num_obj] = ENERGIE_FOOD;
        Taille_Obj [*type][*num_obj] = 4;
    }
}




Erase_object (int *type, int *num_obj)
{
    Object [*type][*num_obj] = 0;
}






Add_Object (int *type, double *pos_x, double *pos_y)
{
    int num_obj = 1;

    while (num_obj != MAX_OBJECT && Object [*type][num_obj] == 1)
    {
        num_obj = num_obj + 1;
    }

    if (Object [*type][num_obj] == 0)
    {
        Object [*type][num_obj] = 1;
                                                                        initialisation_specifique (type, &num_obj);
        Object_x [*type][num_obj] = *pos_x;
        Object_y [*type][num_obj] = *pos_y;
        Object_vx [*type][num_obj] = 0;
        Object_vy [*type][num_obj] = 0;
    }
}

















Prison (int *type, int *num_obj)
{
        if (Object_x [*type][*num_obj] > LARGEUR_FENETRE)
        {
            Object_vx [*type][*num_obj] = -(Object_vx [*type][*num_obj])/2;
        }
        else if (Object_x [*type][*num_obj] < 0)
        {
            Object_vx [*type][*num_obj] = -(Object_vx [*type][*num_obj])/2;
        }

        if (Object_y [*type][*num_obj] > HAUTEUR_FENETRE)
        {
            Object_vy [*type][*num_obj] = -(Object_vy [*type][*num_obj])/2;
        }
        else if (Object_y [*type][*num_obj] < 0)
        {
            Object_vy [*type][*num_obj] = -(Object_vy [*type][*num_obj])/2;
    }
}



int show_object (SDL_Surface *ecran, SDL_Surface *cellule, SDL_Surface *cellule_pred, SDL_Surface *Obj, int *position_souris_x, int *position_souris_y)
{
    if (AFFICHAGE_ENVI == 1)
    {
        SDL_Rect position_Obj;
        SDL_Rect position_cellule;

        Obj = SDL_CreateRGBSurface (SDL_HWSURFACE, 4, 4, 32, 0,0,0,0);

        int type = 0;

        while (type != NB_TYPE_OBJECT)
        {
            type = type + 1;
            int num_obj = 0;

            while (num_obj != MAX_OBJECT)
            {
                num_obj = num_obj + 1;

                if (Object [type][num_obj] == 1)
                {

                    position_Obj.x = Object_x [type][num_obj] - (Taille_Obj [type][num_obj]/2);
                    position_Obj.y = Object_y [type][num_obj] - (Taille_Obj [type][num_obj]/2);

                    if (type == TYPE_FOOD)
                    {
                            SDL_FillRect (Obj, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                    }



                    if (type == TYPE_OEUF)
                    {
                            SDL_FillRect (Obj, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                    }




                    if (type == TYPE_CELL || type == TYPE_CELL_SOUCHE)
                    {
                            int bleu = 0;
                            int rouge = 0;
                            int vert = 255;

                            int delta_E = LIMITE_SUP_E_CELL - LIMITE_INF_E_CELL;


                            if (Energie_Obj [type][num_obj] > LIMITE_INF_E_CELL && Energie_Obj [type][num_obj] < ((delta_E/7)+LIMITE_INF_E_CELL))
                            {
                                rouge = ((Energie_Obj [type][num_obj] - LIMITE_INF_E_CELL)/(delta_E/7))*255;

                                vert = 0;
                                bleu = 0;
                            }
                            else if (Energie_Obj [type][num_obj] > ((delta_E/7)+LIMITE_INF_E_CELL) && Energie_Obj [type][num_obj] < (((delta_E/7)*2)+LIMITE_INF_E_CELL))
                            {
                                vert = (((Energie_Obj [type][num_obj] - LIMITE_INF_E_CELL)-(delta_E/7))/(delta_E/7))*255;

                                rouge = 255;
                                bleu = 0;
                            }
                            else if (Energie_Obj [type][num_obj] > (((delta_E/7)*2)+LIMITE_INF_E_CELL) && Energie_Obj [type][num_obj] < (((delta_E/7)*3)+LIMITE_INF_E_CELL))
                            {
                                rouge = 255 - (((Energie_Obj [type][num_obj] - LIMITE_INF_E_CELL)-(delta_E/7)*2)/(delta_E/7))*255;

                                vert = 255;
                                bleu = 0;
                            }

                            else if (Energie_Obj [type][num_obj] > (((delta_E/7)*3)+LIMITE_INF_E_CELL) && Energie_Obj [type][num_obj] < (((delta_E/7)*4)+LIMITE_INF_E_CELL))
                            {
                                bleu = (((Energie_Obj [type][num_obj] - LIMITE_INF_E_CELL)-(delta_E/7)*3)/(delta_E/7))*255;

                                rouge = 0;
                                vert = 255;
                            }

                            else if (Energie_Obj [type][num_obj] > (((delta_E/7)*4)+LIMITE_INF_E_CELL))
                            {
                                vert = 255;
                                rouge = 255;
                                bleu = 255;
                            }

                            position_Obj.x = Object_x [type][num_obj] - 2;
                            position_Obj.y = Object_y [type][num_obj] - 2;

                            SDL_FillRect (Obj, NULL, SDL_MapRGB(ecran->format, rouge, vert, bleu));

                            position_cellule.x = Object_x [type][num_obj] - (Taille_Obj [type][num_obj]/2);
                            position_cellule.y = Object_y [type][num_obj] - (Taille_Obj [type][num_obj]/2);

                            int type_cell = 0;

                                                                            verif_type_cell (&type_cell, &num_obj);

                            if (type_cell == CELL_TYPE_BASE)
                            {
                                SDL_BlitSurface(cellule,NULL,ecran,&position_cellule);
                            }
                            else if (type_cell == CELL_TYPE_PREDATRICE)
                            {
                                SDL_BlitSurface(cellule_pred,NULL,ecran,&position_cellule);
                            }

                    }


                    SDL_BlitSurface (Obj, NULL, ecran, &position_Obj);

                }
            }
        }
    }
}


show_object_spe(SDL_Surface *ecran, SDL_Surface *Obj, int *rouge, int *bleu, int *vert, double *taille, double *pos_x, double *pos_y)
{
    Obj = SDL_CreateRGBSurface (SDL_HWSURFACE, *taille, *taille, 32, 0,0,0,0);

    SDL_Rect position_Obj;

    position_Obj.x = *pos_x - (*taille/2);
    position_Obj.y = *pos_y - (*taille/2);

    SDL_FillRect (Obj, NULL, SDL_MapRGB(ecran->format, *rouge, *bleu, *vert));
    SDL_BlitSurface (Obj, NULL, ecran, &position_Obj);
}
















Cellules (SDL_Surface *ecran, SDL_Surface *Obj, int *type, int *num_obj, int *mouse_on_obj)
{
    if (*type == TYPE_CELL || *type == TYPE_CELL_SOUCHE)
    {
        nb_life = nb_life + 1;
        int ini_input = 0;

        double taille_obj = Taille_Obj [*type][*num_obj];
        double pos_x = Object_x [*type][*num_obj];
        double pos_y = Object_y [*type][*num_obj];
        double vx = Object_vx [*type][*num_obj];
        double vy = Object_vy [*type][*num_obj];

        double E = Energie_Obj [*type][*num_obj];

        int type_cell_percevant = 0;
                                                                                            Send_Input_state (&ini_input, &pos_x, &pos_y, &E, &vx, &vy);
                                                                                            Expression_gen (type, num_obj);
                                                                                            verif_type_cell (&type_cell_percevant, num_obj);
        int type_percu = 0;

        while (type_percu != NB_TYPE_OBJECT)
        {
            type_percu = type_percu + 1;
            int num_percep = 0;

            while (num_percep != MAX_OBJECT)
            {
                int abs_food = 0;
                num_percep = num_percep + 1;

                if (Object [type_percu][num_percep] == 1)
                {
                    double percep_x = Object_x [type_percu][num_percep];
                    double percep_y = Object_y [type_percu][num_percep];
                                                                                            perception (ecran, Obj, mouse_on_obj, &type_percu, &percep_x, &percep_y, &pos_x, &pos_y);

                    if (type_cell_percevant == CELL_TYPE_BASE && type_percu == TYPE_FOOD)
                    {
                                                                                            absorption_food (&taille_obj, &E, &pos_x, &pos_y, &percep_x, &percep_y, &abs_food);
                        if (abs_food == 1)
                        {
                            Object [type_percu][num_percep] = 0;
                            int type_food = type_percu;
                            double new_food_x = (rand()%LARGEUR_FENETRE/4) + LARGEUR_FENETRE/3;
                            double new_food_y = (rand()%HAUTEUR_FENETRE/4) + HAUTEUR_FENETRE/3;
                                                                                            Add_Object (&type_food, &new_food_x, &new_food_y);
                        }
                    }

                    else if (type_cell_percevant == CELL_TYPE_PREDATRICE && type_percu == TYPE_CELL && num_percep != *num_obj)
                    {
                        int type_cell_percu = 0;
                                                                            verif_type_cell (&type_cell_percu, &num_percep);

                        if (type_cell_percu == CELL_TYPE_PREDATRICE)
                        {
                            Energie_Obj [*type][*num_obj] = Energie_Obj [*type][*num_obj] - PERTE_E_AGRESSION;
                        }
                                                                            absorption_food (&taille_obj, &E, &pos_x, &pos_y, &percep_x, &percep_y, &abs_food);
                        if (abs_food == 1)
                        {
                            Object [type_percu][num_percep] = 0;
                        }
                    }
                }
            }
        }




                                                                            vie_cellulaire (type, num_obj, &E, &vx, &vy);
                                                                            Action (num_obj, type, &E, &pos_x, &pos_y, &vx, &vy);



        Object_vx [*type][*num_obj] = vx;
        Object_vy [*type][*num_obj] = vy;
        Object_x [*type][*num_obj] = pos_x;
        Object_y [*type][*num_obj] = pos_y;

        Energie_Obj [*type][*num_obj] = E;
    }
}







Reinitialisation_cellule ()
{
    Nb_reini_cell = Nb_reini_cell + 1;
    int num_cell = 0;

    while (num_cell != 10)
    {
        num_cell = num_cell  + 1;
        int type = TYPE_CELL_SOUCHE;
        double pos_x = rand()% LARGEUR_FENETRE;
        double pos_y = rand()%HAUTEUR_FENETRE;
                                                                                        Add_Object (&type, &pos_x, &pos_y);
    }
                        FILE *File = NULL;

                        File = fopen ("Nb_réini_cell.txt", "w+");
                        fprintf (File, "Nombre de réinitialisation cellule = %d", Nb_reini_cell);
                        fclose(File);
}






Oeuf (int *type, int *num_obj)
{
    if (*type == TYPE_OEUF)
    {
        nb_life = nb_life + 1;
        double pos_x = Object_x [*type][*num_obj];
        double pos_y = Object_y [*type][*num_obj];

        double E = Energie_Obj [*type][*num_obj];

                                                                            vie_oeuf (type, num_obj, &E, &pos_x, &pos_y);

        Energie_Obj [*type][*num_obj] = E;
    }
}





