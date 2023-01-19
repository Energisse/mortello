#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;
int checkCovered(char p[], int n)
{
    char m[(n * n) + 1] = {};
    strcpy(m, p);
    for (int i = 0; i < n * n; i++)
    {
        if (p[i] == '1')
        {
            if ((i + 1) % n)
            {
                m[i + 1] = '1';
            }
            if (i % n)
            {
                m[i - 1] = '1';
            }
            if (i >= n)
            {
                m[i - n] = '1';
            }
            if (i < n * n - n)
            {
                m[i + n] = '1';
            }
        }
    }
    for (int i = 0; i < n * n; i++)
    {
        if (m[i] != '1')
            return false;
    }
    return true;
}

void binary(int n, char s[], int index, int taille, char minGrid[], int &minPion)
{
    // lorsque l'on atteinds une feuille de l'arbre
    if (index == n)
    {
        if (checkCovered(s, taille))
        {
            int pion = 0;
            // Compte le nombre de pion placcé
            for (int i = 0; i < n * n; i++)
            {
                if (s[i] == '1')
                    pion++;
            }
            if (pion < minPion)
            {
                // enregistre le meilleur placement
                minPion = pion;
                strcpy(minGrid, s);
            }
        }
        return;
    }
    s[index] = '0';
    binary(n, s, index + 1, taille, minGrid, minPion);
    s[index] = '1';
    binary(n, s, index + 1, taille, minGrid, minPion);
}

int main()
{
    int n;
    cout << "taille : ";
    cin >> n;
    char s[(n * n) + 1];
    char minGrid[n * n + 1];
    int minPion = n * n;
    s[(n * n)] = '\0';
    minGrid[(n * n)] = '\0';
    binary(n * n, s, 0, n, minGrid, minPion);
    cout << minPion << endl;
    cout << minGrid << endl;
    return 0;
}
