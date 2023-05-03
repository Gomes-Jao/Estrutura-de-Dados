#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

void show(node *stack);
void pop(node **stack);
int top(node *stack);
void push(node **stack, int value);
int length(node *stack);
void create_stack(node *var);

typedef struct{
    int info;
    struct node *next;
}node;


void show(node *stack)
{
    if(stack)
    {
        if(!stack->next) printf("%d\n", stack->info);
        else
        {
            printf("%d ", stack->info);
            show(stack->next);
        }  
    }
}


void pop(node **stack)
{
    if(*stack)
    {
        node *aux = *stack;
        *stack = (*stack)->next;
        free(aux);
    }
    else printf("stack vazia.\n");
}


int top(node *stack)
{
    if(stack) return stack->info;
    else
    {
        printf("stack vazia.\n");
        return 0;
    }
}


void push(node **stack, int value)
{
    node *aux = malloc(sizeof(node));

    if(aux)
    {
        aux->info = value;
        aux->next = *stack;
        *stack = aux;
    }
    else printf("Erro ao alocar memória.\n");
}


int length(node *stack)
{
    if(stack)
    {
        return 1 + length(stack->next);
    }
    else return 0;
}


void create_stack(node *var)
{
    var = malloc(sizeof(node));

    if(!var) printf("Erro ao alocar memória.\n");
    else var->next = NULL;
}
