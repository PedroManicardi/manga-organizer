#include <stdio.h>
#include <stdlib.h>
#include "manga.h"

int main() {
    int choice;
    Manga mangas[MAX];
    int mangaCount = loadMangasFromFile(mangas);

    while (1) {
        printf("1. Adicionar Manga\n");
        printf("2. Listar Mangas\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        getchar();  // Limpar o buffer do teclado

        switch (choice) {
            case 1:
                addManga(mangas, &mangaCount);
                saveMangasToFile(mangas, mangaCount);
                break;
            case 2:
                listMangas(mangas, mangaCount);
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}