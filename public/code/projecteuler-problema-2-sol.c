#include <stdio.h>

int main()
{
    int a = 1, b = 2, c = 3;
    int sum = 2;	// second term

    while (c < 4000000) {
        a = b;
        b = c;
        c = a + b;

        if (c % 2 == 0) { // even ?
            sum += c;
        }
    }

    printf("sum = %d\n", sum);
    return 0;
}
