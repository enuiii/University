#include <iostream>
#include <math.h>
#include <iomanip>

int main()
{
    int t, hours, min, sec;
    std::cin >> t;

    if (t < 0 || t > 86399)
    {
        return 0;
    }

    hours = t / 3600 % 24;
    min = t / 60 % 60;
    sec = t % 60;

    std::cout << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << min << ":" << std::setw(2) << std::setfill('0') << sec << std::endl;

    int a[100][100], transpose[100][100], row, column, i, j;

    std::cin >> row >> column;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            std::cin >> a[i][j];
        }
    }

    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
        {
            transpose[j][i] = a[i][j];
        }

    for (int i = 0; i < column; ++i)
        for (int j = 0; j < row; ++j)
        {
            std::cout << transpose[i][j] << " ";

            if (j == row - 1)
                std::cout << std::endl;
        }
}