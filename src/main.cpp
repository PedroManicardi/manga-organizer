#include <iostream>
#include <vector>
#include "manga.h"

int main() {
    std::vector<Manga> mangas = loadMangasFromFile();

    while (true) {
        std::cout << "1. Adicionar Manga\n"
                  << "2. Listar Mangas\n"
                  << "3. Sair\n"
                  << "Escolha uma opção: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                addManga(mangas);
                saveMangasToFile(mangas);
                break;
            case 2:
                listMangas(mangas);
                break;
            case 3:
                return 0;
            default:
                std::cout << "Opção inválida!\n";
        }
    }

    return 0;
}
