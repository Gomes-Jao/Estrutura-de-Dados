#include <stdio.h>
#include <stdlib.h>
#include "linked_stack_numeros.h"

void separar_pilha(node **pilha, node **pilhaInteira, node **pilhaFracionada)
{
    while((top(*pilha) != -2) && (top(*pilha) != -4))
    {
        push(pilhaFracionada, top(*pilha));
        pop(pilha);
    }

    while(length(*pilha))
    {
        if(top(*pilha) == -2 || top(*pilha) == -4)
        {
            pop(pilha);
        }

        push(pilhaInteira, top(*pilha));
        pop(pilha);
    }
}

void receber_valores(node **pilha)
{
    char c;
    int intC;

    while(scanf("%c", &c) && c != '\n')
    {
        intC = c - '0';
        push(pilha, intC);
    }
}

void filtrar(node **pilha, node **descartados, int max)
{
    node *aux = NULL;
    int min = 10;

    create_stack(aux);

    if(length(*pilha) == max)
    {
        while(length(*pilha) > 0)
        {
            pop(pilha);
        }

        push(pilha, 0);
        max = 0;
    }
    else if(length(*pilha) < max)
    {
        printf("Erro ao retirar a quantidade de numeros desejada.");
        exit(0);
    }

    while(length(*descartados) < max)
    {
        while(length(*pilha))
        {
            if(top(*pilha) < min) min = top(*pilha);
            push(&aux, top(*pilha));
            pop(pilha);
        }

        while(length(aux))
        {
            push(pilha, top(aux));
            pop(&aux);
        }

        while(length(*pilha))
        {
            if(top(*pilha) == min && (length(*descartados) < max))
            {
                push(descartados, top(*pilha));
                pop(pilha);
            }
            else
            {
                push(&aux, top(*pilha));
                pop(pilha);
            }
        }
        
        while(length(aux))
        {
            push(pilha, top(aux));
            pop(&aux);
        }
    }

    while(length(*descartados))
    {
        pop(descartados);
    }
}

void mostrar_pilha(node *stack)
{
    if(stack)
    {
        if(!stack->next) printf("%d\n", stack->info);
        else
        {
            if(stack->info == -2) printf(",");
            else printf("%d", stack->info);
            mostrar_pilha(stack->next);
        }  
    }
}

void devolver_para_a_pilha_original(node **pilhaOriginal, node **pilhaAtual)
{
    while(length(*pilhaAtual))
    {
        push(pilhaOriginal, top(*pilhaAtual));
        pop(pilhaAtual);
    }
}

int main()
{
    node *pilha = NULL;
    node *pilhaInteiros = NULL;
    node *pilhaFracionados = NULL;
    node *pilhaDescartados = NULL;
    node *pilhaSaida = NULL;
    int K, W;

    create_stack(pilha);
    create_stack(pilhaInteiros);
    create_stack(pilhaFracionados);
    create_stack(pilhaDescartados);
    create_stack(pilhaSaida);

    printf("\nDigite o numero: ");
    receber_valores(&pilha);

    printf("\nDigite quantos numeros serao tirados das partes inteira e fracionada: ");
    scanf("%d %d", &K, &W);

    separar_pilha(&pilha, &pilhaInteiros, &pilhaFracionados);
    
    filtrar(&pilhaInteiros, &pilhaDescartados, K);
    filtrar(&pilhaFracionados, &pilhaDescartados, W);

    devolver_para_a_pilha_original(&pilha, &pilhaInteiros);

    push(&pilha, -2);

    devolver_para_a_pilha_original(&pilha, &pilhaFracionados);

    while(length(pilha))
    {
        push(&pilhaSaida, top(pilha));
        pop(&pilha);
    }

    mostrar_pilha(pilhaSaida);

    return 0;
}