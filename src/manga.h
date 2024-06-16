#ifndef MANGA_H
#define MANGA_H

#define MAX 100
#define FILE_NAME "mangas.txt"
#define PRIMARY_INDEX_FILE "primary_index.txt"
#define SECONDARY_INDEX_FILE "secondary_index.txt"
#define DELIMITER "|"

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
void createPrimaryIndex(Manga mangas[], int count);
void createSecondaryIndex(Manga mangas[], int count);
int getRecordPositionByTitle(const char *title);
void retrieveMangaByTitle(const char *title);
int loadMangasFromFile(Manga mangas[]);
void deleteMangaByTitle(const char *title);

#endif