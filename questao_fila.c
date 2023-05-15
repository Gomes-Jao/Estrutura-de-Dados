#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX 20

typedef struct fila {
    char nomes[MAX][50];
    int inicio, fim;
} Fila;

void inicializa_fila(Fila *f) {
    for(int i = 0; i < MAX; i++)
    {
        strcpy(f->nomes[i], "~");
    }
    f->inicio = 0;
    f->fim = 0;
}

void insere_fila(Fila *f, char *nome) {
    int i, j, k;
    int valid = 1;

    for(int k = 0; nome[k] != '\0'; k++)
    {
        if(!isalpha(nome[k]) && nome[k] != ' ') valid = 0;
    }

    if(valid == 0) printf("\nNome invalido. Tente novamente.\n\n");

    else if(f->fim == MAX)
    {
        printf("\nFila cheia.\n\n");
    }
    else
    {
        for (i = f->inicio; i < f->fim; i++) {
            if (strcmp(nome, f->nomes[i]) < 0) {
                break;
            }
        }
        for (j = f->fim; j > i; j--) {
            strcpy(f->nomes[j], f->nomes[j-1]);
        }
        strcpy(f->nomes[i], nome);
        f->fim++;
    }

}

void desenfileirar(Fila *f) {
    int i;

    if(f->fim == 0) printf("\nFila vazia.\n");
    else
    {
        for (i = 0; i < f->fim-1; i++) {
            strcpy(f->nomes[i], f->nomes[i+1]);
        }
        strcpy(f->nomes[i], "~");
        f->fim--;
    }
}

int contar_gaps(Fila *f, int inicio, int fim)
{
    int quantidade = 0;

    printf("Inicio: %d\nFim: %d", inicio, fim);

    for(int i = inicio; i <= fim; i++)
    {
        if(strcmp(f->nomes[i], "~") == 0) quantidade++;
    }
    printf("Quantidade: %d\n\n", quantidade);
    return quantidade;
}

void remove_fila(Fila *f, char *nome) {
    int i;
    int valid = f->fim == 0 ? 0 : 1;

    for(int k = 0; nome[k] != '\0'; k++)
    {
        if(!isalpha(nome[k]) && nome[k] != ' ') valid = 0;
    }

    for (i = f->inicio; i < f->fim; i++) {
        if(strcmp(nome, f->nomes[i]) == 0) {
            valid = 1;
            break;
        }
        else valid = 0;
    }

    if(valid == 0) printf("\nNome nao encontrado. Tente novamente.\n");
    else if (valid == 1)
    {
        if(contar_gaps(f, f->inicio, MAX) < 2 * contar_gaps(f, f->fim, MAX))
        {
            strcpy(f->nomes[i], "~");
        }
        else
        {
            for (; i < f->fim-1; i++) {
                strcpy(f->nomes[i], f->nomes[i+1]);
            }
            strcpy(f->nomes[i], "~");
            f->fim--;
        }
    }
        
        
}

void mostra_fila(Fila *f) {
    int i;
    for (i = 0; i < MAX; i++) {
            printf("%s \n", f->nomes[i]);
    }
    printf("\n");
}

bool clearStdin (void) {
    int var = true;
    char c;

    while (c = getchar())
    {
        if(c != '\n') var = false;
        else break;
    };

    return var;
}

int main() {
    Fila f;
    inicializa_fila(&f);

    char opcao;
    char nome[50];

    do {
        printf("\n1 - Inserir nome\n");
        printf("2 - Remover nome\n");
        printf("3 - Mostrar fila\n");
        printf("4 - Desenfileirar\n");
        printf("0 - Sair\n");
        printf("\nOpcao: ");
        scanf(" %c", &opcao);

        bool unique = clearStdin();

        if(!isdigit(opcao) || !unique)
        {
            opcao = 5;
        }
        else
        {
            opcao -= '0';
        }

        switch (opcao) {
            case 1:
                printf("\nDigite o nome: ");
                scanf(" %[^\n]", nome);
                insere_fila(&f, nome);
                break;
            case 2:
                printf("\nDigite o nome: ");
                scanf(" %[^\n]", nome);
                remove_fila(&f, nome);
                break;
            case 3:
                printf("\nFila:\n\n");
                mostra_fila(&f);
                break;
            case 4:
                desenfileirar(&f);
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida!\n\n");
        }
    } while (opcao != 0);

    return 0;
}
