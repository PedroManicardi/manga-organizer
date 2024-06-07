#ifndef MANGA_H
#define MANGA_H

#include <string>
#include <vector>

#define MAX_MANGAS 100
#define MAX_VOLUMES 200
#define FILE_NAME "mangas.txt"

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

#endif
