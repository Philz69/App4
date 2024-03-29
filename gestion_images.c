/********
Fichier: gestion_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include <stdio.h>
#include "bibliotheque_images.h"
#include "AutoValidation.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];

int main()
{
    AutoValidation();
    /*int lignes1, colonnes1;
    int lignes2, colonnes2;
    int maxval;
    int histogramme[MAX_VALEUR + 1];
    char nom[MAX_CHAINE] = "images/validation.pgm";
    struct MetaData metadonnees;
    int debug = 0;
    int retour;

    printf("-> Debut!\n");

    // exemple d'appel de fonction
    retour = pgm_lire(nom, image1,
                      &lignes1, &colonnes1,
                      &maxval, &metadonnees);

    printf("\n%d %d %d\n", lignes1, colonnes1);
    printf("%s %s %s", metadonnees.auteur, metadonnees.dateCreation, metadonnees.lieuCreation);
    if (debug)
    {
        printf("%d, %d, %d", lignes1, colonnes1, maxval);

       if(debug)
       {
        for (int i = 0; i < lignes1; i++)
        {
            for (int j = 0; j < colonnes1; j++)
            {
                printf("%d", image1[i][j]);
               
            }
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
        if (debug)
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
        if (debug)
        {
            printf("Valeur la plus commune: %d", retour);
        }
    }

    retour = pgm_eclaircir_noircir(image1, lignes1, colonnes1, maxval, 50);
    if(!retour)
    {
        printf("Succes eclaircir noircir \n");
       pgm_creer_histogramme(image1, lignes1, colonnes1, histogramme) ;
       if(debug)
       {
            for (int i = 0; i < maxval + 1; i++)
            {
                printf("%d|", histogramme[i]);
            }
       }
    }

    retour = pgm_copier(image1, lignes1, colonnes1, image2, &lignes2, &colonnes2);
    retour = pgm_creer_negatif(image2, lignes1, colonnes1, maxval);
    if(!retour)
    {
        printf("Succes negatif\n");
       pgm_creer_histogramme(image2, lignes1, colonnes1, histogramme) ;
       if(debug)
       {
            for (int i = 0; i < maxval + 1; i++)
            {
                printf("%d|", histogramme[i]);
            }
       }
    }

    retour = pgm_copier(image1, lignes1, colonnes1, image2, &lignes2, &colonnes2);
    retour = pgm_eclaircir_noircir(image2, lignes2, colonnes2, maxval, 50);
    pgm_ecrire("noircir.pgm", image2, lignes2, colonnes2, maxval, metadonnees);
    retour = pgm_copier(image1, lignes1, colonnes1, image2, &lignes2, &colonnes2);
    retour = pgm_creer_negatif(image2, lignes1, colonnes1, maxval);
    pgm_ecrire("negatif.pgm", image2, lignes2, colonnes2, maxval, metadonnees);
    retour = pgm_copier(image1, lignes1, colonnes1, image2, &lignes2, &colonnes2);
    retour = pgm_extraire(image2,100,100,150,150, &lignes2, &colonnes2);
    pgm_ecrire("extraire.pgm", image2, lignes2, colonnes2, maxval, metadonnees);

    //retour = pgm_sont_identiques(image1, lignes1, colonnes1, image2, lignes2, colonnes2);
    //retour = pgm_pivoter90(image1, &lignes1, &colonnes1, 0);
    pgm_ecrire("extract.pgm", image1,
               lignes1, colonnes1,
               maxval, metadonnees);

    printf("-> Fin!\n");
    ppm_lire("Sherbrooke_Frontenac_nuit.ppm", imageRGB1, &lignes1, &colonnes1, &maxval, &metadonnees);
    ppm_copier(imageRGB1, lignes1, colonnes1, imageRGB2, &lignes2, &colonnes2);
    ppm_pivoter90(imageRGB2, &lignes2, &colonnes2, 1);
    ppm_ecrire("rgb.ppm", imageRGB2, lignes2, colonnes2, maxval, metadonnees);*/
    return 0;
}
