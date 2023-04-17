#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void printar(int valid)
{
    if(valid == 2) printf("CPF válido.");
    else printf("CPF inválido.");
}

int multiplying_digits(int *cpf, int indexNumber)
{
    int result = 0;
    int mult = 10;
    for(int i = indexNumber - 9; i < indexNumber; i++)
    {
        result += (cpf[i] * mult);
        mult --;
    }
    return result;
}

int verifying_digit(int *cpf, int indexNumber)
{
    int sum = multiplying_digits(cpf, indexNumber);
    
    int numKey = sum % 11;

    if(numKey == 0 || numKey == 1)
    {
        if(cpf[indexNumber] != 0) return 0;
    }
    else
    {
        if(cpf[indexNumber] != 11 - numKey) return 0;
    }
    return 1;
}

void get_cpf(int *cpf)
{
    printf("Por favor, digite os números de seu CPF: ");
    for(int i = 0; i < 11; i++)
    {
        cpf[i] = (getchar() - 48);
    }
}

int main()
{
    int cpf[11];
    int valid = 0;

    get_cpf(cpf);

    valid += verifying_digit(cpf, 9);
    valid += verifying_digit(cpf, 10);

    printar(valid);

    return 0;
}
