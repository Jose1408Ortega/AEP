#include <stdio.h>
#include <string.h>

const int TAMANHO_NOME = 50;
const int TAMANHO_SENHA = 50;
const char NOME_ARQUIVO[] = "usuarios.txt";

void incluirNovoUsuario() {
    FILE *arquivo = fopen(NOME_ARQUIVO, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char nome[TAMANHO_NOME], senha[TAMANHO_SENHA];
    printf("Digite o nome do usuario: ");
    scanf("%s", nome);
    printf("Digite a senha: ");
    scanf("%s", senha);

    fprintf(arquivo, "%s %s\n", nome, senha);
    fclose(arquivo);
    printf("Usuario adicionado com sucesso!\n");
}

void alterarUsuarioExistente() {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char nome[TAMANHO_NOME], senha[TAMANHO_SENHA], linha[2 * TAMANHO_NOME];
    char nomeBusca[TAMANHO_NOME];
    int encontrado = 0;

    printf("Digite o nome do usuario que deseja alterar: ");
    scanf("%s", nomeBusca);

    FILE *arquivoTemp = fopen("temp.txt", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo temporario!\n");
        fclose(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%s %s", nome, senha);
        if (strcmp(nome, nomeBusca) == 0) {
            encontrado = 1;
            printf("Digite o novo nome do usuario: ");
            scanf("%s", nome);
            printf("Digite a nova senha: ");
            scanf("%s", senha);
        }
        fprintf(arquivoTemp, "%s %s\n", nome, senha);
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove(NOME_ARQUIVO);
    rename("temp.txt", NOME_ARQUIVO);

    if (encontrado) {
        printf("Usuario alterado com sucesso!\n");
    } else {
        printf("Usuario nao encontrado!\n");
    }
}

void excluirUsuarioExistente() {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char nome[TAMANHO_NOME], senha[TAMANHO_SENHA], linha[2 * TAMANHO_NOME];
    char nomeBusca[TAMANHO_NOME];
    int encontrado = 0;

    printf("Digite o nome do usuario que deseja excluir: ");
    scanf("%s", nomeBusca);

    FILE *arquivoTemp = fopen("temp.txt", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo temporario!\n");
        fclose(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%s %s", nome, senha);
        if (strcmp(nome, nomeBusca) != 0) {
            fprintf(arquivoTemp, "%s %s\n", nome, senha);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove(NOME_ARQUIVO);
    rename("temp.txt", NOME_ARQUIVO);

    if (encontrado) {
        printf("Usuario excluido com sucesso!\n");
    } else {
        printf("Usuario nao encontrado!\n");
    }
}

void listarUsuariosCadastrados() {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char nome[TAMANHO_NOME], senha[TAMANHO_SENHA];

    printf("\nUsuarios cadastrados:\n");
    while (fscanf(arquivo, "%s %s", nome, senha) != EOF) {
        printf("%s\n", nome);
    }

    fclose(arquivo);
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Incluir Usuario\n");
        printf("2. Alterar Usuario\n");
        printf("3. Excluir Usuario\n");
        printf("4. Listar Usuarios\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirNovoUsuario();
                break;
            case 2:
                alterarUsuarioExistente();
                break;
            case 3:
                excluirUsuarioExistente();
                break;
            case 4:
                listarUsuariosCadastrados();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
