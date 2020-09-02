#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#include "Constantes.h"

    int parent = 0;

    int Facteur_mutation_gen_wait [MAX_OBJECT + 1] = {0};
    int Cellule_type_wait [MAX_OBJECT + 1] = {0};


vie_oeuf (int *type, int *num_obj, double *E, double *pos_x, double *pos_y)
{
        *E = *E + GAIN_E_OEUF_BY_BOUCLE;

        if (*E >= ENERGIE_NAISSANCE_CELL)
        {
            int type_cell = TYPE_CELL;
                                                                            Send_parent_gen_egg (num_obj);
                                                                            Send_parent_network (num_obj);
                                                                            Erase_object (type, num_obj);
                                                                            Add_Object (&type_cell, pos_x, pos_y);
        }

}



Add_gen_egg (int *type, int *num_obj)
{
    int Fac_mut = 0;
    int Cell_type = 0;
                                                                            recup_gen_parent (&parent, &Fac_mut, &Cell_type);
    Facteur_mutation_gen_wait [*num_obj] = Fac_mut;
    Cellule_type_wait [*num_obj] = Cell_type;
}



Send_parent_gen (int *num_obj)
{
    parent = *num_obj;
}


recup_gen_parent_egg (int *parent_egg, int *Fac_mut, int *Cell_type)
{
    *Fac_mut = Facteur_mutation_gen_wait [*parent_egg];
    *Cell_type = Cellule_type_wait [*parent_egg];
}
