#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#include "Constantes.h"


    double Neurones_wait [MAX_OBJECT + 1][MAX_NEURONE + 1] = {0};

    double Neurones_type_wait [MAX_OBJECT + 1][MAX_NEURONE + 1] = {0};
    double Neurones_val_entree_wait [MAX_OBJECT + 1][MAX_NEURONE + 1] = {0};
    double Neurones_val_sortie_wait [MAX_OBJECT + 1][MAX_NEURONE + 1] = {0};

    double Synapse_wait [MAX_OBJECT + 1][MAX_NEURONE + 1][MAX_SINAPSES_BY_NEURONE + 1] = {0};
    double Val_synapse_wait [MAX_OBJECT + 1][MAX_NEURONE + 1][MAX_SINAPSES_BY_NEURONE + 1] = {0};
    double Neurones_connected_wait [MAX_OBJECT + 1][MAX_NEURONE + 1][MAX_SINAPSES_BY_NEURONE + 1] = {0};



Recup_network_egg (int *num_obj, int *num_neuron, int *num_synapse, int *recup_neuron, double *neuron, double *type, double *val_neuron, double *val_sortie_neuron, double *synapse, double *val_synapse, double *neuron_connecte)
{
    if (*recup_neuron == 0)
    {
        Neurones_wait [*num_obj][*num_neuron] = *neuron;
        Neurones_type_wait [*num_obj][*num_neuron] = *type;
        Neurones_val_entree_wait [*num_obj][*num_neuron] = *val_neuron;
        Neurones_val_sortie_wait [*num_obj][*num_neuron] = *val_sortie_neuron;

        *recup_neuron = 1;

    }
        Synapse_wait [*num_obj][*num_neuron][*num_synapse] = *synapse;
        Val_synapse_wait [*num_obj][*num_neuron][*num_synapse] = *val_synapse;
        Neurones_connected_wait [*num_obj][*num_neuron][*num_synapse] = *neuron_connecte;
}


Send_network_egg (int *num_obj, int *num_neuron, int *num_synapse, int *recup_neuron, double *neuron, double *type, double *val_neuron, double *val_sortie_neuron, double *synapse, double *val_synapse, double *neuron_connecte)
{
    if (*recup_neuron == 0)
    {
        *neuron = Neurones_wait [*num_obj][*num_neuron];
        *type = Neurones_type_wait [*num_obj][*num_neuron];
        *val_neuron = Neurones_val_entree_wait [*num_obj][*num_neuron];
        *val_sortie_neuron = Neurones_val_sortie_wait [*num_obj][*num_neuron];
    }

        *synapse = Synapse_wait [*num_obj][*num_neuron][*num_synapse];
        *val_synapse = Val_synapse_wait [*num_obj][*num_neuron][*num_synapse];
        *neuron_connecte = Neurones_connected_wait [*num_obj][*num_neuron][*num_synapse];
}

















Mutation_network (int *num_obj)
{
    int nb_mutation = rand()% MAX_MUTATION_BY_EGG;
    nb_mutation = nb_mutation + 1;

    while (nb_mutation != 0)
    {
        nb_mutation = nb_mutation - 1;

        int nb_neuron_actif = 0;
        int num_neuron = 0;

        while (num_neuron != MAX_NEURONE)
        {
            num_neuron = num_neuron + 1;

            if (Neurones_wait [*num_obj][num_neuron] == 1)
            {
                nb_neuron_actif = nb_neuron_actif + 1;
            }
        }


        int alea = rand()%NB_TYPE_MUTATIONS;
        alea = alea + 1;

        if (alea == MUTATION_ADD_SYNAPSE)
        {
                                                        Mutate_add_synapse (num_obj, &nb_neuron_actif);
        }

        else if (alea == MUTATION_MODIF_SYNAPSE)
        {
                                                        Mutate_modif_synapse (num_obj, &nb_neuron_actif);
        }

        else if (alea == MUTATION_ADD_NEURON)
        {
                                                        Mutate_add_neuron (num_obj, &nb_neuron_actif);
        }
        else if (alea == MUTATION_MODIF_NEURON)
        {
                                                        Mutate_modif_neuron (num_obj, &nb_neuron_actif);
        }
        else if (alea == MUTATION_SUPP_STRUCTURE)
        {
                                                        Mutate_supp_struct (num_obj, &nb_neuron_actif);
        }
    }

}





Mutate_add_synapse (int *num_obj, int *nb_neuron_actif)
{
        int alea_neuron = 0;
        int alea_neuron2 = NB_INPUT;
        int num_actif = 0;

        num_actif = rand()%(*nb_neuron_actif - NB_OUTPUT);
        num_actif = num_actif + 1;

        while (num_actif != 0)
        {
            alea_neuron = alea_neuron + 1;

            if (Neurones_wait [*num_obj][alea_neuron] == 1)
            {
                num_actif = num_actif - 1;
            }
        }

        num_actif = rand()%(*nb_neuron_actif - NB_INPUT);
        num_actif = num_actif + 1;

        while (num_actif != 0)
        {
            alea_neuron2 = alea_neuron2 + 1;

            if (Neurones_wait [*num_obj][alea_neuron2] == 1)
            {
                num_actif = num_actif - 1;
            }
        }

        int num_synapse = 1;

        while (Synapse_wait [*num_obj][alea_neuron][num_synapse] == 1)
        {
            num_synapse = num_synapse + 1;
        }

        if (num_synapse <= MAX_SINAPSES_BY_NEURONE)
        {
                double a = rand()%100000;
                double b = rand()%100000;
                double c = (a - b)/10000;

            Synapse_wait [*num_obj][alea_neuron][num_synapse] = 1;
            Val_synapse_wait [*num_obj][alea_neuron][num_synapse] = c;
            Neurones_connected_wait [*num_obj][alea_neuron][num_synapse] = alea_neuron2;

            int ecrire = 0;

            if (ecrire == 1)
            {
                            FILE *File = NULL;

                            File = fopen ("Ajout Synapse.txt", "w+");
                            fprintf (File, "num_egg : %d --> num_neuron : %d \n--> synapse : %d --> val_synapse : %f \nnum_neuron2 : %d", *num_obj, alea_neuron, num_synapse, c, alea_neuron2);
                            fclose (File);
            }
        }
}









Mutate_modif_synapse (int *num_obj, int *nb_neuron_actif)
{
        int alea_neuron = 0;
        int num_actif = 0;

        num_actif = rand()%(*nb_neuron_actif - NB_OUTPUT);
        num_actif = num_actif + 1;

        while (num_actif != 0)
        {
            alea_neuron = alea_neuron + 1;

            if (Neurones_wait [*num_obj][alea_neuron] == 1)
            {
                num_actif = num_actif - 1;
            }
        }


        int nb_synapse_actif = 0;
        int num_synapse = 0;

        while (num_synapse != MAX_SINAPSES_BY_NEURONE)
        {
            num_synapse = num_synapse + 1;

            if (Synapse_wait [*num_obj][alea_neuron][num_synapse] == 1)
            {
                nb_synapse_actif = nb_synapse_actif + 1;
            }
        }

        num_synapse = 0;
        double val_origine = 0;

        if (nb_synapse_actif != 0)
        {
            int num_synapse_actif = 0;

            num_synapse_actif = rand()%nb_synapse_actif;
            num_synapse_actif = num_synapse_actif + 1;

            while (num_synapse_actif != 0)
            {
                num_synapse = num_synapse + 1;

                if (Synapse_wait [*num_obj][alea_neuron][num_synapse] == 1)
                {
                    num_synapse_actif = num_synapse_actif - 1;
                }
            }

                val_origine = Val_synapse_wait [*num_obj][alea_neuron][num_synapse];

                double a = rand()%100000;
                double b = rand()%100000;
                double c = (a - b)/10000;

                Val_synapse_wait [*num_obj][alea_neuron][num_synapse] = c;
            }



                int ecrire = 0;

                if (ecrire == 1)
                {
                                FILE *File = NULL;

                                File = fopen ("Mutatation Synapse.txt", "w+");
                                fprintf (File, "Oeuf numero %d", *num_obj);
                                fprintf (File, "\nNeuron %d --> nombre de synapse actif : %d", alea_neuron, nb_synapse_actif);

                        if (nb_synapse_actif != 0)
                        {
                                fprintf (File, "\nValeur original synapse %d : %f", num_synapse, val_origine);
                                fprintf (File, "\nValeur mutée synapse %d : %f", num_synapse, Val_synapse_wait [*num_obj][alea_neuron][num_synapse]);
                        }

                                fclose (File);
                }
}








Mutate_add_neuron (int *num_obj, int *nb_neuron_actif)
{
        int alea_neuron = 0;
        int num_actif = 0;

        num_actif = rand()%(*nb_neuron_actif - NB_OUTPUT);
        num_actif = num_actif + 1;

        while (num_actif != 0)
        {
            alea_neuron = alea_neuron + 1;

            if (Neurones_wait [*num_obj][alea_neuron] == 1)
            {
                num_actif = num_actif - 1;
            }
        }


        int nb_synapse_actif = 0;
        int num_synapse = 0;

        while (num_synapse != MAX_SINAPSES_BY_NEURONE)
        {
            num_synapse = num_synapse + 1;

            if (Synapse_wait [*num_obj][alea_neuron][num_synapse] == 1)
            {
                nb_synapse_actif = nb_synapse_actif + 1;
            }
        }

        num_synapse = 0;
        double neuron_connect_origine = 0;
        int num_new_neuron = 1;
        double val_origine = 0;

        if (nb_synapse_actif != 0)
        {
            int num_synapse_actif = 0;

            num_synapse_actif = rand()%nb_synapse_actif;
            num_synapse_actif = num_synapse_actif + 1;

            while (num_synapse_actif != 0)
            {
                num_synapse = num_synapse + 1;

                if (Synapse_wait [*num_obj][alea_neuron][num_synapse] == 1)
                {
                    num_synapse_actif = num_synapse_actif - 1;
                }
            }

            val_origine = Val_synapse_wait [*num_obj][alea_neuron][num_synapse];


            while (Neurones_wait [*num_obj][num_new_neuron] == 1 && num_new_neuron != MAX_SS_COUCHE)
            {
                num_new_neuron = num_new_neuron + 1;
            }

            neuron_connect_origine = Neurones_connected_wait [*num_obj][alea_neuron][num_synapse];

            if (num_new_neuron < MAX_SS_COUCHE)
            {
                int type = rand()%NB_TYPE_NEURONES;
                type = type + 1;

                Neurones_wait [*num_obj][num_new_neuron] = 1;
                Neurones_type_wait [*num_obj][num_new_neuron] = type;
                Neurones_val_entree_wait [*num_obj][num_new_neuron] = 0;
                Neurones_val_sortie_wait [*num_obj][num_new_neuron] = 0;

                double a = rand()%100000;
                double b = rand()%100000;
                double c = (a - b)/10000;

                Synapse_wait [*num_obj][num_new_neuron][1] = 1;
                Val_synapse_wait [*num_obj][num_new_neuron][1] = c;
                Neurones_connected_wait [*num_obj][num_new_neuron][1] = Neurones_connected_wait [*num_obj][alea_neuron][num_synapse];

                Neurones_connected_wait [*num_obj][alea_neuron][num_synapse] = num_new_neuron;
            }
        }

                int ecrire = 0;

                if (ecrire == 1)
                {
                                FILE *File = NULL;

                                File = fopen ("Ajout Neurone.txt", "w+");
                                fprintf (File, "Oeuf numero %d", *num_obj);
                                fprintf (File, "\n\nNeuron départ : %d --> nombre de synapse actif : %d", alea_neuron, nb_synapse_actif);

                        if (nb_synapse_actif != 0)
                        {
                                fprintf (File, "\nValeur synapse %d : %f", num_synapse, val_origine);
                                fprintf (File, "\nNeurone connecté à l'origine : %f", neuron_connect_origine);
                                fprintf (File, "\nNeurone connecté après mutation : %f", Neurones_connected_wait [*num_obj][alea_neuron][num_synapse]);

                                fprintf (File, "\n\nNouveau neurone : %d", num_new_neuron);
                                fprintf (File, "\nValeur synapse 1 : %f", Val_synapse_wait [*num_obj][num_new_neuron][1]);
                                fprintf (File, "\nNeurone connecté : %f", Neurones_connected_wait [*num_obj][num_new_neuron][1]);
                        }

                                fclose (File);
                }
}










Mutate_modif_neuron (int *num_obj, int *nb_neuron_actif)
{
    *nb_neuron_actif = *nb_neuron_actif - NB_INPUT - NB_OUTPUT;


    if (*nb_neuron_actif != 0)
    {
        double type_neuron_origine = 0;

            int alea_neuron = NB_INPUT;
            int num_actif = 0;

            num_actif = rand()%*nb_neuron_actif;
            num_actif = num_actif + 1;

            while (num_actif != 0)
            {
                alea_neuron = alea_neuron + 1;

                if (Neurones_wait [*num_obj][alea_neuron] == 1)
                {
                    num_actif = num_actif - 1;
                }
            }

                type_neuron_origine = Neurones_type_wait [*num_obj][alea_neuron];

                int new_type = rand()%NB_TYPE_NEURONES;
                new_type = new_type + 1;

                Neurones_type_wait [*num_obj][alea_neuron] = new_type;


                    int ecrire = 0;

                    if (ecrire == 1)
                    {
                                    FILE *File = NULL;

                                    File = fopen ("Modif type neuron.txt", "w+");
                                    fprintf (File, "Oeuf numero : %d --> num_neuron : %d", *num_obj, alea_neuron);
                                    fprintf (File, "\nType d'origine : %f", type_neuron_origine);
                                    fprintf (File, "\nType après mutation : %f", Neurones_type_wait [*num_obj][alea_neuron]);
                                    fclose (File);
                    }
    }
}














Mutate_supp_struct (int *num_obj, int *nb_neuron_actif)
{
        *nb_neuron_actif = *nb_neuron_actif - NB_INPUT - NB_OUTPUT;

    if (*nb_neuron_actif != 0)
    {
            int alea_neuron = NB_INPUT;
            int num_actif = 0;

            num_actif = rand()%*nb_neuron_actif;
            num_actif = num_actif + 1;

            while (num_actif != 0)
            {
                alea_neuron = alea_neuron + 1;

                if (Neurones_wait [*num_obj][alea_neuron] == 1)
                {
                    num_actif = num_actif - 1;
                }
            }

            Neurones_wait [*num_obj][alea_neuron] = 0;


            int num_synapse = 0;

            while (num_synapse != MAX_SINAPSES_BY_NEURONE)
            {
                num_synapse = num_synapse + 1;

                if (Synapse_wait [*num_obj][alea_neuron][num_synapse] == 1)
                {
                    Synapse_wait [*num_obj][alea_neuron][num_synapse] = 0;
                }
            }



            int num_neuron = 0;
            num_actif = *nb_neuron_actif - 1;

            if (*nb_neuron_actif != 0)
            {
                while (num_actif != 0)
                {
                    num_neuron = num_neuron + 1;

                    if (Neurones_wait [*num_obj][num_neuron] == 1)
                    {
                        num_actif = num_actif - 1;
                        int num_synapse = 0;

                        while (num_synapse != MAX_SINAPSES_BY_NEURONE)
                        {
                            num_synapse = num_synapse + 1;

                            if (Neurones_connected_wait [*num_obj][num_neuron][num_synapse] == alea_neuron)
                            {
                                Synapse_wait [*num_obj][num_neuron][num_synapse] = 0;
                            }
                        }
                    }
                }
            }
    }
}










ecrire_network_egg_pondu (int *num_obj)
{
                            FILE *File2 = NULL;

                            File2 = fopen ("Neurones actif Oeuf pondu.txt", "w+");
                            fprintf (File2, " Test neurones actif oeuf pondu %d \n : \n", *num_obj);

                            int num_entree = 0;

                            while (num_entree != MAX_NEURONE)
                            {
                                num_entree = num_entree + 1;
                                fprintf (File2, " Neurone %d : %f \n", num_entree, Neurones_wait [*num_obj][num_entree]);
                            }

                            fclose(File2);
}

ecrire_network_egg_eclos (int *num_obj)
{
                            FILE *File2 = NULL;

                            File2 = fopen ("Neurones actif Oeuf eclos.txt", "w+");
                            fprintf (File2, " Test neurones actif oeuf eclos %d \n : \n", *num_obj);

                            int num_entree = 0;

                            while (num_entree != MAX_NEURONE)
                            {
                                num_entree = num_entree + 1;
                                fprintf (File2, " Neurone %d : %f \n", num_entree, Neurones_wait [*num_obj][num_entree]);
                            }

                            fclose(File2);
}
