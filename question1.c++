#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void binary(int n, char s[], int index)
{
    if (index == n)
    {
        cout << s << endl;
        return;
    }
    s[index] = '0';
    binary(n, s, index + 1);
    s[index] = '1';
    binary(n, s, index + 1);
}

int main()
{
    int n;
    cout << "taille : ";
    cin >> n;
    char s[n + 1];
    s[n] = '\0';
    binary(n, s, 0);
    return 0;
}
