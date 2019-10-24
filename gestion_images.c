/********
Fichier: gestion_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include <stdio.h>
#include "bibliotheque_images.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];

int main()
{
    int lignes1, colonnes1;
    int lignes2, colonnes2;
    int maxval;
    int histogramme[MAX_VALEUR + 1];
    char nom[MAX_CHAINE] = "Sherbrooke_Frontenac_nuit.pgm";
    struct MetaData metadonnees;
    int debug = 0;
    int retour;

    printf("-> Debut!\n");

    // exemple d'appel de fonction
    retour = pgm_lire(nom, image1,
                      &lignes1, &colonnes1,
                      &maxval, &metadonnees);

    if (debug)
    {
        printf("%d, %d, %d", lignes1, colonnes1, maxval);
        printf("%s %s %s", metadonnees.auteur, metadonnees.dateCreation, metadonnees.lieuCreation);
        for (int i = 0; i < lignes1; i++)
        {
            for (int j = 0; j < colonnes1; j++)
            {
                printf("%d", image1[i][j]);
            }
        }
    }
    // exemple detraitement d'un code de retour (erreur ou reussite)
    printf("-> Retour: ");
    if (retour == OK)
        printf("-> OK");
    else
        printf("-> ERREUR");
    printf("\n");

    // autre exemple d'appel de fonction
    retour = pgm_copier(image1, lignes1, colonnes1, image2, &lignes2, &colonnes2);
    if (!retour)
    {
        printf("Succes copie\n");
    }

    retour = pgm_creer_histogramme(image1, lignes1, colonnes2, histogramme);
    if (!retour)
    {
        printf("Succes histogramme\n");
        if (!debug)
        {
            for (int i = 0; i < maxval + 1; i++)
            {
                printf("%d|", histogramme[i]);
            }
        }
    }

    retour = pgm_couleur_preponderante(image1, lignes1, colonnes1);
    if (retour > 0)
    {
        printf("Succes preponderante\n");
        if (!debug)
        {
            printf("Valeur la plus commune: %d", retour);
        }
    }

    retour = pgm_eclaircir_noircir(image2, lignes1, colonnes1, maxval, 50);
    if(!retour)
    {
       pgm_creer_histogramme(image1, lignes1, colonnes1, histogramme) ;
            for (int i = 0; i < maxval + 1; i++)
            {
                printf("%d|", histogramme[i]);
            }

    }

    pgm_ecrire("test.pgm", image2,
               lignes2, colonnes2,
               maxval, metadonnees);

    printf("-> Fin!\n");

    return 0;
}
