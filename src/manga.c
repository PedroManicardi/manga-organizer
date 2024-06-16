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
        char acquired_volumes_str[256]; // buffer para armazenar a string
        sprintf(acquired_volumes_str, ""); // inicializar buffer

        for (int j = 0; j < mangas[i].acquired_volumes; j++) {
            sprintf(acquired_volumes_str + strlen(acquired_volumes_str), "%d ", mangas[i].acquired_volumes_list[j]);
        }
        fprintf(file, "%s%s%s%s%s%s%s%s%s%s%s%s%d%s%d%s%d%s%d%s%d%s%s%s\n",
                mangas[i].ISBN, DELIMITER,
                mangas[i].title, DELIMITER,
                mangas[i].authors, DELIMITER,
                mangas[i].genre, DELIMITER,
                mangas[i].magazine, DELIMITER,
                mangas[i].publisher, DELIMITER,
                mangas[i].start_year, DELIMITER,
                mangas[i].end_year, DELIMITER,
                mangas[i].edition_year, DELIMITER,
                mangas[i].total_volumes, DELIMITER,
                mangas[i].acquired_volumes, DELIMITER,
                acquired_volumes_str, DELIMITER);
    }
    fclose(file);
}

void createPrimaryIndex(Manga mangas[], int count) {
    FILE *file = fopen(PRIMARY_INDEX_FILE, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de índice primário!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s%s%d\n", mangas[i].ISBN, DELIMITER, i);
    }
    fclose(file);
}

void createSecondaryIndex(Manga mangas[], int count) {
    FILE *file = fopen(SECONDARY_INDEX_FILE, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de índice secundário!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s%s%d\n", mangas[i].title, DELIMITER, i);
    }
    fclose(file);
}

int getTotalRecords(FILE *file) {
    int count = 0;
    char line[150];
    fseek(file, 0, SEEK_SET);  // Posiciona o ponteiro no início do arquivo

    while (fgets(line, sizeof(line), file)) {
        count++;
    }

    return count;
}

int getRecordPositionByTitle(const char *title) {
    FILE *file = fopen(SECONDARY_INDEX_FILE, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de índice secundário!\n");
        return -1;
    }

    int totalRecords = getTotalRecords(file);
    char line[150];
    int low = 0;
    int high = totalRecords - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        fseek(file, 0, SEEK_SET);  // Posiciona o ponteiro no início do arquivo

        // Avança até a linha correspondente ao índice mid
        for (int i = 0; i <= mid; i++) {
            fgets(line, sizeof(line), file);
        }

        // Extrai o título do registro atual
        char *token = strtok(line, DELIMITER);
        if (strcmp(token, title) == 0) {
            token = strtok(NULL, DELIMITER);
            fclose(file);
            return atoi(token);
        } else if (strcmp(token, title) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    fclose(file);
    return -1;
}

void retrieveMangaByTitle(const char *title) {
    int position = getRecordPositionByTitle(title);
    if (position == -1) {
        printf("Titulo nao encontrado...\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de dados!\n");
        return;
    }

    fseek(file, 0, SEEK_SET);
    int count;
    fscanf(file, "%d\n", &count);

    char line[500];
    for (int i = 0; i <= position; i++) {
        fgets(line, sizeof(line), file);
    }

    char *token = strtok(line, DELIMITER);
    printf("Manga encontrado com sucesso!\n");
    printf("ISBN: %s\n", token);
    token = strtok(NULL, DELIMITER);
    printf("Título: %s\n", token);
    token = strtok(NULL, DELIMITER);
    printf("Autores: %s\n", token);
    token = strtok(NULL, DELIMITER);
    printf("Gênero: %s\n", token);
    token = strtok(NULL, DELIMITER);
    printf("Revista: %s\n", token);
    token = strtok(NULL, DELIMITER);
    printf("Editora: %s\n", token);
    token = strtok(NULL, DELIMITER);
    printf("Ano de início: %d\n", atoi(token));
    token = strtok(NULL, DELIMITER);
    printf("Ano de término: %d\n", atoi(token));
    token = strtok(NULL, DELIMITER);
    printf("Ano da edição: %d\n", atoi(token));
    token = strtok(NULL, DELIMITER);
    printf("Total de volumes: %d\n", atoi(token));
    token = strtok(NULL, DELIMITER);
    printf("Volumes adquiridos: %d\n", atoi(token));


    char *volumesAdquiridos = strtok(NULL, DELIMITER);
    printf("Lista de volumes adquiridos: %s\n", volumesAdquiridos);

    fclose(file);
}


int loadMangasFromFile(Manga mangas[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Arquivo nao encontrado. Iniciando uma nova colecao.\n");
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