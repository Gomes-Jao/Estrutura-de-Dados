#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int info;
    struct node *next;
}node;

void show(node *list);
void insert_at_start(node **list, int value);
void insert_at_mid(node **list, int value);
void insert_at_end(node **list, int value);
int length(node *list);
int head(node *list);
node *tail(node *list);
bool is_in(node *list, int value);
void remove_at_start(node **list);
void remove_at_mid(node **list, int value);
void remove_at_end(node **list);
void remove_all(node **list, int value);
node *conc_at_third(node **list1, node **list2);
void conc(node **list1, node **list2);


void show(node *list)
{
    if(list)
    {
        if(!list->next) printf("%d\n", list->info);
        else
        {
            printf("%d ", list->info);
            show(list->next);
        }  
    }
}


void insert_at_start(node **list, int value)
{
    node *aux = malloc(sizeof(node));

    if(aux)
    {
        aux->info = value;
        aux->next = *list;
        *list = aux;
    }
    else printf("Erro ao alocar memória.\n");
}


void insert_at_mid(node **list, int value)
{
    node *aux1, *aux2, *new_element = malloc(sizeof(node));

    if(new_element)
    {
        new_element->info = value;
        new_element->next = NULL;

        if(!*list)
        {
            *list = new_element;
        }
        else if((*list)->info > new_element->info)
        {
            new_element->next = *list;
            *list = new_element;
        }
        else
        {
            aux1 = *list;
            aux2 = aux1->next;

            while(aux2 && aux2->info < new_element->info)
            {
                aux1 = aux1->next;
                aux2 = aux1->next;
            }

            new_element->next = aux1->next;
            aux1->next = new_element;
        }
    }
    else printf("Erro ao alocar memoria.\n");
}


void insert_at_end(node **list, int value)
{  
    node *aux, *new_element = malloc(sizeof(node));

    if(new_element)
    {
        new_element->info = value;
        new_element->next = NULL;

        if(!*list)
        {
            *list = new_element;
        }
        else
        {
            aux = *list;
            while(aux->next)
            {
                aux = aux->next;
            }
            aux->next = new_element;
        }
    }
    else printf("Erro ao alocar memoria.\n");
}


int length(node *list)
{
    if(list)
    {
        return 1 + length(list->next);
    }
    else return 0;
}


int head(node *list)
{
    if(list) return list->info;
    else
    {
        printf("list vazia.\n");
        return 0;
    }
}


node *tail(node *list)
{
    if(list) return list->next;
    else
    {
        printf("list vazia.\n");
        return list->next;
    }
}


bool is_in(node *list, int value)
{
    if(list->info == value) return true;
    else if(!(list->next)) return false;
    else is_in(list->next, value);
}


void remove_at_start(node **list)
{
    if(*list)
    {
        node *aux = *list;
        *list = (*list)->next;
        free(aux);
    }
    else printf("list vazia.\n");
}


void remove_at_mid(node **list, int value)
{
if(*list)
{
    node *aux1 = *list;
    node *aux2 = aux1->next;

    while(aux2->info != value)
    {
        aux1 = aux1->next;
        aux2 = aux1->next;
    }

    aux1->next = aux2->next;
    free(aux2);
}
else printf("list vazia.\n");
}


void remove_at_end(node **list)
{
    if(*list)
    {
        node *aux1, *aux2;

        aux1 = *list;
        aux2 = aux1->next;
        if(aux2)
        {
            while(aux2->next)
            {
                aux1 = aux1->next;
                aux2 = aux1->next;
            }
            aux1->next = aux2->next;
            free(aux2);
        }
        else
        {
            *list = NULL;
        }
    }
    else printf("list vazia.\n");
}


void remove_all(node **list, int value)
{
    if(*list)
    {
        node *aux1 = *list;
        node *aux2 = aux1->next;
        node *aux3;
        
        if(aux1->info == value)
        {
            *list = (*list)->next;
            free(aux1);
        }
        else
        {
            while(aux2)
            {
                if(aux2->info == value)
                {
                    aux1->next = aux2->next;
                    free(aux2);
                    aux2 = aux1->next;
                }
                else
                {
                    aux1 = aux1->next;
                    aux2 = aux1->next;
                }
            }
        }
    }
    else printf("lista vazia.\n");
}


node *conc_at_third(node **list1, node **list2)
{
    if(!*list1) return *list2;
    else if(!*list2) return *list1;
    else if(*list1 && *list2)
    {
        node *third_list = NULL;
        node *aux1, *aux2;
        int element;
        aux1 = *list1;
        aux2 = *list2;

        while(aux1 && aux2)
        {
            if(aux1->info < aux2->info)
            {
                element = head(aux1);
                aux1 = aux1->next;
            }
            else
            {
                element = head(aux2);
                aux2 = aux2->next;
            }
            insert_at_end(&third_list, element);
        }

        if(aux1) while(aux1)
        {
            element = head(aux1);
            insert_at_end(&third_list, element);
            aux1 = aux1->next;
        }
        else while(aux2)
        {
            element = head(aux2);
            insert_at_end(&third_list, element);
            aux2 = aux2->next;
        }
        
        return third_list;
    }
    else printf("Ambas as lists vazias.\n");
    return *list1;
}


void conc(node **list1, node **list2)
{
    if(*list1 && *list2)
    {
        node *aux1, *aux2, *aux3;
        int element;
        aux1 = *list1;
        aux2 = *list2;
        aux3 = aux1->next;

        while(aux1 && aux2)
        {
            if((aux2->info) <= *list1)
            {
                element = aux2->info;
                insert_at_mid(&(*list1), element);
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
    else if(*list2)
    {
        node *aux1, *aux2;
        aux1 = *list1;
        aux2 = *list2;
        while(aux2)
        {
            int element;
            element = aux2->info;
            insert_at_end(&aux1, element);
            aux2 = aux2->next;
        }
    }
    else printf("Ambas as listas vazias\n");
}

void create_list(node *var)
{
    var = malloc(sizeof(node));

    if(!var) printf("Erro ao alocar memória.\n");
    else var->next = NULL;
}