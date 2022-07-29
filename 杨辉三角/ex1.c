#include <stdio.h>
#include <stdlib.h>
/***** Begin *****/
int main()
{
    int n;
    scanf("%d", &n);
    int a[10][10];
    printf("[");
    for (int i = 0; i < n; i++)
    {
        a[i][0] = a[i][i] = 1;
        for (int j = 1; j < i; j++)
        {
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
        }
        printf("[");
        for (int j = 0; j <= i; j++)
        {
            printf("%d", a[i][j]);
            if (j != i) putchar(',');
        }
        putchar(']');
        if (i != n - 1) putchar(',');
    }
    putchar(']');
    return 0;
}
/***** End *****/