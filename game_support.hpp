#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

#ifndef GAME_SUPPORT_HPP
#define GAME_SUPPORT_HPP

/*
allocate a two-dimensional array of size n × m,
where n and m are the number of rows and columns
and initialize this array with the space character (’ ’).
*/
inline char** allocate_tab_2D(int n, int m)
{
    char** tab = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++)
        tab[i] = (char*)malloc(m * sizeof(char));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            tab[i][j] = ' ';
        }
    }
    return tab;
}

/*
free a two-dimensional array, of n rows.
*/
inline void desallocate_tab_2D(char** tab, int n) {
    for (int i = 0; i < n; ++i) {
        free(tab[i]);
    }
}

/*
display the contents of a character array of size n × m.
*/
inline void print_tab_2D(char** tab, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c", tab[i][j]);
        }
        printf("\n");
    }
}

/*
count the maximum number of rows (nbLin) and columns (nbCol) in the file whose name is fileName
*/
inline void file_size(const char* fileName, int* nbLin, int* nbCol) {

    FILE* file = NULL;
    file = fopen(fileName, "r");
    int c;
    int max = 0;

    if (file != NULL) {
        do {
            c = fgetc(file);
            if (c == '\n' || c == '\r' || c == EOF) {
                if (*nbCol > max) {
                    max = *nbCol;
                }
                (*nbLin)++;
                (*nbCol) = 0;
                if (c == '\r') {
                    c = fgetc(file);
                }
            } else {
                (*nbCol)++;
            }

        } while (c != EOF);

        *nbCol = max;
        fclose(file);
    } else {
        printf("file introuvable");
    }
}


/*
read a file whose name is fileName
and return the array that contains the characters of the file
so that a line of the array corresponds to a line of the file.
*/
inline char** lire_fichier(const char* fileName) {
    int line = 0;
    int column = 0;

    int lig = 0;
    int col = 0;

    file_size(fileName, &line, &column);

    char** tab = allocate_tab_2D(line, column);

    FILE* file = NULL;
    file = fopen(fileName, "r");
    int c;
    if (file != NULL) {
        do {
            c = fgetc(file);
            if (c == '\n' || c == '\r' || c == EOF) {
                lig++;
                col = 0;
                if (c == '\r') {
                    c = fgetc(file);
                }
            } else {
                tab[lig][col] = c;
                col++;
            }
        } while (c != EOF);
        fclose(file);
    } else {
        printf("file introuvable ??????");
    }
    return tab;
}

SDL_Texture *load_image(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Error while charging an image BMP: %s", SDL_GetError());
        return NULL;
    }
    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 255, 0, 255));
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Error while creating a texture: %s", SDL_GetError());
        return NULL;
    }
    return texture;
}
#endif
