#include <stdio.h>


void    shift(int mtrx[6][6], int n)
{
    int i;
    int j;
    int tmp;

    i = 0;
    j = 0;
    tmp = 0;
    // циклов будет столько, пока я могу раглядеть вложенные квадраты внутри большого. последний квадратик 5 1
    //                                                                                                     0 5   (из мэйна) всего три квадрарата. 6 \ 2 = 3


    while (i < n / 2)
    {
        j = i;
        // идея в том, чтобы менять местами цифры в 1) первом ряду 2) в последнем столбце 3) в последнем ряду 4) в первом столбце
        // цикл до предпоследного места в ряду, потому что я методом выше переставляю местами цифры в след квадрате так же по 4 точкам. будет напомнинать некий ромб
        while (j < n - i - 1)
        {
            tmp = mtrx[i][j];
            mtrx[i][j] = mtrx[n - 1 - j][i];
            mtrx[n - 1 -j][i] = mtrx[n - 1 -i][n - 1-j];
            mtrx[n - 1 - i][n - 1 -j] = mtrx[j][n - 1 - i];
            mtrx[j][n - 1 - i] = tmp;
            j++;
        }
        i++;
    }
}

void    print_matrix(int mtrx[6][6], int n)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < n)
    {
        j = 0;
        while (j < n)
        {
            printf("%d", mtrx[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

int main(void)
{
    int matrix[6][6] = { {0, 1, 2, 3, 4, 5},
                         {5, 4, 3, 2, 1, 0},
                         {3, 4, 5, 1, 0, 2},
                         {2, 1, 0, 5, 4, 3},
                         {3, 5, 2, 4, 1, 0},
                         {4, 0, 1, 5, 3, 2}};
    print_matrix(matrix, 6);
    shift(matrix, 6);
    printf("\n");
    print_matrix(matrix, 6);
    return (0);
}

// самым неочевидным было понять, как правильно выбрать расположение конкретных точек для каждого квадрата. путал i с J в [n - 1 - (i | j)] но потом понял что там чередование с [][i] на [][j]
//пойду решать еще задачки на похожую тему, думаю дело практики
// компилил gcc -Wall -Werror -Wextra rotate.c
