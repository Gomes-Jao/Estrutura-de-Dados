#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printar(int *arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        if(i == (len - 1))
        {
            printf("%d\n", arr[i]);
        }
        else
        {
            printf("%d ", arr[i]);
        }
    }
}

void sort(int *arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < (len - 1); j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
            }
        }
    }
}

int is_in(int *arr, int value, int maxLen)
{
    for(int i = 0; i < maxLen; i++)
    {
        if(arr[i] == value) return 1;
    }

    return 0;
}

int get_complement(int *arr1, int *arr2, int *arrComplement, int len1, int len2, int *lenComplement)
{
    *lenComplement = 0;

    for(int i = 0; i < len2; i++)
    {
        if(!(is_in(arr1, arr2[i], len1)))
        {
            return 1;
        }
        else if(!(is_in(arr2, arr1[i], len2)))
        {
            arrComplement[*lenComplement] = arr1[i];
            *lenComplement += 1;
        }
    }

    return 0;
}

void get_intersection(int *arr1, int *arr2, int *arrIntersection, int len1, int len2, int *lenIntersection)
{
    *lenIntersection = 0;

    if(len1 > len2)
    {
        for(int i = 0; i < len1; i++)
        {
            if(is_in(arr2, arr1[i], len2))
            {
                arrIntersection[*lenIntersection] = arr1[i];
                *lenIntersection += 1;
            }
        }
    }
    else
    {
        for(int i = 0; i < len2; i++)
        {
            if(is_in(arr1, arr2[i], len1))
            {
                arrIntersection[*lenIntersection] = arr1[i];
                *lenIntersection += 1;
            }
        }
    }
}

void get_union(int *arr1, int *arr2, int *arrUnion, int len1, int len2, int *lenUnion)
{
    *lenUnion = 0;

    for(int i = 0; i < len1; i++)
    {
        if(*lenUnion == 0)
        {
            arrUnion[*lenUnion] = arr1[i];
            *lenUnion += 1;
        }
        else if(!(is_in(arrUnion, arr1[i], *lenUnion)))
        {
            arrUnion[*lenUnion] = arr1[i];
            *lenUnion += 1;
        }
    }
    for(int i = 0; i < len2; i++)
    {
        if(!(is_in(arrUnion, arr2[i], *lenUnion)))
        {
            arrUnion[*lenUnion] = arr2[i];
            *lenUnion += 1;
        }
    }
}

void get_arr(int *arr, int *len)
{
    char aux;
    *len = 0;
    printf("Digite os digitos do vetor: ");
    do
    {
        scanf("%d%c", &arr[*len], &aux);
        *len += 1;
    } while (aux != '\n');
}

int main()
{
    int arr1[10], arr2[10], arrUnion[20], arrComplement[20], arrIntersection[20];
    int len1, len2, lenUnion, lenComplement, lenIntersection;

    get_arr(arr1, &len1);
    get_arr(arr2, &len2);

    get_union(arr1, arr2, arrUnion, len1, len2, &lenUnion);

    get_intersection(arr1, arr2, arrIntersection, len1, len2, &lenIntersection);

    int isPossible = get_complement(arr1, arr2, arrComplement, len1, len2, &lenComplement);

    sort(arr1, len1);
    sort(arr2, len2);
    sort(arrUnion, lenUnion);
    sort(arrIntersection, lenIntersection);
    sort(arrComplement, lenComplement);

    printf("O vetor resultante da união de A e B é: ");
    printar(arrUnion, lenUnion);
    printf("O vetor resultante da interseção de A e B é: ");
    printar(arrIntersection, lenIntersection);

    if(isPossible)
    {
        printf("O complemento de B em A é: ");
        printar(arrComplement, lenComplement);
    }
    else printf("Impossível encontrar o complemento.");

    return 0;
}
