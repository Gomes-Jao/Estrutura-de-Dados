#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "linked_stack_numeros.h"

// Correções:
//  - Tratamento de entrada.
//  - Ordenação da pilha para mostrar o número ordenado da maior forma possível.

void sort_stack(node **stack, int retirar)
{
    node *auxStack = NULL;
    node *stackFinal = NULL;
    int min;

    create_stack(auxStack);
    create_stack(stackFinal);

    while(length((*stack)))
    {
        min = 10;

        while(length((*stack)))
        {
            if(top((*stack)) < min)
            {
                min = top((*stack));
            }
            push(&auxStack, top((*stack)));
            pop(stack);
        }

        while(length(auxStack))
        {
            if(top(auxStack) != min)
            {
                push(stack, top(auxStack));
                pop(&auxStack);
            }
            else if(retirar > 0)
            {
                pop(&auxStack);
                retirar--;
            }
            else
            {
                push(&stackFinal, top(auxStack));
                pop(&auxStack);
            }
        }
    }

    *stack = stackFinal;
    free(&stackFinal);
}

void receber_valores(node **stackTotal)
{
    char c;
    int valid = 1;
    int intC;
    int isReal = 0;

    while(scanf("%c", &c) && c != '\n')
    {
        intC = c - '0';

        if((!length(*stackTotal)) && (intC == -2 || intC == -4))
        {
            valid = 0;
        }
        if((intC < 0 && intC != -2 && intC != -4) || (intC > 9))
        {
            valid = 0;
        }
        else
        {
            if(intC == -2 || intC == -4) isReal++;
            push(stackTotal, intC);
        }
    }

    if(valid == 0 || isReal > 1)
    {
        printf("Valor incorreto. Digite novamente: ");
        
        while(length(*stackTotal))
        {
            pop(stackTotal);
        }
        receber_valores(stackTotal);
    }
}

int quantidade_a_retirar(int max)
{
    int valor = 0;
    int intC;
    int valid = 1;
    char c;

    while(scanf("%c", &c) && c != '\n')
    {
        intC = c - '0';
        if(isdigit(c) == 0 || intC > max || intC < 0)
        {
            valid = 0;
        }
        else
        {
            valor *= 10;
            valor += intC;
        }
    }

    if(valid == 0)
    {
        printf("Digite novamente: ");
        valor = quantidade_a_retirar(max);
    }

    return valor;
}

void quebrar_pilha(node **stack, node **stackInteira, node **stackFracionaria)
{
    node *stackTemp = NULL;
    int isNatural = 1;

    create_stack(stackTemp);

    while(length(*stack) && (top(*stack) != -2) && (top(*stack) != -4))
    {
        push(&stackTemp, top(*stack));
        pop(stack);
    }

    if((top(*stack) == -2) || (top(*stack) == -4))
    {
        while(length(stackTemp))
        {
            push(stackFracionaria, top(stackTemp));
            pop(&stackTemp);
        }
    }
    else
    {
        while(length(stackTemp))
        {
            push(stackInteira, top(stackTemp));
            pop(&stackTemp);
        }
    }

    while(length(*stack))
    {
        if(top(*stack) == -2 || top(*stack) == -4)
        {
            pop(stack);
            isNatural = 0;
        }

        push(&stackTemp, top(*stack));
        pop(stack);
    }

    if(!isNatural)
    {
        while(length(stackTemp))
        {
            push(stackInteira, top(stackTemp));
            pop(&stackTemp);
        }
    }
}

void concatenar(node **stack, node **stackInteira, node **stackFracionaria)
{
    node *stackTemp = NULL;

    while(length(*stackFracionaria))
    {
        push(&stackTemp, top(*stackFracionaria));
        pop(stackFracionaria);
    }

    while(length(stackTemp))
    {
        push(stack, top(stackTemp));
        pop(&stackTemp);
    }

    if(length(*stack))
    {
        push(stack, -2);
    }
    if(!length(*stackInteira)) push(stack, 0);
    else
    {
        while(length(*stackInteira))
        {
            push(&stackTemp, top(*stackInteira));
            pop(stackInteira);
        }

        while(length(stackTemp))
        {
            push(stack, top(stackTemp));
            pop(&stackTemp);
        }
    }
}

void show_stack(node *stack)
{
    while(length(stack))
    {
        if(stack->info == -2) printf(",");
        else printf("%d", stack->info);
        pop(&stack);
    }
}

int main()
{
    node *stackTotal = NULL;
    node *stackInteira = NULL;
    node *stackFracionaria = NULL;
    int retirar_inteiros, retirar_fracionarios;

    // Inicializa a pilha
    create_stack(stackTotal);

    // Recebe o valor a ser organizado
    printf("\nDigite o numero a ser organizado: ");
    receber_valores(&stackTotal);

    // Quebre a pilha stackTotal em duas pilhas. Uma contendo os numeros inteiros e outra a parte fracionaria.
    quebrar_pilha(&stackTotal, &stackInteira, &stackFracionaria);

    // Pergunta quantos numeros serao tirados da parte inteira.
    if(length(stackInteira))
    {
        printf("Digite quantos digitos deverao ser tirados da parte inteira: ");
        retirar_inteiros = quantidade_a_retirar(length(stackInteira));
    }
    
    // Pergunta quantos numeros serao tirados da parte fracionaria.
    if(length(stackFracionaria))
    {
        printf("Digite quantos digitos deverao ser tirados da parte fracionaria: ");
        retirar_fracionarios = quantidade_a_retirar(length(stackFracionaria));
    }

    // Ordena as pilhas separadamente.
    sort_stack(&stackInteira, retirar_inteiros);
    sort_stack(&stackFracionaria, retirar_fracionarios);

    // Concatena a parte fracionada e inteira.
    concatenar(&stackTotal, &stackInteira, &stackFracionaria);

    // Printa a pilha.
    printf("Pilha ordenada: ");
    show_stack(stackTotal);

    return 0;
}
