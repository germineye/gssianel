#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define MAX_SIZE 36

double a[MAX_SIZE][MAX_SIZE + 1];
int n;

void mtrx_in();
void gss();
int findPiv(int, int);
void rowSwp(int, int);
void mtrx_out();

int main()
{
    printf("enter the number of equations: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE)
    {
        printf("im not einstien🥀\n");
        return 36;
    }

    printf("(%d x %d):\n", n, n + 1);
    mtrx_in();
    gss();
    printf("\nresult:\n");
    mtrx_out();

    return 0;
}

void mtrx_in()
{
    for (int i = 0; i < n; i++)
    {
        printf("row %d: ", i + 1);
        for (int j = 0; j <= n; j++)
        {
            scanf("%lf", &a[i][j]);
        }
    }
}

void gss()
{
    for (int i = 0; i < n; i++)
    {
        int pivotRow = findPiv(i, i);
        if (pivotRow != i)
        {
            rowSwp(i, pivotRow);
        }

        if (fabs(a[i][i]) < 1e-9)
        {
            continue;
        }

        for (int j = i + 1; j < n; j++)
        {
            double factor = a[j][i] / a[i][i];
            for (int k = i; k <= n; k++)
            {
                a[j][k] -= factor * a[i][k];
            }
        }
    }
}

/* Tim hang co phan tu pivot lon nhat */
int findPiv(int col, int start)
{
    int maxRow = start;
    for (int i = start + 1; i < n; i++)
    {
        if (fabs(a[i][col]) > fabs(a[maxRow][col]))
        {
            maxRow = i;
        }
    }
    return maxRow;
}

void rowSwp(int r1, int r2)
{
    for (int j = 0; j <= n; j++)
    {
        double temp = a[r1][j];
        a[r1][j] = a[r2][j];
        a[r2][j] = temp;
    }
}

void mtrx_out()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            printf("%10.3f", a[i][j]);
        }
        printf("\n");
    }
}
