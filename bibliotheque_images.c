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
    char buffer;

    *p_lignes = 0;
    *p_colonnes = 0;
    *p_maxval = 0;

    FILE *fptr;
    fptr = fopen(nom_fichier, "r");
    if (fptr == NULL)
    {
        fclose(fptr);
        return ERREUR_FICHIER;
    }

    if (fgetc(fptr) == '#')
    {
        for (int i = 0; i < MAX_CHAINE; i++)
        {
            buffer = fgetc(fptr);
            if (buffer == ';' || buffer == '\n' || buffer == '\r')
            {
                (*p_metadonnees).auteur[i] = '\0';
                break;
            }
            else
            {
                (*p_metadonnees).auteur[i] = buffer;
            }
        }
        for (int i = 0; i < MAX_CHAINE; i++)
        {
            buffer = fgetc(fptr);
            if (buffer == ';' || buffer == '\n' || buffer == '\r')
            {
                (*p_metadonnees).dateCreation[i] = '\0';
                break;
            }
            else
            {
                (*p_metadonnees).dateCreation[i] = buffer;
            }
        }
        for (int i = 0; i < MAX_CHAINE; i++)
        {
            buffer = fgetc(fptr);
            if (buffer == ';' || buffer == '\n' || buffer == '\r')
            {
                (*p_metadonnees).lieuCreation[i] = '\0';
                break;
            }
            else
            {
                (*p_metadonnees).lieuCreation[i] = buffer;
            }
        }
    }
    else
    {
        rewind(fptr);
    }

    fscanf(fptr, "%s", format);
    if (format[0] != 'P' || format[1] != '2' || format[2] != '\0')
    {

        fclose(fptr);
        return ERREUR_FORMAT;
    }

    fscanf(fptr, "%d %d %d", p_colonnes, p_lignes, p_maxval);

    if (*p_colonnes > MAX_LARGEUR || *p_lignes > MAX_HAUTEUR)
    {
        return ERREUR_TAILLE;
    }

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

    FILE *fptr;
    fptr = fopen(nom_fichier, "w");

    if (fptr == NULL)
    {
        fclose(fptr);
        return -1;
    }

    fprintf(fptr, "#%s;%s;%s\n", metadonnees.auteur, metadonnees.dateCreation, metadonnees.lieuCreation);
    fprintf(fptr, "P2\n");
    fprintf(fptr, "%d %d\n", colonnes, lignes);
    fprintf(fptr, "%d\n", maxval);

    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            fprintf(fptr, "%d ", matrice[i][j]);
        }
        fprintf(fptr, "\n");
    }

    fclose(fptr);
    return 0;
}

int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
    (*p_lignes2) = lignes1;
    (*p_colonnes2) = colonnes1;

    for (int i = 0; i < lignes1; i++)
    {
        for (int j = 0; j < colonnes1; j++)
        {
            matrice2[i][j] = matrice1[i][j];
        }
    }
    return OK;
}

int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int histogramme[MAX_VALEUR + 1])
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
        if (histogramme[i] > preponderanteVal)
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
            if (matrice[i][j] < 0)
            {
                matrice[i][j] = 0;
            }
            else if (matrice[i][j] > maxval)
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
            if (matrice[i][j] < 0)
            {
                matrice[i][j] = 0;
            }
            else if (matrice[i][j] > maxval)
            {
                matrice[i][j] = maxval;
            }
        }
    }
    return 0;
}

int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes)
{
    if (lignes2 >= (*p_lignes) || lignes1 >= (*p_lignes) || colonnes1 >= (*p_colonnes) || colonnes2 >= (*p_colonnes))
    {
        return -1;
    }
    int buffer[MAX_HAUTEUR][MAX_LARGEUR];
    for (int i = lignes1; i <= lignes2; i++)
    {
        for (int j = colonnes1; j <= colonnes2; j++)
        {
            buffer[i - lignes1][j - colonnes1] = matrice[i][j];
        }
    }
    *p_lignes = lignes2 - lignes1 + 1;
    *p_colonnes = colonnes2 - colonnes1 + 1;
    for (int i = 0; i < *p_lignes; i++)
    {
        for (int j = 0; j < *p_colonnes; j++)
        {
            matrice[i][j] = buffer[i][j];
        }
    }
    printf("\n%d %d | %d %d | %d %d\n", lignes1, colonnes1, lignes2, colonnes2, *p_lignes, *p_colonnes);
    return 0;
}
int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
    if (lignes1 != lignes2 || colonnes1 != colonnes2)
    {
        return 1;
    }
    for (int i = 0; i < lignes1; i++)
    {
        for (int j = 0; j < colonnes1; j++)
        {
            if (matrice1[i][j] != matrice2[i][j])
            {
                return 1;
            }
        }
    }
    return 0;
}

int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
    int buffer[MAX_HAUTEUR][MAX_LARGEUR];
    int temp = 0;
    int newI, newJ;
    if (sens != 0 && sens != 1)
    {
        return -1;
    }
    for (int i = 0; i < *p_lignes; i++)
    {
        for (int j = 0; j < *p_colonnes; j++)
        {
            if (sens)
            {
                newI = *p_lignes - i - 1;
                newJ = j;
            }
            else
            {
                newI = i;
                newJ = *p_colonnes - j - 1;
            }
            buffer[newJ][newI] = matrice[i][j];
        }
    }
    temp = *p_lignes;
    *p_lignes = *p_colonnes;
    *p_colonnes = temp;

    for (int i = 0; i < *p_lignes; i++)
    {
        for (int j = 0; j < *p_colonnes; j++)
        {
            matrice[i][j] = buffer[i][j];
        }
    }
    return 0;
}

int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
    char format[MAX_CHAINE];
    char buffer;
    *p_lignes = 0;
    *p_colonnes = 0;
    *p_maxval = 0;

    FILE *fptr;
    fptr = fopen(nom_fichier, "r");
    printf("\n%s\n", nom_fichier);
    if (fptr == NULL)
    {
        fclose(fptr);
        return ERREUR_FICHIER;
    }
    if (fgetc(fptr) == '#')
    {
        for (int i = 0; i < MAX_CHAINE; i++)
        {
            buffer = fgetc(fptr);
            if (buffer == ';' || buffer == '\n' || buffer == '\r')
            {
                (*p_metadonnees).auteur[i] = '\0';
                break;
            }
            else
            {
                (*p_metadonnees).auteur[i] = buffer;
            }
        }
        for (int i = 0; i < MAX_CHAINE; i++)
        {
            buffer = fgetc(fptr);
            if (buffer == ';' || buffer == '\n' || buffer == '\r')
            {
                (*p_metadonnees).dateCreation[i] = '\0';
                break;
            }
            else
            {
                (*p_metadonnees).dateCreation[i] = buffer;
            }
        }
        for (int i = 0; i < MAX_CHAINE; i++)
        {
            buffer = fgetc(fptr);
            if (buffer == ';' || buffer == '\n' || buffer == '\r')
            {
                (*p_metadonnees).lieuCreation[i] = '\0';
                break;
            }
            else
            {
                (*p_metadonnees).lieuCreation[i] = buffer;
            }
        }
    }
    else
    {
        rewind(fptr);
    }

    fscanf(fptr, "%s", format);
    if (format[0] != 'P' || format[1] != '3' || format[2] != '\0')
    {

        fclose(fptr);
        return ERREUR_FORMAT;
    }

    fscanf(fptr, "%d %d %d", p_colonnes, p_lignes, p_maxval);
    if (*p_colonnes > MAX_LARGEUR || *p_lignes > MAX_HAUTEUR)
    {
        return ERREUR_TAILLE;
    }

    for (int i = 0; i < (*p_lignes); i++)
    {
        for (int j = 0; j < (*p_colonnes); j++)
        {
            fscanf(fptr, "%d %d %d", &matrice[i][j].valeurR, &matrice[i][j].valeurG, &matrice[i][j].valeurB);
        }
    }

    fclose(fptr);
    return OK;
}

int ppm_ecrire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
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
    fprintf(fptr, "P3\n");
    fprintf(fptr, "%d %d\n", colonnes, lignes);
    fprintf(fptr, "%d\n", maxval);

    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            fprintf(fptr, "%d %d %d ", matrice[i][j].valeurR, matrice[i][j].valeurG, matrice[i][j].valeurB);
        }
        fprintf(fptr, "\n");
    }

    fclose(fptr);
    return 0;
}
int ppm_copier(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
    (*p_lignes2) = lignes1;
    (*p_colonnes2) = colonnes1;

    for (int i = 0; i < lignes1; i++)
    {
        for (int j = 0; j < colonnes1; j++)
        {
            matrice2[i][j].valeurR = matrice1[i][j].valeurR;
            matrice2[i][j].valeurG = matrice1[i][j].valeurG;
            matrice2[i][j].valeurB = matrice1[i][j].valeurB;
        }
    }
    return 0;
}
int ppm_sont_identiques(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
    if (lignes1 != lignes2 || colonnes1 != colonnes2)
    {
        return 1;
    }
    for (int i = 0; i < lignes1; i++)
    {
        for (int j = 0; j < colonnes1; j++)
        {
            if (matrice1[i][j].valeurR != matrice2[i][j].valeurR || matrice1[i][j].valeurG != matrice2[i][j].valeurG || matrice1[i][j].valeurB != matrice2[i][j].valeurB)
            {
                return 1;
            }
        }
    }
    return 0;
}
int ppm_pivoter90(struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
    struct RGB buffer[MAX_HAUTEUR][MAX_LARGEUR];
    int temp = 0;
    int newI, newJ;
    if (sens != 0 && sens != 1)
    {
        return -1;
    }
    for (int i = 0; i < *p_lignes; i++)
    {
        for (int j = 0; j < *p_colonnes; j++)
        {
            if (sens)
            {
                newI = *p_lignes - i - 1;
                newJ = j;
            }
            else
            {
                newI = i;
                newJ = *p_colonnes - j - 1;
            }
            buffer[newJ][newI].valeurR = matrice[i][j].valeurR;
            buffer[newJ][newI].valeurG = matrice[i][j].valeurG;
            buffer[newJ][newI].valeurB = matrice[i][j].valeurB;
        }
    }
    temp = *p_lignes;
    *p_lignes = *p_colonnes;
    *p_colonnes = temp;

    for (int i = 0; i < *p_lignes; i++)
    {
        for (int j = 0; j < *p_colonnes; j++)
        {
            matrice[i][j].valeurR = buffer[i][j].valeurR;
            matrice[i][j].valeurG = buffer[i][j].valeurG;
            matrice[i][j].valeurB = buffer[i][j].valeurB;
        }
    }
    return 0;
}
