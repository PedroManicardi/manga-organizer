#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manga.h"

void addManga(Manga mangas[], int *count) {
    if (*count >= MAX) {
        printf("Limite de mangas atingido!\n");
        return;
    }

    Manga m;

    printf("Digite o ISBN: ");
    fgets(m.ISBN, sizeof(m.ISBN), stdin);
    m.ISBN[strcspn(m.ISBN, "\n")] = '\0';  // Remover o newline

    printf("Digite o título: ");
    fgets(m.title, sizeof(m.title), stdin);
    m.title[strcspn(m.title, "\n")] = '\0';

    printf("Digite os autores: ");
    fgets(m.authors, sizeof(m.authors), stdin);
    m.authors[strcspn(m.authors, "\n")] = '\0';

    printf("Digite o gênero: ");
    fgets(m.genre, sizeof(m.genre), stdin);
    m.genre[strcspn(m.genre, "\n")] = '\0';

    printf("Digite a revista: ");
    fgets(m.magazine, sizeof(m.magazine), stdin);
    m.magazine[strcspn(m.magazine, "\n")] = '\0';

    printf("Digite a editora: ");
    fgets(m.publisher, sizeof(m.publisher), stdin);
    m.publisher[strcspn(m.publisher, "\n")] = '\0';

    printf("Digite o ano de início: ");
    scanf("%d", &m.start_year);
    getchar();  // Limpar o buffer do teclado

    printf("Digite o ano de fim: ");
    scanf("%d", &m.end_year);
    getchar();  // Limpar o buffer do teclado

    printf("Digite o ano da edição: ");
    scanf("%d", &m.edition_year);
    getchar();  // Limpar o buffer do teclado

    printf("Digite a quantidade total de volumes: ");
    scanf("%d", &m.total_volumes);
    getchar();  // Limpar o buffer do teclado

    printf("Digite a quantidade de volumes adquiridos: ");
    scanf("%d", &m.acquired_volumes);
    getchar();  // Limpar o buffer do teclado

    printf("Digite os números dos volumes adquiridos (separados por espaço): ");
    for (int i = 0; i < m.acquired_volumes; i++) {
        scanf("%d", &m.acquired_volumes_list[i]);
    }
    getchar();  // Limpar o buffer do teclado

    mangas[*count] = m;
    (*count)++;
}

void listMangas(Manga mangas[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Manga %d\n", i + 1);
        printf("ISBN: %s\n", mangas[i].ISBN);
        printf("Título: %s\n", mangas[i].title);
        printf("Autores: %s\n", mangas[i].authors);
        printf("Gênero: %s\n", mangas[i].genre);
        printf("Revista: %s\n", mangas[i].magazine);
        printf("Editora: %s\n", mangas[i].publisher);
        printf("Ano de Início: %d\n", mangas[i].start_year);
        printf("Ano de Fim: %d\n", mangas[i].end_year);
        printf("Ano da Edição: %d\n", mangas[i].edition_year);
        printf("Quantidade Total de Volumes: %d\n", mangas[i].total_volumes);
        printf("Quantidade de Volumes Adquiridos: %d\n", mangas[i].acquired_volumes);
        printf("Volumes Adquiridos: ");
        for (int j = 0; j < mangas[i].acquired_volumes; j++) {
            printf("%d ", mangas[i].acquired_volumes_list[j]);
        }
        printf("\n----------------------\n");
    }
}

void saveMangasToFile(Manga mangas[], int count) {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n%d\n%d\n%d\n",
                mangas[i].ISBN,
                mangas[i].title,
                mangas[i].authors,
                mangas[i].genre,
                mangas[i].magazine,
                mangas[i].publisher,
                mangas[i].start_year,
                mangas[i].end_year,
                mangas[i].edition_year,
                mangas[i].total_volumes,
                mangas[i].acquired_volumes);
        for (int j = 0; j < mangas[i].acquired_volumes; j++) {
            fprintf(file, "%d ", mangas[i].acquired_volumes_list[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int loadMangasFromFile(Manga mangas[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Arquivo não encontrado. Iniciando uma nova coleção.\n");
        return 0;
    }

    int count;
    fscanf(file, "%d\n", &count);
    for (int i = 0; i < count; i++) {
        fscanf(file, "%s\n", mangas[i].ISBN);
        fscanf(file, "%[^\n]\n", mangas[i].title);
        fscanf(file, "%[^\n]\n", mangas[i].authors);
        fscanf(file, "%[^\n]\n", mangas[i].genre);
        fscanf(file, "%[^\n]\n", mangas[i].magazine);
        fscanf(file, "%[^\n]\n", mangas[i].publisher);
        fscanf(file, "%d\n", &mangas[i].start_year);
        fscanf(file, "%d\n", &mangas[i].end_year);
        fscanf(file, "%d\n", &mangas[i].edition_year);
        fscanf(file, "%d\n", &mangas[i].total_volumes);
        fscanf(file, "%d\n", &mangas[i].acquired_volumes);
        for (int j = 0; j < mangas[i].acquired_volumes; j++) {
            fscanf(file, "%d", &mangas[i].acquired_volumes_list[j]);
        }
        fscanf(file, "\n");
    }
    fclose(file);

    return count;
}
