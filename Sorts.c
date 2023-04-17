#include <stdio.h>
#include <stdlib.h>

void printar_array(int *arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        if(i == n - 1) printf("%d\n\n", arr[i]);
        else printf("%d ", arr[i]);
    }
}

void swap(int *valor1, int *valor2)
{
    int aux = *valor1;
    *valor1 = *valor2;
    *valor2 = aux;
}
//Não sabemos o que a roberta quer aqui
void bubble_sort(int *arr, int size) // Complexidade O(n / n² / n²)
{
    int i, j;
    for (i = 0; i < size - 1; i++)
    {
        printf("Iteracao %d: ", i);
        printar_array(arr, size);

        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}
//Já tá otimizado
void select_sort(int *arr, int size) // Complexidade O(n² / n² / n²)
{
    int i, j, minIndex;

    for(int i = 0; i < size - 1; i++)
    {

        printf("Iteracao %d: ", i);
        printar_array(arr, size);

        minIndex = i;
        for(int j = i; j < size; j++)
        {
            if(arr[j] < arr[minIndex]) minIndex = j;
        }
        swap(&arr[i], &arr[minIndex]);
    }
}

void select_sort_opt(int *arr, int size)
{
    int minIndex, maxIndex;

    for(int i = 0, j = size - 1; i < j; i++, j--)
    {

        printf("Iteracao %d: ", i);
        printar_array(arr, size);

        minIndex = i;
        maxIndex = j;

        for(int k = i; k <= j; k++)
        {
            if(arr[k] < arr[minIndex]) minIndex = k;
            if(arr[k] < arr[maxIndex]) maxIndex = k;
        }

        swap(&arr[i], &arr[minIndex]);

        if(maxIndex == i) maxIndex = minIndex;

        swap(&arr[j], &arr[maxIndex]);
    }
}
//Já tá otimizado
void bin_sort(int *arr, int size) // Complexidade O(log n / log n / log n) PRECISA SER REVISTO
{
    int swapped = 1;

    for(int i = 0; i < size && swapped; i++)
    {
        swapped = 0;

        while(arr[i] != i)
        {
            swap(&arr[arr[i]], &arr[i]);
            swapped = 1;
        }
    }   
}

void bin_sort_opt(int *arr, int size)
{
    int swapped = 1;

    for(int i = 0; i < size && swapped; i++)
    {
        swapped = 0;

        while(arr[i] != i && arr[size - 1 - i] != size - 1 - i)
        {
            swap(&arr[arr[i]], &arr[i]);
            swap(&arr[arr[size - 1 - i]], &arr[size - 1 - i]);
            swapped = 1;
        }
        while(arr[i] != i)
        {
            swap(&arr[arr[i]], &arr[i]);
            swapped = 1;
        }
        while(arr[size - 1 - i] != size - 1 - i)
        {
            swap(&arr[arr[size - 1 - i]], &arr[size - 1 - i]);;
            swapped = 1;
        }
    }   
}
//Difícil de otimizar
void insert_sort(int *arr, int size) // Complexidade O(n / n² / n²)
{
    int i, j, key;

    for(int i = 1; i < size; i++)
    {
        printf("Iteracao %d: ", i);
        printar_array(arr, size);

        for(int j = i; (j > 0) && (arr[j] < arr[j - 1]); j--)
        {
            swap(&arr[j], &arr[j - 1]);
        }
    }
}
//Bonito demais pra otimizar
void shell_sort(int *arr, int size) // Complexidade O(nlog n / nlog n / n²)
{
    int mov = size / 2 + 1;

    for(int mov = size / 2 + 1, k = 0; mov > 0; mov--, k++)
    {
        printf("Iteracao %d: ", k);
        printar_array(arr, size);

        for(int i = 0; i + mov < size; i++)
        {
            if(arr[i] > arr[i + mov]) swap(&arr[i], &arr[i + mov]);
        }
    }
}

void sort_for_merge(int *arr, int init, int mid, int end)
{
    int i = 0;
    int arr1[mid - init + 1];
    int arr2[end - mid];

    for(int j = 0; j < mid - init + 1; j++)
    {
        arr1[j] = arr[init + j];
    }

    for(int k = 0; k < end - mid; k++)
    {
        arr2[k] = arr[mid + k + 1];
    }

    for(int i = init, j = 0, k = 0; i < end + 1; i++)
    {
        
        if((j < mid - init + 1) && (k < end - mid))
        {
            if(arr1[j] < arr2[k])
            {
                arr[i] = arr1[j++];
            }
            else
            {
                arr[i] = arr2[k++];
            }
        }
        else
        {
            while(j < mid - init + 1) arr[i++] = arr1[j++];
            while(k < end - mid) arr[i++] = arr2[k++];
        }
    }
}

void merge_sort(int *arr, int init, int end) // Complexidade O(nlog n / nlog n / nlog n)
{
    if(init < end)
    {
        int mid = (init + end) / 2;

        merge_sort(arr, init, mid);
        merge_sort(arr, mid + 1, end);
        sort_for_merge(arr, init, mid, end);
    }
}
//Em construção ʕっ•ᴥ•ʔっ
void heapify(int *arr, int size, int root)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if(left < size && arr[left] > arr[largest]) largest = left;
    if(right < size && arr[right] > arr[largest]) largest = right;

    if(largest != root)
    {
        swap(&arr[root], &arr[largest]);
        heapify(arr, size, largest);
    } 
}

void heap_sort(int *arr, int size) // Complexidade O(nlog n / nlog n / nlog n)
{
    for(int i = size / 2 - 1; i >= 0; i--) heapify(arr, size, i);
    for(int i = size - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }   
}
//Em construção ʕっ•ᴥ•ʔっ
void radix_sort()
{

}

int partition(int *arr, int init, int end)
{
    int pivot = arr[init];
    int i = init;
    
    for(int j = init + 1; j <= end; j++)
    {
        if(arr[j] <= pivot)
        {
            swap(&arr[++i], &arr[j]);
        }
    }

    swap(&arr[init], &arr[i]);

    return i;
}

void quick_sort(int *arr, int init, int end) // Complexidade(nlog n / nlog n / n²)
{
    if(init < end)
    {
        int pivotIndex = partition(arr, init, end);
        quick_sort(arr, init, pivotIndex - 1);
        quick_sort(arr, pivotIndex + 1, end);
    }
}

int main()
{
    int arrBin[10] = {3, 4, 1, 5, 7, 6, 8, 9, 0, 2};
    int worstArrBin[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    int arr[10] = {9, 8, 7, 0, 3, 4, 123, 23, 1231, 23};
    int worstArr[10] = {1231, 123, 23, 23, 9, 8, 7, 4, 3, 0};

    heap_sort(arr, 10);

    printf("Array final: ");
    printar_array(arr, 10);

    return 0;
}
