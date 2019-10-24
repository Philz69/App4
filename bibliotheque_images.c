/********
Fichier: bibliotheque_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include "bibliotheque_images.h"

int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR],
             int *p_lignes, int *p_colonnes,
             int *p_maxval, struct MetaData *p_metadonnees)
{
    char format[MAX_CHAINE];

    (*p_lignes) = 0;
    (*p_colonnes) = 0;
    (*p_maxval) = 0;

    FILE *fptr;
    fptr = fopen(nom_fichier, "r");

    if (fptr == NULL)
    {
        fclose(fptr);
        return -1;
    }

    /*if (fgetc(fptr) == "#")
    {
        fscanf(fptr, "#%s;%s;%s", (*p_metadonnees).auteur, (*p_metadonnees).dateCreation, (*p_metadonnees).lieuCreation);
    }*/

    fscanf(fptr, "%s", format);
    if (strcmp(format, "P2"))
    {
        fclose(fptr);
        return -1;
    }

    fscanf(fptr, "%d %d %d", p_lignes, p_colonnes, p_maxval);

    for (int i = 0; i < (*p_lignes); i++)
    {
        for (int j = 0; j < (*p_colonnes); j++)
        {
            fscanf(fptr, "%d", &matrice[i][j]);
        }
    }

    fclose(fptr);
    return OK;
}

int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR],
               int lignes, int colonnes,
               int maxval, struct MetaData metadonnees)
{
    char format[MAX_CHAINE];

    FILE *fptr;
    fptr = fopen(nom_fichier, "w");

    if (fptr == NULL)
    {
        fclose(fptr);
        return -1;
    }

        fprintf(fptr, "#%s;%s;%s\n", metadonnees.auteur, metadonnees.dateCreation, metadonnees.lieuCreation);
        fprintf(fptr, "P2\n");
        fprintf(fptr, "%d %d\n%d\n", lignes, colonnes, maxval);



    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            fprintf(fptr, "%d ", matrice[i][j]);
        }
        fprintf(fptr, "\n");
    }

    fclose(fptr);
    return OK;
}

int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
    (*p_lignes2) =  lignes1;
    (*p_colonnes2) =  colonnes1;

    for (int i = 0; i < lignes1; i++)
    {
        for (int j = 0; j < colonnes1; j++)
        {
             matrice2[i][j] = matrice1[i][j];
        }
    }
    return 0;
}

int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int histogramme[MAX_VALEUR+1]) 
{

    for (int i = 0; i < MAX_VALEUR + 1; i++)
    {
        histogramme[i] = 0;
    }

    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            histogramme[matrice[i][j]]++;
        }
    }
    return 0;
}

int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes)
{   
    int histogramme[MAX_VALEUR];
    pgm_creer_histogramme(matrice, lignes, colonnes, histogramme);
    int preponderantePos = 0;
    int preponderanteVal = 0;
    for (int i = 0; i < MAX_VALEUR; i++)
    {
       if(histogramme[i] > preponderanteVal)
       {
           preponderantePos = i;
           preponderanteVal = histogramme[i];
       } 
    }
    return preponderantePos;
}
int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur)
{
    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
           matrice[i][j] = matrice[i][j] + valeur;
           if(matrice[i][j] < 0)
           {
               matrice[i][j] = 0;
           }
           else if(matrice[i][j] > maxval)
           {
               matrice[i][j] = maxval;
           }
        }
    }
    return 0;
}
int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval)
{
    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
           matrice[i][j] = maxval - matrice[i][j];
           if(matrice[i][j] < 0)
           {
               matrice[i][j] = 0;
           }
           else if(matrice[i][j] > maxval)
           {
               matrice[i][j] = maxval;
           }
        }
    }
    return 0;
}

int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes)
{
    int buffer[MAX_HAUTEUR][MAX_LARGEUR];
    for (int i = lignes1; i < lignes2; i++)
    {
        for (int j = colonnes1; j < colonnes2; j++)
        {
            buffer[i - lignes1][j - colonnes1] = matrice[i][j];
        }
    }
    for (int i = 0; i < lignes2 - lignes1; i++)
    {
        for (int j = 0; j < colonnes2 - colonnes1; j++)
        {
            matrice[i][j]  = buffer[i][j];
        }
    }
    (*p_lignes) = lignes2 - lignes1;
    (*p_colonnes) = colonnes2 - colonnes1;
}