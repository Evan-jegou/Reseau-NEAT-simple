#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#include "Constantes.h"

    int ini_network = 0;

    int num_parent_network = 0;
    int nb_input = 0;

    double Input [NB_INPUT + 1] = {0};

    double Neurones [MAX_OBJECT + 1][MAX_NEURONE + 1] = {0};

    double Neurones_type [MAX_OBJECT + 1][MAX_NEURONE + 1] = {0};
    double Neurones_val_entree [MAX_OBJECT + 1][MAX_NEURONE + 1] = {0};
    double Neurones_val_sortie [MAX_OBJECT + 1][MAX_NEURONE + 1] = {0};

    double Synapse [MAX_OBJECT + 1][MAX_NEURONE + 1][MAX_SINAPSES_BY_NEURONE + 1] = {0};
    double Val_synapse [MAX_OBJECT + 1][MAX_NEURONE + 1][MAX_SINAPSES_BY_NEURONE + 1] = {0};
    double Neurones_connected [MAX_OBJECT + 1][MAX_NEURONE + 1][MAX_SINAPSES_BY_NEURONE + 1] = {0};


Network (int *num_obj, int *dir_x, int *dir_y, int *lay)
{
                                                                                Initialiser_network ();

        int num_input = 0;

        while (num_input != NB_INPUT)
        {
            num_input = num_input + 1;

            Neurones_val_entree [*num_obj][num_input] = Input [num_input];
        }



        int num_neuron = 0;

            while (num_neuron != MAX_SS_COUCHE)
            {
                num_neuron = num_neuron + 1;

                if (Neurones [*num_obj][num_neuron] == 1)
                {

                    double valeur = Neurones_val_entree [*num_obj][num_neuron];

                                                                            Fonction_neurone (num_obj, &valeur, &num_neuron);

                    Neurones_val_sortie [*num_obj][num_neuron] = valeur;
                    Neurones_val_entree [*num_obj][num_neuron] = 0;
                }
            }

            num_neuron = 0;

            while (num_neuron != MAX_SS_COUCHE)
            {
                num_neuron = num_neuron + 1;

                if (Neurones [*num_obj][num_neuron] == 1)
                {
                    int num_synapse = 0;

                    while (num_synapse != MAX_SINAPSES_BY_NEURONE)
                    {
                        num_synapse = num_synapse + 1;

                        if (Synapse [*num_obj][num_neuron][num_synapse] == 1)
                        {
                            int neuron_connecte = Neurones_connected [*num_obj][num_neuron][num_synapse];

                            double valeur = Neurones_val_sortie [*num_obj][num_neuron] * Val_synapse [*num_obj][num_neuron][num_synapse];
                            Neurones_val_entree [*num_obj][neuron_connecte] = Neurones_val_entree [*num_obj][neuron_connecte] + valeur;

                        }
                    }
                }
            }
                                                                Envoi_sortie_reseau (num_obj, dir_x, dir_y, lay);

}






Initialiser_network ()
{
    if (ini_network == 0)
    {
        int num_object = 0;

        while (num_object != MAX_OBJECT)
        {
            num_object = num_object + 1;
            int neuron = 0;

            while (neuron != NB_INPUT)
            {
                neuron = neuron + 1;

                Neurones [num_object][neuron] = 1;
                Neurones_type [num_object][neuron] = NEURONE_LIN;
                Neurones_val_entree [num_object][neuron] = 0;
                Neurones_val_sortie [num_object][neuron] = 0;

                int num_synapse = 0;

                while (num_synapse != MAX_SINAPSES_BY_NEURONE)
                {
                    num_synapse = num_synapse + 1;

                    Synapse [num_object][neuron][num_synapse] = 0;
                    Val_synapse [num_object][neuron][num_synapse] = 0;
                    Neurones_connected [num_object][neuron][num_synapse] = 0;
                }
            }

            neuron = NB_INPUT;

            while (neuron != (MAX_SS_COUCHE - NB_OUTPUT))
            {
                neuron = neuron + 1;

                Neurones [num_object][neuron] = 0;
                Neurones_type [num_object][neuron] = NEURONE_LIN;
                Neurones_val_entree [num_object][neuron] = 0;
                Neurones_val_sortie [num_object][neuron] = 0;

                int num_synapse = 0;

                while (num_synapse != MAX_SINAPSES_BY_NEURONE)
                {
                    num_synapse = num_synapse + 1;

                    Synapse [num_object][neuron][num_synapse] = 0;
                    Val_synapse [num_object][neuron][num_synapse] = 0;
                    Neurones_connected [num_object][neuron][num_synapse] = 0;
                }
            }


            neuron = (MAX_SS_COUCHE - NB_OUTPUT);

            while (neuron != MAX_SS_COUCHE)
            {
                neuron = neuron + 1;

                Neurones [num_object][neuron] = 1;
                Neurones_type [num_object][neuron] = NEURONE_SIG;
                Neurones_val_entree [num_object][neuron] = 0;
                Neurones_val_sortie [num_object][neuron] = 0;

                int num_synapse = 0;

                while (num_synapse != MAX_SINAPSES_BY_NEURONE)
                {
                    num_synapse = num_synapse + 1;

                    Synapse [num_object][neuron][num_synapse] = 0;
                    Val_synapse [num_object][neuron][num_synapse] = 0;
                    Neurones_connected [num_object][neuron][num_synapse] = 0;
                }
            }
        }
        ini_network = 1;
    }
}



Add_Input (int *ini_input, double *Val_Entree)
{
    if (*ini_input == 0)
    {
        int num_entree = 0;

        while (num_entree != NB_INPUT)
        {
            num_entree = num_entree + 1;

            Input [num_entree] = 0;
        }

        *ini_input = 1;
        nb_input = 0;
    }

    nb_input = nb_input + 1;
    Input [nb_input] = *Val_Entree;

}




Envoi_sortie_reseau (int *num_obj, int *dir_x, int *dir_y, int *lay)
{
    int Bin = 0;
    int num_output = MAX_SS_COUCHE - NB_OUTPUT;

    while (num_output != MAX_SS_COUCHE)
    {
        num_output = num_output + 1;

        double valeur_output = Neurones_val_sortie [*num_obj][num_output];

                if (valeur_output > 0.5)
                {
                    Bin = 1;
                }
                else if (valeur_output < 0.5)
                {
                    Bin = -1;
                }
                else if (valeur_output == 0.5)
                {
                    Bin = 0;
                }

        if ((MAX_SS_COUCHE - num_output) == 0)
        {
            *dir_x = Bin;
        }
        else if ((MAX_SS_COUCHE - num_output) == 1)
        {
            *dir_y = Bin;
        }
        else if ((MAX_SS_COUCHE - num_output) == 2)
        {
            *lay = Bin;
        }
    }




                    int ecrire = 0;


                        if (*num_obj == 6 && ecrire == 1)
                            {

                                FILE *File = NULL;

                                File = fopen ("Sortie.txt", "w+");
                                fprintf (File, " Test Sortie neurone Cellule %d \n : \n", *num_obj);

                                int num_entree = 0;

                                while (num_entree != MAX_NEURONE)
                                {
                                    num_entree = num_entree + 1;
                                    fprintf (File, " Valeur de sortie du neurone %d : %f \n", num_entree, Neurones_val_sortie [*num_obj][num_entree]);
                                }

                                fclose(File);
                            }

}




 Send_parent_network (int *num_obj)
 {
     num_parent_network = *num_obj;
 }





Add_network_obj (int *type, int *num_obj)
{
    if (*type == TYPE_OEUF)
    {
        int parent = num_parent_network;
        num_parent_network = 0;
                                                            Send_network_cell (num_obj, &parent);
                                                            Mutation_network (num_obj);
    }

    if (*type == TYPE_CELL)
    {
        int parent = num_parent_network;
        num_parent_network = 0;
                                                            Recup_network_cell (num_obj, &parent);
    }
}


Send_network_cell (int *num_obj, int *parent)
{
    int num_neuron = 0;

    while (num_neuron != MAX_SS_COUCHE)
    {
        num_neuron = num_neuron + 1;

        if (Neurones [*parent][num_neuron] == 1)
        {
            int recup_neuron = 0;

            double neuron =  Neurones [*parent][num_neuron];
            double type = Neurones_type [*parent][num_neuron];
            double val_neuron = Neurones_val_entree [*parent][num_neuron];
            double val_sortie_neuron = Neurones_val_sortie [*parent][num_neuron];

                int num_synapse = 0;

                while (num_synapse != MAX_SINAPSES_BY_NEURONE)
                {
                    num_synapse = num_synapse + 1;

                    double synapse = Synapse [*parent][num_neuron][num_synapse];
                    double val_synapse = Val_synapse [*parent][num_neuron][num_synapse];
                    double neuron_connecte = Neurones_connected [*parent][num_neuron][num_synapse];

                                                                                                        Recup_network_egg (num_obj, &num_neuron, &num_synapse, &recup_neuron, &neuron, &type, &val_neuron, &val_sortie_neuron, &synapse, &val_synapse, &neuron_connecte);
                }
        }
    }

                        int ecrire = 0;

                        if (ecrire == 1)
                        {
                            FILE *File = NULL;

                            File = fopen ("Ponte.txt", "w+");
                            fprintf (File, "Oeuf numero %d , pondu par la cellule numero %d", *num_obj, *parent);
                            fclose (File);


                            FILE *File2 = NULL;

                            File2 = fopen ("Neurones actif cellule pondeuse.txt", "w+");
                            fprintf (File2, " Test neurone actif cell %d \n : \n", *parent);

                            int num_entree = 0;

                            while (num_entree != MAX_NEURONE)
                            {
                                num_entree = num_entree + 1;
                                fprintf (File2, " Neurone %d : %f \n", num_entree, Neurones [*parent][num_entree]);
                            }

                            fclose(File2);
                                                                                                        ecrire_network_egg_pondu (num_obj);
                        }


}




Recup_network_cell (int *num_obj, int *parent)
{
    int num_neuron = 0;

    while (num_neuron != MAX_SS_COUCHE)
    {
        int recup_neuron = 0;
        num_neuron = num_neuron + 1;

        double neuron =  0;
        double type = 0;
        double val_neuron = 0;
        double val_sortie_neuron = 0;

            int num_synapse = 0;

            while (num_synapse != MAX_SINAPSES_BY_NEURONE)
            {
                num_synapse = num_synapse + 1;

                double synapse = 0;
                double val_synapse = 0;
                double neuron_connecte = 0;
                                                                        Send_network_egg (parent, &num_neuron, &num_synapse, &recup_neuron, &neuron, &type, &val_neuron, &val_sortie_neuron, &synapse, &val_synapse, &neuron_connecte);

                if (recup_neuron == 0)
                {
                    Neurones [*num_obj][num_neuron] = neuron;
                    Neurones_type [*num_obj][num_neuron] = type;
                    Neurones_val_entree [*num_obj][num_neuron] = val_neuron;
                    Neurones_val_sortie [*num_obj][num_neuron] = val_sortie_neuron;

                    recup_neuron = 1;
                }


                Synapse [*num_obj][num_neuron][num_synapse] = synapse;
                Val_synapse [*num_obj][num_neuron][num_synapse] = val_synapse;
                Neurones_connected [*num_obj][num_neuron][num_synapse] = neuron_connecte;

            }
    }
                        int ecrire = 0;

                        if (ecrire == 1)
                        {

                            FILE *File = NULL;

                            File = fopen ("Eclosion.txt", "w+");
                            fprintf (File, "Oeuf numero %d , éclos en la cellule numero %d", *parent, *num_obj);
                            fclose (File);


                            FILE *File2 = NULL;

                            File2 = fopen ("Neurones actif naissance cell.txt", "w+");
                            fprintf (File2, " Test neurone actif cell %d \n : \n", *num_obj);

                            int num_entree = 0;

                            while (num_entree != MAX_NEURONE)
                            {
                                num_entree = num_entree + 1;
                                fprintf (File2, " Neurone %d : %f \n", num_entree, Neurones [*num_obj][num_entree]);
                            }

                            fclose(File2);
                                                                                                        ecrire_network_egg_eclos (parent);

                        }
}






















Fonction_neurone (int *num_obj, double *valeur, int *num_neuron)
{
    if (Neurones_type [*num_obj][*num_neuron] == NEURONE_LIN)
    {
                                                                            Linear (valeur);
    }
    else if (Neurones_type [*num_obj][*num_neuron] == NEURONE_SIG)
    {
                                                                            Sigmoid (valeur);
    }
    else if (Neurones_type [*num_obj][*num_neuron] == NEURONE_SIN)
    {
                                                                            Sinus (valeur);
    }
    else if (Neurones_type [*num_obj][*num_neuron] == NEURONE_SQR)
    {
                                                                            Square (valeur);
    }
    else if (Neurones_type [*num_obj][*num_neuron] == NEURONE_ABS)
    {
                                                                            Absolute (valeur);
    }
    else if (Neurones_type [*num_obj][*num_neuron] == NEURONE_REL)
    {
                                                                            Reluctant (valeur);
    }
    else if (Neurones_type [*num_obj][*num_neuron] == NEURONE_GAU)
    {
                                                                            Gaussian (valeur);
    }
}




reinitialisation_network ()
{
    ini_network = 0;
}
