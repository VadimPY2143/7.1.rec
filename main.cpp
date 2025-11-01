#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// ==== 1. Генерація випадкових чисел рекурсивно ====
void generateMatrix(int** X, int rows, int cols, int i = 0, int j = 0) {
    if (i == rows) return;
    X[i][j] = rand() % 36 - 12; // (-12 ... 23)
    if (j + 1 < cols)
        generateMatrix(X, rows, cols, i, j + 1);
    else
        generateMatrix(X, rows, cols, i + 1, 0);
}

// ==== 2. Виведення матриці рекурсивно ====
void printMatrix(int** X, int rows, int cols, int i = 0, int j = 0) {
    if (i == rows) return;
    cout << setw(5) << X[i][j];
    if (j + 1 < cols)
        printMatrix(X, rows, cols, i, j + 1);
    else {
        cout << endl;
        printMatrix(X, rows, cols, i + 1, 0);
    }
}

// ==== 3. Перевірка критерію ====
bool satisfiesCriterion(int val) {
    return val % 2 != 0 || val >= 0;
}

// ==== 4. Обчислення суми і кількості (рекурсивно) ====
void processMatrix(int** X, int rows, int cols, int& count, int& sum, int i = 0, int j = 0) {
    if (i == rows) return;
    if (satisfiesCriterion(X[i][j])) {
        sum += X[i][j];
        count++;
        X[i][j] = 0; // заміна нулем
    }
    if (j + 1 < cols)
        processMatrix(X, rows, cols, count, sum, i, j + 1);
    else
        processMatrix(X, rows, cols, count, sum, i + 1, 0);
}

// ==== 5. Порівняння двох рядків для сортування ====
bool compareRows(int* a, int* b) {
    if (a[0] != b[0]) return a[0] < b[0];           // ↑ 1 стовпчик
    if (a[1] != b[1]) return a[1] < b[1];           // ↑ 2 стовпчик
    return a[3] > b[3];                             // ↓ 4 стовпчик
}

// ==== 6. Рекурсивне сортування рядків (наприклад, рекурсивний bubble sort) ====
void sortRows(int** X, int rows, int cols, int i = 0) {
    if (i == rows - 1) return;
    for (int j = 0; j < rows - i - 1; j++) {
        if (!compareRows(X[j], X[j + 1])) {
            swap(X[j], X[j + 1]);
        }
    }
    sortRows(X, rows, cols, i + 1);
}

// ==== 7. Головна функція ====
int main() {
    srand(time(0));

    const int rows = 7;
    const int cols = 6;
    int** X = new int*[rows];
    for (int i = 0; i < rows; i++)
        X[i] = new int[cols];

    cout << "Початкова матриця:\n";
    generateMatrix(X, rows, cols);
    printMatrix(X, rows, cols);

    // ---- Завдання 1 ----
    int count = 0, sum = 0;
    processMatrix(X, rows, cols, count, sum);

    cout << "\nПісля заміни елементів, що задовольняють критерію:\n";
    printMatrix(X, rows, cols);
    cout << "\nКількість = " << count << ", сума = " << sum << endl;

    // ---- Завдання 2 ----
    sortRows(X, rows, cols);
    cout << "\nПісля впорядкування рядків:\n";
    printMatrix(X, rows, cols);

    // очищення
    for (int i = 0; i < rows; i++) delete[] X[i];
    delete[] X;

    return 0;
}
