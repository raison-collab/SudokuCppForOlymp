// Программа для решения судоку в общем случае с вводом и выводом через консоль
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Функция для проверки, можно ли поместить цифру в данную клетку
bool isSafe(vector<vector<int>> &grid, int row, int col, int num)
{
    // Проверяем строку и столбец
    for (int i = 0; i < grid.size(); i++)
    {
        if (grid[row][i] == num || grid[i][col] == num)
        {
            return false;
        }
    }
    // Проверяем секцию
    int n = sqrt(grid.size());    // Размер секции
    int rowStart = row - row % n; // Начало секции по строке
    int colStart = col - col % n; // Начало секции по столбцу
    for (int i = rowStart; i < rowStart + n; i++)
    {
        for (int j = colStart; j < colStart + n; j++)
        {
            if (grid[i][j] == num)
            {
                return false;
            }
        }
    }
    // Если все проверки пройдены, то можно поместить цифру
    return true;
}

// Функция для решения судоку с помощью рекурсии и возврата
bool solveSudoku(vector<vector<int>> &grid, int row, int col)
{
    // Если мы дошли до конца сетки, то решение найдено
    if (row == grid.size())
    {
        return true;
    }
    // Если мы дошли до конца строки, то переходим на следующую
    if (col == grid.size())
    {
        return solveSudoku(grid, row + 1, 0);
    }
    // Если клетка уже заполнена, то переходим на следующую
    if (grid[row][col] != 0)
    {
        return solveSudoku(grid, row, col + 1);
    }
    // Пробуем все возможные цифры от 1 до n
    for (int num = 1; num <= grid.size(); num++)
    {
        // Проверяем, можно ли поместить цифру в клетку
        if (isSafe(grid, row, col, num))
        {
            // Помещаем цифру в клетку
            grid[row][col] = num;
            // Продолжаем решать судоку с помощью рекурсии
            if (solveSudoku(grid, row, col + 1))
            {
                return true;
            }
            // Если решение не найдено, то возвращаем клетку в исходное состояние
            grid[row][col] = 0;
        }
    }
    // Если ни одна цифра не подходит, то решение не существует
    return false;
}

// Функция для вывода сетки на экран
void printGrid(vector<vector<int>> &grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid.size(); j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
}

// Главная функция
int main()
{
    // Получаем размер сетки через консоль
    int n;
    cout << "Введите размер сетки: ";
    cin >> n;
    // Проверяем, существует ли поле для судоку размера n x n
    if (n < 1 || sqrt(n) != floor(sqrt(n)))
    {
        // Выводим сообщение об ошибке и завершаем программу
        cout << "Invalid field\n";
        return 0;
    }
    // Создаем сетку размером n x n
    vector<vector<int>> grid(n, vector<int>(n));
    // Получаем значения сетки через консоль
    cout << "Введите значения сетки: \n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
        }
    }
    // Пытаемся решить судоку
    if (solveSudoku(grid, 0, 0))
    {
        // Выводим решение на экран
        cout << "Решение судоку: \n";
        printGrid(grid);
    }
    else
    {
        // Сообщаем, что решение не существует
        cout << "No solution exists\n";
    }
    return 0;
}
