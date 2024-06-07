#ifndef MANGA_H
#define MANGA_H

#include <string>
#include <vector>

#define FILE_NAME "mangas.txt"
#define PRIMARY_INDEX_FILE "primary_index.txt"
#define SECONDARY_INDEX_FILE "secondary_index.txt"

class Manga {
public:
    std::string ISBN;
    std::string title;
    std::string authors;
    std::string genre;
    std::string magazine;
    std::string publisher;
    int start_year;
    int end_year;
    int edition_year;
    int total_volumes;
    int acquired_volumes;
    std::vector<int> acquired_volumes_list;

    Manga();
    void input();
    void print() const;
};

void addManga(std::vector<Manga>& mangas);
void listMangas(const std::vector<Manga>& mangas);
void saveMangasToFile(const std::vector<Manga>& mangas);
std::vector<Manga> loadMangasFromFile();
void updateManga(std::vector<Manga>& mangas);
void deleteManga(std::vector<Manga>& mangas);
void updatePrimaryIndex(const std::vector<Manga>& mangas);
void updateSecondaryIndex(const std::vector<Manga>& mangas);

#endif
