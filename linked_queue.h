#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

void show(node *queue);
void create_queue(node *var);
int length(node *queue);
int first(node *queue);
node *last(node *queue);
void insert(node **queue, int value);
void remove(node **queue);
void conc(node **queue1, node **queue2);

typedef struct{
    int info;
    struct node *next;
}node;


void show(node *queue)
{
    if(queue)
    {
        if(!queue->next) printf("%d\n", queue->info);
        else
        {
            printf("%d ", queue->info);
            show(queue->next);
        }  
    }
}


void create_queue(node *var)
{
    var = malloc(sizeof(node));

    if(!var) printf("Erro ao alocar memória.\n");
    else var->next = NULL;
}


int length(node *queue)
{
    if(queue)
    {
        return 1 + length(queue->next);
    }
    else return 0;
}


int first(node *queue)
{
    if(queue) return queue->info;
    else
    {
        printf("queue vazia.\n");
        return 0;
    }
}


node *last(node *queue)
{
    if(queue->next) return last(queue->next);
    else if (queue) return queue;
    else
    {
        printf("queue vazia.\n");
        return queue->next;
    }
}


void insert(node **queue, int value)
{  
    node *aux, *new_element = malloc(sizeof(node));

    if(new_element)
    {
        new_element->info = value;
        new_element->next = NULL;

        if(!*queue)
        {
            *queue = new_element;
        }
        else
        {
            aux = *queue;
            while(aux->next)
            {
                aux = aux->next;
            }
            aux->next = new_element;
        }
    }
    else printf("Erro ao alocar memoria.\n");
}


void remove(node **queue)
{
    if(*queue)
    {
        node *aux = *queue;
        *queue = (*queue)->next;
        free(aux);
    }
    else printf("queue vazia.\n");
}


void conc(node **queue1, node **queue2)
{
    if(*queue1 && *queue2)
    {
        node *aux1, *aux2, *aux3;
        int element;
        aux1 = *queue1;
        aux2 = *queue2;
        aux3 = aux1->next;

        while(aux1 && aux2)
        {
            if((aux2->info) <= *queue1)
            {
                element = aux2->info;
                insert_at_mid(&(*queue1), element);
                aux2 = aux2->next;
            }
            else if(aux2->info <= aux3->info)
            {
                element = aux2->info;
                insert_at_mid(&aux1, element);
                aux2 = aux2->next;
            }
            else
            {
                aux1 = aux1->next;
            }
        }
        if(aux2) while(aux2)
        {
            element = aux2->info;
            insert_at_end(&aux1, element);
            aux2 = aux2->next;
        }
    }
    else if(*queue2)
    {
        node *aux1, *aux2;
        aux1 = *queue1;
        aux2 = *queue2;
        while(aux2)
        {
            int element;
            element = aux2->info;
            insert_at_end(&aux1, element);
            aux2 = aux2->next;
        }
    }
    else printf("Ambas as queueas vazias\n");
}