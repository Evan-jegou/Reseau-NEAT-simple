#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#include "Constantes.h"

    int parent_egg = 0;

    int ini_gen = 0;

    double Percep_x  = 0;
    double Percep_y  = 0;

    int Facteur_mutation_gen [MAX_OBJECT + 1] = {0};
    int Cellule_type [MAX_OBJECT + 1] = {0};






Expression_gen (int *type, int *num_obj)
{
                                                            initialisation_gen ();





}




initialisation_gen ()
{
    if (ini_gen == 0)
    {
        int num_cell = 0;

        while (num_cell != MAX_OBJECT)
        {
            num_cell = num_cell + 1;

            Cellule_type [num_cell] = CELL_TYPE_BASE;
            Facteur_mutation_gen [num_cell] = FACTEUR_MUTATION_MAX;
        }

        Cellule_type [1] = CELL_TYPE_PREDATRICE;

        ini_gen = 1;
    }
}

reinitialisation_gen ()
{
    ini_gen = 0;
}




verif_type_cell (int *type_cell, int *num_obj)
{
    *type_cell = Cellule_type [*num_obj];
}






vie_cellulaire (int *type, int *num_obj, double *E, double *vx, double *vy)
{
        *E = *E - (PERTE_E_BY_BOUCLE + (PERTE_E_BY_BOUCLE * (FACTEUR_PERTE_E_VITESSE *(fabs(*vx) + fabs(*vy)))));

        if (*E <= LIMITE_INF_E_CELL)
        {
            Erase_object (type, num_obj);
        }
}












Action (int *num_obj, int *type, double *E, double *pos_x, double *pos_y, double *vx, double *vy)
{
    int dir_x = 0;
    int dir_y = 0;
    int lay = 0;

                                                                            Network (num_obj, &dir_x, &dir_y, &lay);

    if (dir_x == 1)
    {
        *vx = *vx + APPORT_VITESSE;
    }
    else if (dir_x == -1)
    {
        *vx = *vx - APPORT_VITESSE;
    }
    else if (dir_x == 0)
    {
        *vx = *vx;
    }

    if (dir_y == 1)
    {
        *vy = *vy + APPORT_VITESSE;
    }
    else if (dir_y == -1)
    {
        *vy = *vy - APPORT_VITESSE;
    }
    else if (dir_y == 0)
    {
        *vy = *vy;
    }

    if (*type == TYPE_CELL && lay == 1 && (*E > ENERGIE_NECESSAIR_PONTE))
    {
        int type_oeuf = TYPE_OEUF;
        *E = *E - PERTE_E_PONTE;
                                                                            Send_parent_gen (num_obj);
                                                                            Send_parent_network (num_obj);
                                                                            Add_Object (&type_oeuf, pos_x, pos_y);
    }

    if (*type == TYPE_CELL_SOUCHE)
    {
        int type_oeuf = TYPE_OEUF;
        *E = *E - PERTE_E_PONTE;
                                                                            Send_parent_gen (num_obj);
                                                                            Send_parent_network (num_obj);
                                                                            Add_Object (&type_oeuf, pos_x, pos_y);
    }
}





recup_gen_parent (int *parent, int *Fac_mut, int *Cell_type)
{
    *Fac_mut = Facteur_mutation_gen [*parent];
    *Cell_type = Cellule_type [*parent];
}


Send_parent_gen_egg (int *num_obj)
{
    parent_egg = *num_obj;
}


Add_gen_cell (int *type, int *num_obj)
{
    int Fac_mut = 0;
    int Cell_type = 0;
                                                                            recup_gen_parent_egg (&parent_egg, &Fac_mut, &Cell_type);
    Facteur_mutation_gen [*num_obj] = Fac_mut;
    Cellule_type [*num_obj] = Cell_type;
}







Sortie_reseaux_alea (int *dir_x, int *dir_y, int *lay)
{
    int output1 = rand()%10;
    int output2 = rand()%10;
    double output3 = rand()%10;


    if (output1 >= 5)
    {
        *dir_x = 1;
    }
    else if (output1 < 5)
    {
        *dir_x = -1;
    }


    if (output2 >= 5)
    {
        *dir_y = 1;
    }
    else if (output2 < 5)
    {
        *dir_y = -1;
    }



    if (output3 >= 9)
    {
        int a = rand()%10;

        if (a >= 9)
        {
            int b = rand()%10;

            if (b >= 9)
            {
                int c = rand()%10;

                if (c >= 2)
                {
                    int d = rand()%10;

                        *lay = 1;
                }
            }
        }
    }


}






absorption_food (double *taille_obj, double *E, double *pos_x, double *pos_y, double *food_x, double *food_y, int *abs_food)
{

    double rayon_cell = *taille_obj/2;

    double dx = *pos_x - *food_x;
    double dy = *pos_y - *food_y;

    double dd = (dx*dx)+(dy*dy);

    if (sqrt(dd) <= (rayon_cell))
        {
            *E = *E + ENERGIE_FOOD;
            *abs_food = 1;
        }
}









perception (SDL_Surface *ecran, SDL_Surface *Obj, int *mouse_on_obj, int *type_percu, double *percep_x, double *percep_y, double *pos_x, double *pos_y)
{
    double dist_x = *percep_x - *pos_x;
    double dist_y = *percep_y - *pos_y;

    double dist_percep = fabs(sqrt((dist_x * dist_x) + (dist_y * dist_y)));

    if (dist_percep <= DISTANCE_PERCEPTION)
    {
        int ini_input = 1;

        Percep_x  = *percep_x - *pos_x;
        Percep_y  = *percep_y - *pos_y;
        double Type_percep = *type_percu;
                                                                percep_other_cell (type_percu, &Type_percep);

                                                                Add_Input (&ini_input, &Percep_x);
                                                                Add_Input (&ini_input, &Percep_y);
                                                                Add_Input (&ini_input, &Type_percep);


        if (*mouse_on_obj == 1 && *type_percu == TYPE_FOOD)
        {
                                                                Show_percep (ecran, Obj, percep_x, percep_y);
        }
    }
}





percep_other_cell (int *type_percu, double *Type_percep)
{
    if (*type_percu == TYPE_CELL)
    {
        if (Cellule_type == CELL_TYPE_PREDATRICE)
        {
            *Type_percep = *Type_percep + 0.1;
        }
    }
}











Show_percep (SDL_Surface *ecran, SDL_Surface *Obj, double *percep_x, double *percep_y)
{
    int rouge = 0;
    int bleu = 255;
    int vert = 255;
    double taille = 5;


                                                        show_object_spe(ecran, Obj, &rouge, &bleu, &vert, &taille, percep_x, percep_y);
}









Send_Input_state (int *ini_input,double *pos_x, double *pos_y, double *E, double *vx, double *vy)
{
                                                        Add_Input (ini_input, pos_x);
                                                        Add_Input (ini_input, pos_y);
                                                        Add_Input (ini_input, E);
                                                        Add_Input (ini_input, vx);
                                                        Add_Input (ini_input, vy);
}



