#ifndef MANGA_H
#define MANGA_H

#define MAX 100
#define FILE_NAME "mangas.txt"

typedef struct {
    char ISBN[20];
    char title[MAX];
    char authors[MAX];
    char genre[MAX];
    char magazine[MAX];
    char publisher[MAX];
    int start_year;
    int end_year;
    int edition_year;
    int total_volumes;
    int acquired_volumes;
    int acquired_volumes_list[MAX];
} Manga;

void addManga(Manga mangas[], int *count);
void listMangas(Manga mangas[], int count);
void saveMangasToFile(Manga mangas[], int count);
int loadMangasFromFile(Manga mangas[]);

#endif