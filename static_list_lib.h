#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct
{
    //Estrutura direcionada a definir o que é interpretado
    //como número ou não. Possuindo duas estruturas internas:
    //VALUE referente ao valor (no momento, inteiro) da variável
    //e ISNUM, cujo afirma ou nega ser um número. Ambas devem ser
    //atualizadas para a definição de um número nesta biblioteca.
    int value;
    bool isnum;
}number;


int length(number *list);
void head(number *list, int *adress);
void tail(number *list, number *newList);
void p_is_in(number *list, int value);
int is_in(number *list, int value);
int position(number *list, int value);
void insert(number *list, int listSize, int value, int position);
void erase(number *list, int value, int quantity);
void sort(number *list);
void invert(number *list);
void conc(number *firstList, number *secondList, number *newList, int newListSize, int ordenate);
void help(char *func);


int length(number *list)
{
    //Parâmetros
    //{
    //  list: um array do tipo NUMBER, com tamanho N elementos
    //        mais um índice ao final, com a estrutura interna
    //        ISNUM = FALSE.       
    //}
    // Retorna um inteiro LEN de acordo com a quantidade de
    //Elementos com a estrutura interna ISNUM = TRUE.
    int len = 0;
    int index = 0;

    while(list[index].isnum)
    {
        index++;
        len++;
    }

    return len;
}


void head(number *list, int *adress)
{
    //Parâmetros
    //{
    //  list: um array do tipo NUMBER, com tamanho N elementos
    //        mais um índice ao final, com a estrutura interna
    //        ISNUM = FALSE.
    //
    //  adress: PONTEIRO de endereço de um INTEIRO para guardar
    //          o valor da cabeça da lista.     
    //}
    // Atribui o valor da cabeça da lista LIST, se houver,
    //à variável ADRESS.
    if(!list[0].isnum)
    {
        printf("Lista sem cabeca.\n");
    }
    else
    {
        *adress = list[0].value;
    }
}


void tail(number *list, number *newList)
{
    //Parâmetros
    //{
    //  list: um array do tipo NUMBER, com tamanho N elementos
    //        mais um índice ao final, com a estrutura interna
    //        ISNUM = FALSE.
    //
    //  newList: um array do tipo NUMBER com tamanho suficiente
    //           para alocar a cauda da lista LIST.          
    //}
    // Verifica se a lista LIST possui cauda. Em seguida,
    //verifica se a lista NEWLIST possui tamanho suficiente para
    //alocar a cauda.
    // Logo, para cada elemento em LIST, além do índice 0,
    //acrescenta-o em NEWLIST.
    if(!list[1].isnum)
    {
        printf("Lista sem cauda.\n");
    }
    else if(length(newList) < length(list) - 1)
    {
        printf("Utilize uma lista maior para ser a cauda.\n");
    }
    else
    {
        int index = 0;
        while(list[index].isnum)
        {
            newList[index] = list[index + 1];
            index++;
        }
        newList[index].isnum = false;
    }
}


void p_is_in(number *list, int value)
{
    //Parâmetros
    //{
    //  list: um array do tipo NUMBER, com tamanho N elementos
    //        mais um índice ao final, com a estrutura interna
    //        ISNUM = FALSE.
    //
    //  value: o INTEIRO que será procurado dentro da lista.
    //}
    // Procura pelo inteiro VALUE dentro da lista LIST.
    //Ao encontrar, mostra na tela a mensagem SIM.
    //Caso o valor não esteja na lista, mostra a mensagem NAO.
    int isIn = 0;
    for(int index = 0; list[index].isnum; index++)
    {
        if(list[index].value == value) isIn = 1;
    }
    printf("%s", isIn == 1 ? "Sim\n" : "Nao\n");
}


int is_in(number *list, int value)
{
    //Parâmetros
    //{
    //  list: um array do tipo NUMBER, com tamanho N elementos
    //        mais um índice ao final, com a estrutura interna
    //        ISNUM = FALSE.
    //
    //  value: o INTEIRO que será procurado detro da lista.
    //}
    //
    // Procura pelo inteiro VALUE dentro da lista LIST.
    //Ao encontrar, retorna 1.
    //Caso o valor não esteja na lista, retorna 0.
    int isIn = 0;
    for(int index = 0; list[index].isnum; index++)
    {
        if(list[index].value == value) return 1;
    }
    return 0;
}


int position(number *list, int value)
{
    //Parâmetros
    //{
    //  list: um array do tipo NUMBER, com tamanho N elementos
    //        mais um índice ao final, com a estrutura interna
    //        ISNUM = FALSE.
    //
    //  value: o INTEIRO que será procurado dentro da lista.
    //}
    //
    // Procura pelo inteiro VALUE dentro da lista LIST.
    //Ao encontrar, retorna o índice do valor na lista.
    //OBS: Não verifica se o valor está na lista.
    int index = 0;
    while(list[index].value != value && list[index].isnum)
    {
        index++;
    }
    return index;
}


void insert(number *list, int listSize, int value, int position)
{
    //Parâmetros
    //{
    //  list: um array do tipo NUMBER, com tamanho N elementos
    //        mais um índice ao final, com a estrutura interna
    //        ISNUM = FALSE.
    //
    //  listSize: o tamanho da lista na qual será inserido o
    //            inteiro VALUE.
    //
    //  value: o INTEIRO que será colocado dentro da lista.
    //
    //  position: o índice no qual será inserido o inteiro.
    //            Ao inserir -1, o item será adicionado ao
    //            final.
    //}
    //
    // Verifica se a lista já está cheia, caso não, procura pelo
    //índice indicado em POSITION dentro da lista LIST, e
    //substitui pelo valor VALUE. Em seguida, substitui os próximos
    //valores pelos seus anteriores.
    int lastIndex = 0;

    while(list[lastIndex].isnum)
    {
        lastIndex++;
    }

    printf("%d\n", lastIndex);

    if((lastIndex + 1) == listSize) printf("Lista cheia.\n");
    else
    {
        if(position == -1)
        {
            list[lastIndex].isnum = true;
            list[lastIndex].value = value;
            list[lastIndex + 1].isnum = false;
        }
        else
        {
            for(int index = position; index <= lastIndex; index++)
            {
                int aux = list[index].value;
                list[index].value = value;
                list[index].isnum = true;
                value = aux;
            }
            list[lastIndex + 1].isnum = false;
        }
    }
}


void erase(number *list, int value, int quantity)
{
    //Parâmetros
    //{
    //  list: um array do tipo NUMBER, com tamanho N elementos
    //        mais um índice ao final, com a estrutura interna
    //        ISNUM = FALSE.
    //
    //  value: o INTEIRO que será retirado da lista.
    //
    //  quantity: a quantidade de vezes que deseja retirar o
    //            inteiro VALUE da lista LIST.
    //}
    //
    // Verifica se há algum inteiro VALUE dentro da lista LIST
    //e, caso haja, procura pelo índice do valor desejado e
    //substitui, a partir deste índice, até o final, o valor
    //ali encontrado, pelo seu seguinte.
    // Repete esse processo até retirar todas as repetições
    //desejadas, na ordem que aparece. Caso haja menos elementos
    //que o indicado em QUANTITY, será mostrado na tela. 
    if(!is_in(list, value)) printf("O valor %d nao esta na lista.\n", value);
    else
    {
        do
        {
            if(!is_in(list, value))
            {
                printf("O valor %d aparece menos vezes que a quantidade indicada.\n", value);
                quantity = 0;
            }
            else
            {
                int valuePosition = position(list, value);

                while(list[valuePosition].isnum)
                {
                    list[valuePosition] = list[valuePosition + 1];
                    valuePosition++;
                }
                quantity--;
            }
        } while (quantity > 0);   
    }  
}


void sort(number *list)
{
    //Parâmetros
    //{
    //  list: um array do tipo NUMBER, com tamanho N elementos
    //        mais um índice ao final, com a estrutura interna
    //        ISNUM = FALSE.
    //}
    //
    // Utiliza o algorítmo de bubble sort para organizar em ordem
    //crescente a lista LIST.    
    for(int indexI = length(list); indexI > 0; indexI--)
    {
        for(int indexJ = 0; indexJ + 1 < indexI; indexJ++)
        {
            if(list[indexJ].value > list[indexJ + 1].value)
            {
                number aux = list[indexJ];
                list[indexJ] = list[indexJ + 1];
                list[indexJ + 1] = aux;
            }
        }
    }
}


void invert(number *list)
{
    //Parâmetros
    //{
    //  list: um array do tipo NUMBER, com tamanho N elementos
    //        mais um índice ao final, com a estrutura interna
    //        ISNUM = FALSE.
    //}
    //
    // Utiliza o algorítmo de bubble sort sem condições para
    //inverter o índice dos elementos na lista.
    for(int indexI = length(list); indexI > 0; indexI--)
    {
        for(int indexJ = 0; indexJ + 1 < indexI; indexJ++)
        {
                number aux = list[indexJ];
                list[indexJ] = list[indexJ + 1];
                list[indexJ + 1] = aux;
        }
    }
}


void conc(number *firstList, number *secondList, number *newList, int newListSize, int ordenate)
{
    //Parâmetros
    //{
    //  firstList: um array do tipo NUMBER, com tamanho N elementos
    //             mais um índice ao final, com a estrutura interna
    //             ISNUM = FALSE.
    //
    //  secondList: outro array do tipo NUMBER, com tamanho N elementos
    //              mais um índice ao final, com a estrutura interna
    //              ISNUM = FALSE.
    //
    //  newList: um terceiro array do tipo NUMBER, com tamanho maior ou
    //           igual à soma da quantidade de elementos presentes nas
    //           listas anteriores mais um índice ao final, com a
    //           estrutura interna ISNUM = FALSE.
    //
    //  newListSize: tamanho da nova lista. Utilizado para verificar se
    //               possui tamanho suficiente para receber os valores.
    //
    //  ordenate: fator de ordenação, caso queira ordenar a nova lista
    //            criada. Recebe 1 caso queira em ordem crescente e -1
    //            caso seja em ordem decrescente.
    //}
    //
    // Verifica se o tamanho da NEWLISTSIZE é suficiente. Caso seja,
    //transfere todos os valores da FIRSTLIST para a NEWLIST. Ao
    //terminar, começa a transferir os valores da SECONDLIST para
    //a NEWLIST, a partir do último índice, verificando se os valores
    //já estão inseridos. Após adicionar todos os valores, de acordo
    //com o fator ORDENATE, organiza ou não a lista.
    if(newListSize - 1 < length(firstList) + length(secondList))
    {
        printf("Escolha uma lista maior para guardar os valores.\n");
    }
    else
    {
        int indexConc = 0;

        for(int index = 0; firstList[index].isnum; index++)
        {
            newList[indexConc] = firstList[index];
            indexConc++;
        }

        for(int index = 0; secondList[index].isnum; index++)
        {
            if(is_in(newList, secondList[index].value)) continue;
            else
            {
                newList[indexConc] = secondList[index];
                indexConc++;
            }
        }
        newList[indexConc].isnum = false;

        if(ordenate == 1)
        {
            sort(newList);
        }
        else if(ordenate == -1)
        {
            sort(newList);
            invert(newList);
        }
    }
}


void help(char *func)
{
    //Parâmetros
    //{
    //  func: nome da função a ser analisada.
    //}
    //
    // Mostra na tela os parâmetros e funcionamento
    //da função utiluzada como parâmetro.
    if(func == "length")
    {
        printf("===========================================================\n");
        printf("Formato: length(list)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  list: um array do tipo NUMBER, com tamanho N elementos\n");
        printf("        mais um indice ao final, com a estrutura interna\n");
        printf("        ISNUM = FALSE.\n");
        printf("}\n\n");
        printf(" Retorna um inteiro LEN de acordo com a quantidade\n");
        printf("de elementos com a estrutura interna ISNUM = TRUE.\n");
        printf("===========================================================\n");
    }
    else if(func == "head")
    {
        printf("===========================================================\n");
        printf("Formato: head(list, adress)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  list: um array do tipo NUMBER, com tamanho N elementos\n");
        printf("        mais um indice ao final, com a estrutura interna\n");
        printf("        ISNUM = FALSE.\n\n");
        printf("  adress: PONTEIRO de endereco de um INTEIRO para guardar\n");
        printf("          o valor da cabeca da lista.\n");
        printf("}\n\n");
        printf(" Atribui o valor da cabeca da lista LIST, se houver,\n");
        printf("a variavel ADRESS.\n");
        printf("===========================================================\n");
    }
    else if(func == "tail")
    {
        printf("===========================================================\n");
        printf("Formato: tail(list, newList)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  list: um array do tipo NUMBER, com tamanho N elementos\n");
        printf("        mais um indice ao final, com a estrutura interna\n");
        printf("        ISNUM = FALSE.\n\n");
        printf("  newList: um array do tipo NUMBER com tamanho suficiente\n");
        printf("           para alocar a cauda da lista LIST.\n");
        printf("}\n\n");
        printf(" Verifica se a lista LIST possui cauda. Em seguida,\n");
        printf("verifica se a lista NEWLIST possui tamanho suficiente\n");
        printf("para alocar a cauda.\n");
        printf(" Logo, para cada elemento em LIST, alem do indice 0,\n");
        printf("acrescenta-o em NEWLIST.\n");
        printf("===========================================================\n");
    }
    else if(func == "p_is_in")
    {
        printf("===========================================================\n");
        printf("Formato: p_is_in(list, value)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  list: um array do tipo NUMBER, com tamanho N elementos\n");
        printf("        mais um indice ao final, com a estrutura interna\n");
        printf("        ISNUM = FALSE.\n\n");
        printf("  value: o INTEIRO que sera procurado dentro da lista.\n");
        printf("}\n\n");
        printf(" Procura pelo inteiro VALUE dentro da lista LIST.\n");
        printf("Ao encontrar, mostra na tela a mensagem SIM.\n");
        printf("Caso o valor nao esteja na lista, mostra a mensagem NAO.\n");
        printf("===========================================================\n");
    }
    else if(func == "is_in")
    {
        printf("===========================================================\n");
        printf("Formato: is_in(list, value)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  list: um array do tipo NUMBER, com tamanho N elementos\n");
        printf("        mais um indice ao final, com a estrutura interna\n");
        printf("        ISNUM = FALSE.\n\n");
        printf("  value: o INTEIRO que sera procurado dentro da lista.\n");
        printf("}\n\n");
        printf(" Procura pelo inteiro VALUE dentro da lista LIST.\n");
        printf("Ao encontrar, retorna 1.\n");
        printf("Caso o valor nao esteja na lista, retorna 0..\n");
        printf("===========================================================\n");
    }
    else if(func == "position")
    {
        printf("===========================================================\n");
        printf("Formato: position(list, value)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  list: um array do tipo NUMBER, com tamanho N elementos\n");
        printf("        mais um indice ao final, com a estrutura interna\n");
        printf("        ISNUM = FALSE.\n\n");
        printf("  value: o INTEIRO que sera procurado dentro da lista.\n");
        printf("}\n\n");
        printf(" Procura pelo inteiro VALUE dentro da lista LIST.\n");
        printf("Ao encontrar, retorna o indice do valor na lista.\n");
        printf("OBS: Nao verifica se o valor esta na lista.\n");
        printf("===========================================================\n");
    }
    else if(func == "insert")
    {
        printf("===========================================================\n");
        printf("Formato: insert(list, listSize, value, position)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  list: um array do tipo NUMBER, com tamanho N elementos\n");
        printf("        mais um indice ao final, com a estrutura interna\n");
        printf("        ISNUM = FALSE.\n\n");
        printf("  listSize: o tamanho da lista na qual sera inserido o\n");
        printf("            inteiro VALUE.\n\n");
        printf("  value: o INTEIRO que sera colocado dentro da lista.\n\n");
        printf("  position: o indice no qual sera inserido o inteiro.\n");
        printf("            Ao inserir -1, o item sera adicionado ao\n");
        printf("            final.\n");
        printf("}\n\n");
        printf(" Verifica se a lista ja esta cheia, caso nao, procura pelo\n");
        printf("indice indicado em POSITION dentro da lista LIST, e\n");
        printf("substitui pelo valor VALUE. Em seguida, substitui os\n");
        printf("proximos valores pelos seus anteriores.\n");
        printf("===========================================================\n");
    }
    else if(func == "erase")
    {
        printf("===========================================================\n");
        printf("Formato: erase(list, value, quantity)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  list: um array do tipo NUMBER, com tamanho N elementos\n");
        printf("        mais um indice ao final, com a estrutura interna\n");
        printf("        ISNUM = FALSE.\n\n");
        printf("  value: o INTEIRO que sera retirado da lista.\n\n");
        printf("  quantity: a quantidade de vezes que deseja retirar o\n");
        printf("            inteiro VALUE da lista LIST.\n");
        printf("}\n\n");
        printf(" Verifica se ha algum inteiro VALUE dentro da lista LIST\n");
        printf("e, caso haja, procura pelo indice do valor desejado e\n");
        printf("substitui, a partir deste indice, ate o final, o valor\n");
        printf("ali encontrado, pelo seu seguinte.\n");
        printf(" Repete esse processo ate retirar todas as repeticoes\n");
        printf("desejadas, na ordem que aparece. Caso haja menos elementos\n");
        printf("que o indicado em QUANTITY, serA mostrado na tela. \n");
        printf("===========================================================\n");
    }
    else if(func == "sort")
    {
        printf("===========================================================\n");
        printf("Formato: sort(list)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  list: um array do tipo NUMBER, com tamanho N elementos\n");
        printf("        mais um indice ao final, com a estrutura interna\n");
        printf("        ISNUM = FALSE.\n");
        printf("}\n\n");
        printf(" Utiliza o algoritmo de bubble sort para organizar em\n");
        printf("ordem crescente a lista LIST.\n");
        printf("===========================================================\n");
    }
    else if(func == "invert")
    {
        printf("===========================================================\n");
        printf("Formato: sort(list)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  list: um array do tipo NUMBER, com tamanho N elementos\n");
        printf("        mais um indice ao final, com a estrutura interna\n");
        printf("        ISNUM = FALSE.\n");
        printf("}\n\n");
        printf(" Utiliza o algoritmo de bubble sort sem condicoes para\n");
        printf("inverter o indice dos elementos na lista.\n");
        printf("===========================================================\n");
    }
    else if(func == "conc")
    {
        printf("===========================================================\n");
        printf("Formato: conc(firstList, secondList, newList, newListSize,\n");
        printf("              ordenate)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  firstList: um array do tipo NUMBER, com tamanho N\n");
        printf("             elementos mais um indice ao final, com a\n");
        printf("             estrutura interna ISNUM = FALSE.\n\n");
        printf("  secondList: outro array do tipo NUMBER, com tamanho N\n");
        printf("              elementos mais um indice ao final, com a\n");
        printf("              estrutura interna ISNUM = FALSE.\n\n");
        printf("  newList: um terceiro array do tipo NUMBER, com tamanho\n");
        printf("           maior ou igual a soma da quantidade de elementos\n");
        printf("           presentes nas listas anteriores mais um indice\n");
        printf("           ao final, com a estrutura interna ISNUM = FALSE.\n\n");
        printf("  newListSize: tamanho da nova lista. Utilizado para\n");
        printf("               verificar se possui tamanho suficiente para\n");
        printf("               receber os valores.\n\n");
        printf("  ordenate: fator de ordenacao, caso queira ordenar a nova\n");
        printf("            lista criada. Recebe 1 caso queira em ordem\n");
        printf("            crescente e -1 caso seja em ordem decrescente.\n");
        printf("}\n\n");
        printf(" Verifica se o tamanho da NEWLISTSIZE e suficiente. Caso\n");
        printf("seja, transfere todos os valores da FIRSTLIST para a\n");
        printf("NEWLIST. Ao terminar, comeca a transferir os valores da\n");
        printf("SECONDLIST para a NEWLIST, a partir do ultimo indice,\n");
        printf("verificando se os  valores ja estao inseridos. Apos\n");
        printf("adicionar todos os valores, de acordo com o fator\n");
        printf("ORDENATE, organiza ou nao a lista.\n");
        printf("===========================================================\n");
    }
    else if(func == "help")
    {
        printf("===========================================================\n");
        printf("Formato: help(func)\n\n");
        printf("Parametros\n");
        printf("{\n");
        printf("  func: nome da funcao a ser analisada.\n");
        printf("}\n\n");
        printf(" Mostra na tela os parametros e funcionamento\n");
        printf("da funcao utilizada como parametro.\n");
        printf("===========================================================\n");
    }
    else
    {
        printf("A funcao requisitada nao esta na bibioteca.\n");
    }
}
