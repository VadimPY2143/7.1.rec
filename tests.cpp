#define UNIT_TESTING
#include "main.cpp"
#include <gtest/gtest.h>

// --- 1. Перевірка критерію ---
TEST(MatrixTests, CriterionCheck) {
    // Критерій: всі непарні, або крім від’ємних
    EXPECT_TRUE(satisfiesCriterion(3));    // непарне → ✅
    EXPECT_TRUE(satisfiesCriterion(0));    // не від’ємне → ✅
    EXPECT_TRUE(satisfiesCriterion(12));   // не від’ємне → ✅
    EXPECT_FALSE(satisfiesCriterion(-2));  // парне й від’ємне → ❌
    EXPECT_TRUE(satisfiesCriterion(-3));   // непарне → ✅
}

// --- 2. Перевірка підрахунку й суми ---
TEST(MatrixTests, ProcessMatrixCountAndSum) {
    const int rows = 2, cols = 3;
    int** X = new int*[rows];
    for (int i = 0; i < rows; i++)
        X[i] = new int[cols];

    // Матриця:
    //  1  -2   3
    //  0   4  -5
    int values[2][3] = {{1, -2, 3}, {0, 4, -5}};
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            X[i][j] = values[i][j];

    int count = 0, sum = 0;
    processMatrix(X, rows, cols, count, sum);

    // Задовольняють критерію: 1 (непарне), 3 (непарне), 0 (не від’ємне),
    // 4 (не від’ємне), -5 (непарне)
    // Не задовольняє лише -2
    EXPECT_EQ(count, 5);
    EXPECT_EQ(sum, 1 + 3 + 0 + 4 + (-5));

    // Всі задовільні елементи замінено на 0
    EXPECT_EQ(X[0][0], 0);  // 1 → 0
    EXPECT_EQ(X[0][1], -2); // лишився
    EXPECT_EQ(X[0][2], 0);  // 3 → 0
    EXPECT_EQ(X[1][0], 0);  // 0 → 0
    EXPECT_EQ(X[1][1], 0);  // 4 → 0
    EXPECT_EQ(X[1][2], 0);  // -5 → 0

    for (int i = 0; i < rows; i++) delete[] X[i];
    delete[] X;
}

// --- 3. Перевірка сортування ---
TEST(MatrixTests, SortRowsWorks) {
    const int rows = 3, cols = 4;
    int** X = new int*[rows];
    for (int i = 0; i < rows; i++)
        X[i] = new int[cols];

    // Формат: [col0, col1, col2, col3]
    int values[3][4] = {
        {2, 5, 0, 10},
        {1, 7, 0, 20},
        {2, 3, 0, 15}
    };

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            X[i][j] = values[i][j];

    sortRows(X, rows, cols);

    // Очікування:
    // Спочатку сортування ↑ col0:
    //   {1,7,0,20}, {2,5,0,10}, {2,3,0,15}
    // Далі для однакових col0=2 → ↑ col1, але 3<5, тому:
    //   {1,7,0,20}, {2,3,0,15}, {2,5,0,10}
    EXPECT_EQ(X[0][0], 1);
    EXPECT_EQ(X[1][0], 2);
    EXPECT_EQ(X[2][0], 2);

    EXPECT_EQ(X[1][1], 3);
    EXPECT_EQ(X[2][1], 5);

    for (int i = 0; i < rows; i++) delete[] X[i];
    delete[] X;
}
