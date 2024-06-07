#include <iostream>
#include <fstream>
#include "manga.h"

Manga::Manga() : start_year(0), end_year(0), edition_year(0), total_volumes(0), acquired_volumes(0) {}

void Manga::input() {
    std::cin.ignore();
    std::cout << "Digite o ISBN: ";
    std::getline(std::cin, ISBN);

    std::cout << "Digite o título: ";
    std::getline(std::cin, title);

    std::cout << "Digite os autores: ";
    std::getline(std::cin, authors);

    std::cout << "Digite o gênero: ";
    std::getline(std::cin, genre);

    std::cout << "Digite a revista: ";
    std::getline(std::cin, magazine);

    std::cout << "Digite a editora: ";
    std::getline(std::cin, publisher);

    std::cout << "Digite o ano de início: ";
    std::cin >> start_year;

    std::cout << "Digite o ano de fim: ";
    std::cin >> end_year;

    std::cout << "Digite o ano da edição: ";
    std::cin >> edition_year;

    std::cout << "Digite a quantidade total de volumes: ";
    std::cin >> total_volumes;

    std::cout << "Digite a quantidade de volumes adquiridos: ";
    std::cin >> acquired_volumes;

    std::cout << "Digite os números dos volumes adquiridos (separados por espaço): ";
    acquired_volumes_list.resize(acquired_volumes);
    for (int i = 0; i < acquired_volumes; ++i) {
        std::cin >> acquired_volumes_list[i];
    }
}

void Manga::print() const {
    std::cout << "ISBN: " << ISBN << "\n"
              << "Título: " << title << "\n"
              << "Autores: " << authors << "\n"
              << "Gênero: " << genre << "\n"
              << "Revista: " << magazine << "\n"
              << "Editora: " << publisher << "\n"
              << "Ano de Início: " << start_year << "\n"
              << "Ano de Fim: " << end_year << "\n"
              << "Ano da Edição: " << edition_year << "\n"
              << "Quantidade Total de Volumes: " << total_volumes << "\n"
              << "Quantidade de Volumes Adquiridos: " << acquired_volumes << "\n"
              << "Volumes Adquiridos: ";
    for (int vol : acquired_volumes_list) {
        std::cout << vol << " ";
    }
    std::cout << "\n----------------------\n";
}

void addManga(std::vector<Manga>& mangas) {
    if (mangas.size() >= MAX_MANGAS) {
        std::cout << "Limite de mangas atingido!\n";
        return;
    }

    Manga m;
    m.input();
    mangas.push_back(m);
}

void listMangas(const std::vector<Manga>& mangas) {
    for (const Manga& m : mangas) {
        m.print();
    }
}

void saveMangasToFile(const std::vector<Manga>& mangas) {
    std::ofstream file(FILE_NAME);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo para escrita!\n";
        return;
    }

    file << mangas.size() << "\n";
    for (const Manga& m : mangas) {
        file << m.ISBN << "\n"
             << m.title << "\n"
             << m.authors << "\n"
             << m.genre << "\n"
             << m.magazine << "\n"
             << m.publisher << "\n"
             << m.start_year << "\n"
             << m.end_year << "\n"
             << m.edition_year << "\n"
             << m.total_volumes << "\n"
             << m.acquired_volumes << "\n";
        for (int vol : m.acquired_volumes_list) {
            file << vol << " ";
        }
        file << "\n";
    }
}

std::vector<Manga> loadMangasFromFile() {
    std::vector<Manga> mangas;
    std::ifstream file(FILE_NAME);
    if (!file) {
        std::cerr << "Arquivo não encontrado. Iniciando uma nova coleção.\n";
        return mangas;
    }

    int count;
    file >> count;
    file.ignore();
    mangas.resize(count);
    for (int i = 0; i < count; ++i) {
        std::getline(file, mangas[i].ISBN);
        std::getline(file, mangas[i].title);
        std::getline(file, mangas[i].authors);
        std::getline(file, mangas[i].genre);
        std::getline(file, mangas[i].magazine);
        std::getline(file, mangas[i].publisher);
        file >> mangas[i].start_year;
        file >> mangas[i].end_year;
        file >> mangas[i].edition_year;
        file >> mangas[i].total_volumes;
        file >> mangas[i].acquired_volumes;
        mangas[i].acquired_volumes_list.resize(mangas[i].acquired_volumes);
        for (int j = 0; j < mangas[i].acquired_volumes; ++j) {
            file >> mangas[i].acquired_volumes_list[j];
        }
        file.ignore();
    }

    return mangas;
}

void updateManga(std::vector<Manga>& mangas) {
    listMangas(mangas);
    std::cout << "Digite o número do manga que deseja atualizar: ";
    size_t index;
    std::cin >> index;
    if (index > 0 && index <= mangas.size()) {
        mangas[index - 1].input();
        saveMangasToFile(mangas);
    } else {
        std::cout << "Número inválido!\n";
    }
}

void deleteManga(std::vector<Manga>& mangas) {
    listMangas(mangas);
    std::cout << "Digite o número do manga que deseja apagar: ";
    size_t index;
    std::cin >> index;
    if (index > 0 && index <= mangas.size()) {
        std::cout << "Tem certeza que deseja apagar o manga " << index << "? (s/n): ";
        char confirm;
        std::cin >> confirm;
        if (confirm == 's' || confirm == 'S') {
            mangas.erase(mangas.begin() + index - 1);
            saveMangasToFile(mangas);
            std::cout << "Manga apagado com sucesso.\n";
        } else {
            std::cout << "Operação cancelada.\n";
        }
    } else {
        std::cout << "Número inválido!\n";
    }
}