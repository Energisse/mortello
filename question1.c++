#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void afficher_combinaisons_binaires(int n, char str[] = {}, int size = 0)
{
    if (n == 0)
    {
        for (int i = 0; i < size; i++)
        {
            cout << str[i];
        }
        cout << endl;
        return;
    }
    char str0[size + 1];
    char str1[size + 1];
    strncpy(str0, str, size);
    strncpy(str1, str, size);
    str0[size] = '0';
    str1[size] = '1';
    afficher_combinaisons_binaires(n - 1, str0, size + 1);
    afficher_combinaisons_binaires(n - 1, str1, size + 1);
}

int main()
{
    afficher_combinaisons_binaires(16);
    return 0;
}
