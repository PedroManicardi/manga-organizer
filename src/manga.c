#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "manga.h"

char *strtrim(char *str) {
    char *end;

    // Remove espaços em branco no início
    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == 0) { // String vazia
        return str;
    }

    // Remove espaços em branco no final
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    // Adiciona o terminador de string
    *(end + 1) = 0;

    return str;
}

// Funcao para adicionar um novo manga ao sistema
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

// Função para salvar os registros de mangas em um arquivo
void saveMangasToFile(Manga mangas[], int count) {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    fprintf(file, "%d\n", count); // Escreve a contagem de mangás no arquivo

    for (int i = 0; i < count; i++) {
        // Escreve cada campo do manga separado por DELIMITER
        fprintf(file, "%s|%s|%s|%s|%s|%s|%d|%d|%d|%d|%d|",
                mangas[i].ISBN, mangas[i].title, mangas[i].authors,
                mangas[i].genre, mangas[i].magazine, mangas[i].publisher,
                mangas[i].start_year, mangas[i].end_year, mangas[i].edition_year,
                mangas[i].total_volumes, mangas[i].acquired_volumes);

        // Escreve a lista de volumes adquiridos
        for (int j = 0; j < mangas[i].acquired_volumes; j++) {
            fprintf(file, "%d ", mangas[i].acquired_volumes_list[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Função para carregar os registros de mangas de um arquivo
int loadMangasFromFile(Manga mangas[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Arquivo não encontrado. Iniciando uma nova coleção.\n");
        return 0;
    }

    int count;
    fscanf(file, "%d\n", &count);
    for (int i = 0; i < count; i++) {
        // Lê cada campo do manga separado por DELIMITER
        fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d|%d|%d|",
               mangas[i].ISBN, mangas[i].title, mangas[i].authors,
               mangas[i].genre, mangas[i].magazine, mangas[i].publisher,
               &mangas[i].start_year, &mangas[i].end_year, &mangas[i].edition_year,
               &mangas[i].total_volumes, &mangas[i].acquired_volumes);

        // Lê a lista de volumes adquiridos
        for (int j = 0; j < mangas[i].acquired_volumes; j++) {
            fscanf(file, "%d ", &mangas[i].acquired_volumes_list[j]);
        }
        fscanf(file, "\n");
    }

    fclose(file);

    return count;
}
// Funcao para criar o indice primario (ISBN -> posicao no vetor)
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

// Funcao para criar o indice secundario (titulo -> posição no vetor)
void createSecondaryIndex(Manga mangas[], int count) {
    FILE *file = fopen(SECONDARY_INDEX_FILE, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de índice secundário!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s%s%s\n", mangas[i].title, DELIMITER, mangas[i].ISBN);
    }
    fclose(file);
}

// Funcao para obter o numero total de registros em um arquivo
int getTotalRecords(FILE *file) {
    int count = 0;
    char line[150];
    fseek(file, 0, SEEK_SET);  // Posiciona o ponteiro no inicio do arquivo

    while (fgets(line, sizeof(line), file)) {
        count++;
    }

    return count;
}

// Funcao para obter a posicao de um registro pelo titulo no indice secundario
int getRecordPositionByTitle(const char *title) {
    // Abrir o arquivo de índice secundário para leitura
    FILE *file = fopen(SECONDARY_INDEX_FILE, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de índice secundário!\n");
        return -1;
    }

    int totalRecords = getTotalRecords(file);
    char line[150];
    int low = 0;
    int high = totalRecords - 1;
    char isbn[20];
    int found = 0;

    // Busca binária no índice secundário
    while (low <= high) {
        int mid = low + (high - low) / 2;
        fseek(file, 0, SEEK_SET);

        // Avança até a linha correspondente ao índice mid
        for (int i = 0; i <= mid; i++) {
            fgets(line, sizeof(line), file);
        }

        // Extrai o título do registro atual
        char *token = strtok(line, DELIMITER);
        if (strcmp(token, title) == 0) {
            strcpy(isbn, strtok(NULL, DELIMITER));
            found = 1;
            break;
        } else if (strcmp(token, title) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    fclose(file);

    if (!found) {
        
        return -1;  // Título não encontrado
    }

    // Abrir o arquivo de índice primário para leitura
    file = fopen(PRIMARY_INDEX_FILE, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de índice primário!\n");
        return -1;
    }

    // Usa fseek diretamente para encontrar a posição do ISBN
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, DELIMITER);
        if (strcmp(strtrim(token), strtrim(isbn)) == 0) {
            fclose(file);
            return atoi(strtrim(strtok(NULL, DELIMITER)));
        }
    }

    fclose(file);

    return -1;  // ISBN não encontrado no índice primário
}

// Funcao para recuperar um manga pelo titulo
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

// Funcao para recuperar um manga pelo titulo
void retrieveAllMangaRecords() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de dados!\n");
        return;
    }

    fseek(file, 0, SEEK_SET);
    int count;
    fscanf(file, "%d\n", &count);

    char line[500];
    for (int i = 0; i < count; i++) {
        fgets(line, sizeof(line), file);

        char *token = strtok(line, DELIMITER);
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
        printf("\n----------------------\n");
    }

    fclose(file);
}

// Funcao para excluir um manga pelo titulo
void deleteMangaByTitle(const char *title) {
    int position = getRecordPositionByTitle(title);
    if (position == -1) {
        printf("Titulo nao encontrado...\n");
        return;
    }
    // Confirmar remocao
    char confirmation;
    printf("Tem certeza que deseja remover o manga \"%s\"? (s/n): ", title);
    scanf(" %c", &confirmation);
    getchar(); // Limpar o buffer do teclado

    if (confirmation != 's' && confirmation != 'S') {
        printf("Operacao de remocao cancelada.\n");
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

    Manga mangas[MAX];
    int new_count = 0;

    for (int i = 0; i < count; i++) {
        if (i != position) {
            char line[500];
            fgets(line, sizeof(line), file);

            char *token = strtok(line, DELIMITER);
            strcpy(mangas[new_count].ISBN, token);
            token = strtok(NULL, DELIMITER);
            strcpy(mangas[new_count].title, token);
            token = strtok(NULL, DELIMITER);
            strcpy(mangas[new_count].authors, token);
            token = strtok(NULL, DELIMITER);
            strcpy(mangas[new_count].genre, token);
            token = strtok(NULL, DELIMITER);
            strcpy(mangas[new_count].magazine, token);
            token = strtok(NULL, DELIMITER);
            strcpy(mangas[new_count].publisher, token);
            token = strtok(NULL, DELIMITER);
            mangas[new_count].start_year = atoi(token);
            token = strtok(NULL, DELIMITER);
            mangas[new_count].end_year = atoi(token);
            token = strtok(NULL, DELIMITER);
            mangas[new_count].edition_year = atoi(token);
            token = strtok(NULL, DELIMITER);
            mangas[new_count].total_volumes = atoi(token);
            token = strtok(NULL, DELIMITER);
            mangas[new_count].acquired_volumes = atoi(token);

            char *volumes_str = strtok(NULL, DELIMITER);
            char *vol_token = strtok(volumes_str, " ");
            mangas[new_count].acquired_volumes = 0;
            while (vol_token != NULL && mangas[new_count].acquired_volumes < MAX) {
                mangas[new_count].acquired_volumes_list[mangas[new_count].acquired_volumes++] = atoi(vol_token);
                vol_token = strtok(NULL, " ");
            }

            new_count++;
        } else {
            char line[500];
            fgets(line, sizeof(line), file); // Skip the line to be deleted
        }
    }

    fclose(file);

    saveMangasToFile(mangas, new_count);
    createPrimaryIndex(mangas, new_count);
    createSecondaryIndex(mangas, new_count);

    printf("Manga excluido com sucesso!\n");
}

void editMangaByTitle(const char *title, Manga mangas[], int count) {
    // Localizar o indice do manga pelo titulo
    int position = getRecordPositionByTitle(title);
    if (position == -1) {
        printf("Manga nao encontrado...\n");
        return;
    }

    do {
        //  Apresentar opcoes de edicao
        printf("Escolha o que deseja editar:\n");
        printf("1. ISBN\n");
        printf("2. Titulo\n");
        printf("3. Autores\n");
        printf("4. Genero\n");
        printf("5. Revista\n");
        printf("6. Editora\n");
        printf("7. Ano de inicio\n");
        printf("8. Ano de termino\n");
        printf("9. Ano da edicao\n");
        printf("10. Total de volumes\n");
        printf("11. Quantidade de volumes adquiridos\n");
        printf("12. Numeros dos volumes adquiridos\n");
        printf("13. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        
        int choice;
        scanf("%d", &choice);
        getchar(); // Limpar o buffer do teclado

        // Ler os novos dados e atualizar o campo correspondente
        switch (choice) {
            case 1:
                printf("Novo ISBN: ");
                fgets(mangas[position].ISBN, sizeof(mangas[position].ISBN), stdin);
                mangas[position].ISBN[strcspn(mangas[position].ISBN, "\n")] = '\0';
                break;
            case 2:
                printf("Novo titulo: ");
                fgets(mangas[position].title, sizeof(mangas[position].title), stdin);
                mangas[position].title[strcspn(mangas[position].title, "\n")] = '\0';
                break;
            case 3:
                printf("Novos autores: ");
                fgets(mangas[position].authors, sizeof(mangas[position].authors), stdin);
                mangas[position].authors[strcspn(mangas[position].authors, "\n")] = '\0';
                break;
            case 4:
                printf("Novo genero: ");
                fgets(mangas[position].genre, sizeof(mangas[position].genre), stdin);
                mangas[position].genre[strcspn(mangas[position].genre, "\n")] = '\0';
                break;
            case 5:
                printf("Nova revista: ");
                fgets(mangas[position].magazine, sizeof(mangas[position].magazine), stdin);
                mangas[position].magazine[strcspn(mangas[position].magazine, "\n")] = '\0';
                break;
            case 6:
                printf("Nova editora: ");
                fgets(mangas[position].publisher, sizeof(mangas[position].publisher), stdin);
                mangas[position].publisher[strcspn(mangas[position].publisher, "\n")] = '\0';
                break;
            case 7:
                printf("Novo ano de inicio: ");
                scanf("%d", &mangas[position].start_year);
                getchar(); // Limpar o buffer do teclado
                break;
            case 8:
                printf("Novo ano de termino: ");
                scanf("%d", &mangas[position].end_year);
                getchar(); // Limpar o buffer do teclado
                break;
            case 9:
                printf("Novo ano da edicao: ");
                scanf("%d", &mangas[position].edition_year);
                getchar(); // Limpar o buffer do teclado
                break;
            case 10:
                printf("Novo total de volumes: ");
                scanf("%d", &mangas[position].total_volumes);
                getchar(); // Limpar o buffer do teclado
                break;
            case 11:
                printf("Nova quantidade de volumes adquiridos: ");
                scanf("%d", &mangas[position].acquired_volumes);
                getchar(); // Limpar o buffer do teclado
                break;
            case 12:
                printf("Novos numeros dos volumes adquiridos (separados por espaco): ");
                for (int i = 0; i < mangas[position].acquired_volumes; i++) {
                    scanf("%d", &mangas[position].acquired_volumes_list[i]);
                }
                getchar(); // Limpar o buffer do teclado
                break;
            case 13:
                printf("Voltando ao menu principal...\n");
                return;
            default:
                printf("Opcao invalida!\n");
                break;
        }

        // Salvar as alteracoes no arquivo
        saveMangasToFile(mangas, count);

        // Reconstruir os indices
        createPrimaryIndex(mangas, count);
        createSecondaryIndex(mangas, count);

        // Perguntar se deseja editar mais algo
        printf("\nDeseja continuar editando este manga? (s/n): ");
        char answer;
        scanf(" %c", &answer);
        getchar(); // Limpar o buffer do teclado
        if (answer != 's' && answer != 'S') {
            printf("Voltando ao menu principal...\n");
            return;
        }

    } while (1);

}

