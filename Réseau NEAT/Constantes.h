#ifndef DEF_CONSTANTES

#define DEF_CONSTANTES

    #define LARGEUR_FENETRE  900
    #define HAUTEUR_FENETRE  700



    #define MAX_OBJECT 300
    #define NB_TYPE_OBJECT 4

    #define TYPE_CELL 1
    #define TYPE_OEUF 2
    #define TYPE_FOOD 3
    #define TYPE_CELL_SOUCHE 4

    #define NB_CELL_TYPE 2
    #define CELL_TYPE_BASE 1
    #define CELL_TYPE_PREDATRICE 2



    #define NB_INPUT 50
    #define NB_OUTPUT 3
    #define MAX_SS_COUCHE 500

    #define MAX_NEURONE 1000
    #define MAX_SINAPSES_BY_NEURONE 100


    #define NB_TYPE_NEURONES 8
    #define NEURONE_SIG 1
    #define NEURONE_LIN 2
    #define NEURONE_SQR 3
    #define NEURONE_SIN 4
    #define NEURONE_ABS 5
    #define NEURONE_REL 6
    #define NEURONE_GAU 7
    #define NEURONE_LAT 8

    #define NB_TYPE_MUTATIONS 5
    #define MUTATION_ADD_SYNAPSE 1
    #define MUTATION_MODIF_SYNAPSE 2
    #define MUTATION_ADD_NEURON 3
    #define MUTATION_MODIF_NEURON 4
    #define MUTATION_SUPP_STRUCTURE 5

    #define MAX_MUTATION_BY_EGG 50

    #define FACTEUR_MUTATION_MAX 10



    #define ENERGIE_NAISSANCE_CELL 500
    #define LIMITE_INF_E_CELL 10
    #define LIMITE_SUP_E_CELL 1000
    #define PERTE_E_BY_BOUCLE 0.01
    #define FACTEUR_PERTE_E_VITESSE 2

    #define PERTE_E_PONTE 100
    #define ENERGIE_NECESSAIR_PONTE 500

    #define ENERGIE_FOOD 100
    #define GAIN_E_OEUF_BY_BOUCLE 0.05

    #define PERTE_E_AGRESSION 100




    #define DISTANCE_PERCEPTION 150




    #define FACTEUR_INERTIE 0.0025
    #define APPORT_VITESSE 0.001



    #define FORCE_REPULSION_COLLISION 1000


    #define AFFICHAGE_ENVI 1

#endif
