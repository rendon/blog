#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int BUFFER_SIZE = 200 * 1024;
char buffer[BUFFER_SIZE];

int main(int argc, char *argv[])
{
    int n, i, A = 0, F = 0, ans = 0;
    scanf("%d\n", &n);

    for (i = 0; i < n; i++)
        buffer[i] = getchar();

    for (i = 0; i < n; i++)
        if (buffer[i] == 'A')
            A++;
        else if (buffer[i] == 'F')
            F++;

    for (i = 0; i < n; i++) {
        if ((buffer[i] == 'I') && ((A + F) + 1 == n)) {
            ans++;
        } else if ((buffer[i] == 'A') && ((A + F) == n)) {
            ans++;
        }
    }

    cout << ans << endl;

    return EXIT_SUCCESS;
}
