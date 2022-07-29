#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/***** Begin *****/
int main()
{
    int n;
    scanf("%d", &n);
    int a[10][10];
    for (int i = 0; i < n; i++)
    {
        a[i][0] = a[i][i] = 1;
        #pragma omp parallel for
        for (int j = 1; j < i; j++)
        {
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
        }
    }
    putchar('[');
    for(int i = 0; i < n; i++)
    {
        putchar('[');
        for(int j = 0; j <= i; j++)
        {
            printf("%d", a[i][j]);
            if(j != i) putchar(',');
        }
        putchar(']');
        if(i != n-1) putchar(',');
    }
    putchar(']');
    putchar('\n');
    return 0;
}
/***** End *****/
