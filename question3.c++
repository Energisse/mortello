#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <limits>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include <malloc.h>
#define MINMAX_MAX_DEPTH 3
struct sysinfo memInfo;
using namespace std;

int checkCovered(char p[], int n)
{
    char m[(n * n) + 1];
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

void placePawn(char grid[], int n, char coups[], char joueur)
{
    for (int i = 0; i < n * n; i++)
    {
        if (coups[i] == '0')
            continue;

        grid[i] = joueur;
        if ((i + 1) % n)
        {
            grid[i + 1] = joueur;
        }
        if (i % n != 0)
        {
            grid[i - 1] = joueur;
        }
        if (i >= n)
        {
            grid[i - n] = joueur;
        }
        if (i < n * n - n)
        {
            grid[i + n] = joueur;
        }
    }
}

int getNbCases(const char grid[], int n)
{
    int count = n * n;
    for (int i = 0; i < n * n; i++)
    {
        if (grid[i] != '0')
            count--;
    }
    return count;
}

void displayGrid(char grid[], int n)
{
    int largeur = (int)log10(n - 1);
    cout << "\t";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < largeur - (int)log10(i - 1); j++)
        {
            cout << " ";
        }
        cout << " " << i;
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "     " << i << "\t";
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < largeur; k++)
            {
                cout << " ";
            }
            cout << " " << ((grid[j + i * n] == '0') ? '-' : grid[j + i * n]);
        }
        cout << endl;
    }
}

int saisie(string text, int n)
{
    int x;
    while (true)
    {
        cout << text;
        cin >> x;
        if (!cin.fail() && x >= 0 && x < n)
            return x;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void playerPlay(char grid[], int n)
{
    displayGrid(grid, n);
    int x1, y1, x2, y2;
    char coups[n * n];
    for (int i = 0; i < n * n; i++)
    {
        coups[i] = '0';
    }
    while (true)
    {
        x1 = saisie("Entrez la coordonnée X du premier point :", n);
        y1 = saisie("Entrez la coordonnée Y du premier point :", n);

        if (grid[x1 + y1 * n] == '0')
        {
            coups[x1 + y1 * n] = 'x';
            break;
        }
        cout << "Impossible de jouer ici" << endl;
    }

    cout << endl;
    if (getNbCases(grid, n) > 1)
    {

        while (true)
        {
            x2 = saisie("Entrez la coordonnée X du second point :", n);
            y2 = saisie("Entrez la coordonnée Y du second point :", n);

            if (grid[x2 + y2 * n] == '0' and (x1 != x2 or y1 != y2))
            {
                coups[x2 + y2 * n] = 'x';
                break;
            }
            cout << "Impossible de jouer ici" << endl;
        }
    }
    placePawn(grid, n, coups, 'x');
}

void binary(char grid[], int n, char **combinaison, int &nbCombinaison, int i = 0)
{
    if (i == 2)
    {
        strcpy(combinaison[--nbCombinaison], grid);
        return;
    }
    // lorsque l'on atteinds une feuille de l'arbre
    if (n == 0)
        return;
    if (grid[n - 1] == '0')
    {
        binary(grid, n - 1, combinaison, nbCombinaison, i);

        // Le case est jouable
        grid[n - 1] = '1';
        binary(grid, n - 1, combinaison, nbCombinaison, i + 1);
        grid[n - 1] = '0';
    }
    else
    {
        binary(grid, n - 1, combinaison, nbCombinaison, i);
    }
}

void getCombinaisons(const char grid[], int n, char ***combinaisons, int &nbcombinaisons)
{
    int nbCase = getNbCases(grid, n);
    // il n'y a alors que une combinaison possible
    if (nbCase <= 2)
    {
        nbcombinaisons = 1;
        *combinaisons = new char *[1];
        (*combinaisons)[0] = new char[n * n];
        for (int i = 0; i < n * n; i++)
        {
            if (grid[i] == '0')
            {
                (*combinaisons)[0][i] = '1';
            }
            else
            {
                (*combinaisons)[0][i] = '0';
            }
        }
        return;
    }
    // taille des combinaison possible de 2 parmi (n*n) -> n!/2(n-2)! -> n*(n-1)*(n-2)!/2*(n-2)!-> n*(n-1)/2
    nbcombinaisons = (nbCase * (nbCase - 1) / 2);
    *combinaisons = new char *[nbcombinaisons];
    for (int i = 0; i < nbcombinaisons; i++)
    {
        (*combinaisons)[i] = new char[n * n];
    }
    int tailleCombinaison = nbcombinaisons;

    // copy de la grille afin de ne pas la modifier pendant la recurence
    char tmpGrid[n * n + 1];
    strcpy(tmpGrid, grid);
    binary(tmpGrid, n * n, *combinaisons, tailleCombinaison, 0);
    for (int i = 0; i < nbcombinaisons; i++)
    {
        for (int j = 0; j < n * n; j++)
        {
            if (grid[j] == (*combinaisons)[i][j])
            {
                (*combinaisons)[i][j] = '0';
            }
        }
    }
}

int minmax(const char grid[], int n, bool maximizing, char bestMove[], int depth = MINMAX_MAX_DEPTH)
{
    bool complet = true;
    for (int i = 0; i < n * n; i++)
    {
        if (grid[i] == '0')
        {
            complet = false;
            break;
        }
    }
    if (depth == 0 || complet)
    {
        int count = 0;
        for (int i = 0; i < n * n; i++)
        {
            if (grid[i] == 'o')
            {
                count++;
            }
        }
        return count;
    }
    char **combinaisons;
    int nbcombinaisons = 0;

    getCombinaisons(grid, n, &combinaisons, nbcombinaisons);
    int val;
    if (maximizing)
    {
        val = -1;
        for (int i = 0; i < nbcombinaisons; i++)
        {
            char choix[n * n + 1];
            strcpy(choix, grid);
            placePawn(choix, n, combinaisons[i], 'o');
            int iteration = minmax(choix, n, false, bestMove, depth - 1);
            if (iteration > val)
            {
                if (depth == MINMAX_MAX_DEPTH)
                    strcpy(bestMove, combinaisons[i]);
                val = iteration;
            }
        }
    }
    else
    {
        val = std::numeric_limits<int>::max();
        for (int i = 0; i < nbcombinaisons; i++)
        {
            char choix[n * n + 1];
            strcpy(choix, grid);
            placePawn(choix, n, combinaisons[i], 'x');

            int iteration = minmax(choix, n, true, bestMove, depth - 1);
            if (iteration < val)
            {
                val = iteration;
            }
        }
    }
    // deallocate memory
    for (int i = 0; i < nbcombinaisons; i++)
    {
        delete[] combinaisons[i];
    }
    delete[] combinaisons;
    return val;
}

int main()
{
    int n;
    cout << "taille : ";
    cin >> n;
    char grid[n * n + 1];
    for (int i = 0; i < n * n; i++)
    {
        grid[i] = '0';
    }
    grid[(n * n)] = '\0';
    int minPion = n * n;
    while (getNbCases(grid, n))
    {
        playerPlay(grid, n);
        if (getNbCases(grid, n) != 0)
        {
            char bestMove[n * n + 1];
            minmax(grid, n, true, bestMove);
            placePawn(grid, n, bestMove, 'o');
        }
    }
    int score = 0;
    for (int i = 0; i < n * n; i++)
    {
        if (grid[i] == 'x')
        {
            score++;
        }
    }
    int scoreIA = n * n - score;
    displayGrid(grid, n);

    if (score > scoreIA)
    {
        cout << "Victoire : " << score << " à " << scoreIA << endl;
    }
    else if (score < scoreIA)
    {
        cout << "Defaite  : " << score << " à " << scoreIA << endl;
    }
    else
    {
        cout << "Egalité" << endl;
    }
    return 0;
}
