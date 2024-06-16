#include <stdio.h>
#include <stdlib.h>
#include "manga.h"

int main() {
    int choice;
    Manga mangas[MAX];
    int mangaCount = loadMangasFromFile(mangas);
    char title[100];

    while (1) {
        printf("\nEscolha o que deseja fazer:\n");
        printf("1. Adicionar Manga\n");
        printf("2. Listar Mangas\n");
        printf("3. Buscar Manga (pelo titulo)\n");
        printf("4. Apagar Manga (pelo titulo)\n");
        printf("5. Editar Manga (pelo titulo)\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        getchar();  // Limpar o buffer do teclado
        printf("\n");

        switch (choice) {
            case 1:
                addManga(mangas, &mangaCount);
                saveMangasToFile(mangas, mangaCount);
                createPrimaryIndex(mangas, mangaCount);
                createSecondaryIndex(mangas, mangaCount);
                break;
            case 2:
                listMangas(mangas, mangaCount);
                break;
            case 3:
                printf("Digite o titulo do manga: ");
                scanf("%99[^\n]", title);
                retrieveMangaByTitle(title);
                break;
            case 4:
                printf("Digite o titulo do manga: ");
                scanf("%99[^\n]", title);
                // deleteMangaByTitle(title);
                break;
            case 5:
                printf("Digite o titulo do manga: ");
                scanf("%99[^\n]", title);
                // retrieveMangaByTitle(title);
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}