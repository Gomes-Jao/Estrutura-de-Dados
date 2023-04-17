#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

void get_name(char *name, int i);
int validate_name(char *name);
void print(int valid);

int main()
{
    char name[100];
    int valid = 1;

    printf("Digite seu nome: ");

    do
    {
        get_name(name, 0);
        valid = validate_name(name);
        print(valid);     
    } while(valid == 0);

    return 0;
}

void get_name(char *name, int i)
{
    int c = getchar();
    if(c == '\n') name[i] = '\0';
    else
    {
        name[i] = c;
        get_name(name, i + 1);
    }
}

int validate_name(char *name)
{
    char keyLetter;

    if(strlen(name) < 3) return 0;

    for(int i = 0; i < strlen(name); i++)
    {
        if(isdigit(name[i])) return 0;
        if(i == 0)
        {
            if(isupper(name[0])) keyLetter = name[0];
            else return 0;
        }
        else if(name[i] == ' ') keyLetter = name[i];
        else if(isupper(name[i]))
        {
            if(keyLetter == ' ')
            {
                if(name[i - 1] == ' ') keyLetter = name[i];
                else return 0;
            }
            else return 0;
        }
    }
    return 1;
}

void print(int valid)
{
    if(valid == 0) printf("Por favor, digite um nome correto: ");
    else if(valid == 1) printf("Nome valido!");
}
