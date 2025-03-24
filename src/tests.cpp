#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

class S21MatrixTest : public ::testing::Test {
 protected:
  S21Matrix matrix1;
  S21Matrix matrix2;
  S21Matrix matrix3;
  S21Matrix zeroMatrix;
  S21Matrix A;
  S21Matrix B;
  S21Matrix matrix;
  S21Matrix m;

  void SetUp() override {
    m = S21Matrix(0, 0);
    matrix = S21Matrix(1, 1);

    A = S21Matrix(2, 3);
    B = S21Matrix(3, 2);

    // Инициализация матриц A и B
    A(0, 0) = 1.0;
    A(0, 1) = 2.0;
    A(0, 2) = 3.0;
    A(1, 0) = 4.0;
    A(1, 1) = 5.0;
    A(1, 2) = 6.0;

    B(0, 0) = 7.0;
    B(0, 1) = 8.0;
    B(1, 0) = 9.0;
    B(1, 1) = 10.0;
    B(2, 0) = 11.0;
    B(2, 1) = 12.0;

    // Инициализация матриц для тестов
    matrix1 = S21Matrix(2, 2);  // 2x2 матрица
    matrix1(0, 0) = 1.0;
    matrix1(0, 1) = 2.0;
    matrix1(1, 0) = 3.0;
    matrix1(1, 1) = 4.0;

    matrix2 = S21Matrix(2, 2);  // 2x2 матрица
    matrix2(0, 0) = 5.0;
    matrix2(0, 1) = 6.0;
    matrix2(1, 0) = 7.0;
    matrix2(1, 1) = 8.0;

    matrix3 = S21Matrix(3, 3);  // 3x3 матрица
    matrix3(0, 0) = 1.0;
    matrix3(0, 1) = 2.0;
    matrix3(0, 2) = 3.0;
    matrix3(1, 0) = 4.0;
    matrix3(1, 1) = 5.0;
    matrix3(1, 2) = 6.0;
    matrix3(2, 0) = 7.0;
    matrix3(2, 1) = 8.0;
    matrix3(2, 2) = 9.0;

    zeroMatrix = S21Matrix(2, 2);  // 2x2 матрица
    zeroMatrix(0, 0) = 0.0;
    zeroMatrix(0, 1) = 0.0;
    zeroMatrix(1, 0) = 0.0;
    zeroMatrix(1, 1) = 0.0;
  }
};

//конструкторы
TEST_F(S21MatrixTest, ConstructorWithNegativeRows) {
  ASSERT_THROW(S21Matrix(-1, 4), std::length_error);
}

TEST_F(S21MatrixTest, ConstructorWithNegativeCols) {
  ASSERT_THROW(S21Matrix(4, -1), std::length_error);
}

TEST_F(S21MatrixTest, ConstructorWithZeroRowsAndCols) {
  ASSERT_EQ(m.getRows(), 0);
  ASSERT_EQ(m.getCols(), 0);
}

TEST_F(S21MatrixTest, CopyConstructor) {
  S21Matrix copyMatrix(matrix1);
  ASSERT_EQ(copyMatrix.getRows(), matrix1.getRows());
  ASSERT_EQ(copyMatrix.getCols(), matrix1.getCols());
  ASSERT_FLOAT_EQ(copyMatrix(0, 0), matrix1(0, 0));
  ASSERT_FLOAT_EQ(copyMatrix(1, 1), matrix1(1, 1));
}

TEST_F(S21MatrixTest, MoveConstructor) {
  S21Matrix moveMatrix(std::move(matrix2));
  ASSERT_EQ(moveMatrix.getRows(), 2);
  ASSERT_EQ(moveMatrix.getCols(), 2);
  ASSERT_EQ(matrix2.getRows(), 0);  // matrix2 должен быть в состоянии "пустой"
  ASSERT_EQ(matrix2.getCols(), 0);
}

TEST_F(S21MatrixTest, Destructor) {
  {
    S21Matrix tempMatrix(2, 2);
    tempMatrix(0, 0) = 1.0;
  }  // tempMatrix выходит из области видимости
  ASSERT_NO_THROW(
      S21Matrix(2, 2));  // Проверяем, что деструктор не вызывает утечек памяти
}

TEST_F(S21MatrixTest, InitializationWithZeroSize) {
  ASSERT_NO_THROW(S21Matrix(0, 0));  // Проверка инициализации нулевой матрицы
}

TEST_F(S21MatrixTest, MatrixDataInitialization) {
  ASSERT_EQ(A(0, 0), 1.0);
  ASSERT_EQ(A(1, 1), 5.0);
  ASSERT_EQ(B(2, 1), 12.0);
}

TEST_F(S21MatrixTest, ZeroMatrixInitialization) {
  ASSERT_EQ(zeroMatrix(0, 0), 0.0);
  ASSERT_EQ(zeroMatrix(1, 1), 0.0);
}

// get и set
TEST_F(S21MatrixTest, GetRows) {
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix3.getRows(), 3);
}

TEST_F(S21MatrixTest, GetCols) {
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_EQ(matrix3.getCols(), 3);
}

TEST_F(S21MatrixTest, Get) {
  int rows, cols;
  matrix1.get(rows, cols);
  EXPECT_EQ(rows, 2);
  EXPECT_EQ(cols, 2);

  matrix3.get(rows, cols);
  EXPECT_EQ(rows, 3);
  EXPECT_EQ(cols, 3);
}

TEST_F(S21MatrixTest, SetRows) {
  matrix1.setRows(3);
  EXPECT_EQ(matrix1.getRows(), 3);
  matrix1.setRows(2);  // возвращаем обратно
  EXPECT_EQ(matrix1.getRows(), 2);
}

TEST_F(S21MatrixTest, SetCols) {
  matrix1.setCols(3);
  EXPECT_EQ(matrix1.getCols(), 3);
  matrix1.setCols(2);  // возвращаем обратно
  EXPECT_EQ(matrix1.getCols(), 2);
}

TEST_F(S21MatrixTest, Set) {
  matrix1.set(3, 4);
  EXPECT_EQ(matrix1.getRows(), 3);
  EXPECT_EQ(matrix1.getCols(), 4);
  matrix1.set(2, 2);  // возвращаем обратно
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);
}

// перегруз оператора =
// Тест на обычное присваивание
TEST_F(S21MatrixTest, AssignmentOperator_Regular) {
  S21Matrix result = matrix1;  // Копирование
  result = matrix2;            // Присваивание
  EXPECT_DOUBLE_EQ(result(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}

// Тест на самоприсваивание
TEST_F(S21MatrixTest, AssignmentOperator_SelfAssignment) {
  matrix1 = matrix1;  // Самоприсваивание
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 4.0);
}

// Тест на присваивание пустой матрицы
TEST_F(S21MatrixTest, AssignmentOperator_EmptyMatrix) {
  matrix1 = m;  // Присваивание пустой матрицы
  EXPECT_EQ(matrix1.getRows(), 0);
  EXPECT_EQ(matrix1.getCols(), 0);
}

// Тест на присваивание матрицы с данными
TEST_F(S21MatrixTest, AssignmentOperator_WithData) {
  matrix1 = matrix2;  // Присваивание
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 8.0);
}

// Тест на присваивание матрицы с разными размерами
TEST_F(S21MatrixTest, AssignmentOperator_DifferentSizes) {
  matrix(0, 0) = 10.0;
  matrix1 = matrix;  // Присваивание меньшей матрицы
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 10.0);
  EXPECT_EQ(matrix1.getRows(), 1);
  EXPECT_EQ(matrix1.getCols(), 1);
}

// перегруз оператора (), может использоваться для изменения значения
TEST_F(S21MatrixTest, AccessValidIndex) {
  // Проверка доступа к элементам по валидным индексам
  EXPECT_EQ(matrix3(0, 0), 1.0);
  EXPECT_EQ(matrix3(1, 1), 5.0);
  EXPECT_EQ(matrix3(2, 2), 9.0);
}

TEST_F(S21MatrixTest, ModifyValue) {
  // Проверка изменения значения элемента
  matrix3(1, 1) = 10.0;
  EXPECT_EQ(matrix3(1, 1), 10.0);
}

TEST_F(S21MatrixTest, AccessOutOfBoundsNegativeIndex) {
  // Проверка выхода за границы массива (отрицательный индекс)
  EXPECT_THROW(matrix3(-1, 0), std::out_of_range);
}

TEST_F(S21MatrixTest, AccessOutOfBoundsRowIndex) {
  // Проверка выхода за границы массива (индекс строки больше размера)
  EXPECT_THROW(matrix3(3, 0), std::out_of_range);
}

TEST_F(S21MatrixTest, AccessOutOfBoundsColumnIndex) {
  // Проверка выхода за границы массива (индекс столбца больше размера)
  EXPECT_THROW(matrix3(0, 3), std::out_of_range);
}

TEST_F(S21MatrixTest, AccessOutOfBoundsNegativeColumnIndex) {
  // Проверка выхода за границы массива (отрицательный индекс столбца)
  EXPECT_THROW(matrix3(0, -1), std::out_of_range);
}

//Вычитает из текущей матрицы другую
TEST_F(S21MatrixTest, SubtractSameDimensions) {
  // Проверка вычитания двух матриц одинаковых размеров
  matrix1.SubMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), -4);
  EXPECT_EQ(matrix1(0, 1), -4);
  EXPECT_EQ(matrix1(1, 0), -4);
  EXPECT_EQ(matrix1(1, 1), -4);
}

TEST_F(S21MatrixTest, SubtractDifferentDimensions) {
  // Создаем матрицу другого размера
  EXPECT_THROW(matrix1.SubMatrix(matrix3), std::invalid_argument);
}

TEST_F(S21MatrixTest, SubtractEmptyMatrix) {
  // Проверка вычитания пустой матрицы
  EXPECT_THROW(matrix1.SubMatrix(m), std::invalid_argument);
}

//Проверяет матрицы на равенство между собой
// Тест на равенство двух одинаковых матриц
TEST_F(S21MatrixTest, EqMatrix_SameMatrices_ReturnsTrue) {
  matrix2 = matrix1;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

// Тест на равенство двух разных матриц
TEST_F(S21MatrixTest, EqMatrix_DifferentMatrices_ReturnsFalse) {
  EXPECT_FALSE(matrix1.EqMatrix(matrix3));
}

// Тест на равенство матрицы с самой собой
TEST_F(S21MatrixTest, EqMatrix_SameMatrix_ReturnsTrue) {
  EXPECT_TRUE(matrix1.EqMatrix(matrix1));
}

// Тест на равенство матриц с одинаковыми значениями, но разными размерами
TEST_F(S21MatrixTest, EqMatrix_DifferentSizes_ReturnsFalse) {
  EXPECT_FALSE(matrix3.EqMatrix(matrix2));
}

// перегруз оператора ()

TEST_F(S21MatrixTest, AccessElement_ValidIndex) {
  EXPECT_DOUBLE_EQ(matrix3(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix3(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(matrix3(2, 2), 9.0);
}

TEST_F(S21MatrixTest, AccessElement_InvalidIndex_ThrowOutOfRange) {
  EXPECT_THROW(matrix3(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix3(3, 0), std::out_of_range);
  EXPECT_THROW(matrix3(0, -1), std::out_of_range);
  EXPECT_THROW(matrix3(0, 3), std::out_of_range);
}

TEST_F(S21MatrixTest, AccessElement_BoundaryIndex) {
  EXPECT_DOUBLE_EQ(matrix3(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix3(2, 2), 9.0);
}

//Создает новую транспонированную матрицу из текущей и возвращает ее
TEST_F(S21MatrixTest, SquareMatrix) {
  S21Matrix transposed = matrix1.Transpose();

  EXPECT_EQ(transposed(0, 0), 1.0);
  EXPECT_EQ(transposed(0, 1), 3.0);
  EXPECT_EQ(transposed(1, 0), 2.0);
  EXPECT_EQ(transposed(1, 1), 4.0);
}

TEST_F(S21MatrixTest, RectangularMatrix) {
  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;
  B(2, 0) = 5.0;
  B(2, 1) = 6.0;
  S21Matrix transposed = B.Transpose();

  EXPECT_EQ(transposed(0, 0), 1.0);
  EXPECT_EQ(transposed(0, 1), 3.0);
  EXPECT_EQ(transposed(0, 2), 5.0);
  EXPECT_EQ(transposed(1, 0), 2.0);
  EXPECT_EQ(transposed(1, 1), 4.0);
  EXPECT_EQ(transposed(1, 2), 6.0);
}

TEST_F(S21MatrixTest, EmptyMatrix) {
  S21Matrix transposed = m.Transpose();

  EXPECT_EQ(transposed.getRows(), 0);
  EXPECT_EQ(transposed.getCols(), 0);
}

// Находим минор матрицы
TEST_F(S21MatrixTest, MinorMatrix_ValidInput) {
  // Тестируем получение минорной матрицы, удаляя 1-ю строку и 1-й столбец
  S21Matrix minor = matrix3.minorMatrix(&matrix3, 0, 0);

  // Ожидаем, что минорная матрица будет равна:
  // 5 6
  // 8 9
  EXPECT_EQ(minor.getRows(), 2);
  EXPECT_EQ(minor.getCols(), 2);
  EXPECT_DOUBLE_EQ(minor(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(minor(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(minor(1, 0), 8.0);
  EXPECT_DOUBLE_EQ(minor(1, 1), 9.0);
}

TEST_F(S21MatrixTest, MinorMatrix_AnotherValidInput) {
  // Тестируем получение минорной матрицы, удаляя 2-ю строку и 2-й столбец
  S21Matrix minor = matrix3.minorMatrix(&matrix3, 1, 1);

  // Ожидаем, что минорная матрица будет равна:
  // 1 3
  // 7 9
  EXPECT_EQ(minor.getRows(), 2);
  EXPECT_EQ(minor.getCols(), 2);
  EXPECT_DOUBLE_EQ(minor(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(minor(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(minor(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(minor(1, 1), 9.0);
}

TEST_F(S21MatrixTest, MinorMatrix_InvalidInput) {
  // Тестируем поведение при недопустимом входе (например, выход за пределы
  // матрицы)
  EXPECT_THROW(matrix3.minorMatrix(&matrix3, 3, 0), std::out_of_range);
  EXPECT_THROW(matrix3.minorMatrix(&matrix3, 0, 3), std::out_of_range);
}

//Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
TEST_F(S21MatrixTest, CalcComplements_SquareMatrix) {
  // Ожидаем, что для квадратной матрицы будет вычислена матрица алгебраических
  // дополнений
  S21Matrix result = matrix1.CalcComplements();

  // Ожидаем, что результат будет равен [[4, -3], [-2, 1]]
  EXPECT_DOUBLE_EQ(result(0, 0), 4);
  EXPECT_DOUBLE_EQ(result(0, 1), -3);
  EXPECT_DOUBLE_EQ(result(1, 0), -2);
  EXPECT_DOUBLE_EQ(result(1, 1), 1);
}

TEST_F(S21MatrixTest, CalcComplements_NonSquareMatrix) {
  // Ожидаем, что вызов CalcComplements для неквадратной матрицы вызовет
  // исключение
  EXPECT_THROW(A.CalcComplements(), std::invalid_argument);
}

//Прибавляет вторую матрицу к текущей
TEST_F(S21MatrixTest, SumMatrix_SameDimensions) {
  // Сложение матриц одинакового размера
  matrix1.SumMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 6);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 8);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 10);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 12);
}

TEST_F(S21MatrixTest, SumMatrix_DifferentDimensions) {
  // Проверка на выброс исключения
  EXPECT_THROW(matrix1.SumMatrix(matrix3), std::invalid_argument);
}

//Вычисляет и возвращает определитель текущей матрицы
// Тест для случая, когда матрица 1x1
TEST_F(S21MatrixTest, Determinant1x1) {
  matrix(0, 0) = 5.0;
  EXPECT_DOUBLE_EQ(matrix.Determinant(), 5.0);
}

// Тест для случая, когда матрица 2x2
TEST_F(S21MatrixTest, Determinant2x2) {
  EXPECT_DOUBLE_EQ(matrix1.Determinant(), -2.0);
}

// Тест для случая, когда матрица 3x3
TEST_F(S21MatrixTest, Determinant3x3) {
  matrix3(2, 2) = 10.0;
  EXPECT_DOUBLE_EQ(matrix3.Determinant(), -3.0);
}

// Тест на выброс исключения для неквадратной матрицы
TEST_F(S21MatrixTest, DeterminantNonSquare) {
  EXPECT_THROW(A.Determinant(), std::invalid_argument);
}

// Тест для случая, когда матрица 4x4
TEST_F(S21MatrixTest, Determinant2x2Error) {
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 4.0;
  EXPECT_DOUBLE_EQ(matrix.Determinant(),
                   0.0);  // Определитель вырожденной матрицы
}

// тесты для InverseMatrix()
// Тест для обратной матрицы 1x1
TEST_F(S21MatrixTest, InverseMatrix_1x1) {
  matrix(0, 0) = 5.0;  // Определитель не равен 0

  S21Matrix inverse = matrix.InverseMatrix();
  EXPECT_DOUBLE_EQ(inverse(0, 0), 1.0 / 5.0);
}

// Тест для обратной матрицы 2x2
TEST_F(S21MatrixTest, InverseMatrix_2x2) {
  matrix1(0, 0) = 4.0;
  matrix1(0, 1) = 7.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 6.0;

  S21Matrix inverse = matrix1.InverseMatrix();
  EXPECT_DOUBLE_EQ(inverse(0, 0), 0.6);   // 1/determinant * (6)
  EXPECT_DOUBLE_EQ(inverse(0, 1), -0.7);  // 1/determinant * (-7)
  EXPECT_DOUBLE_EQ(inverse(1, 0), -0.2);  // 1/determinant * (-2)
  EXPECT_DOUBLE_EQ(inverse(1, 1), 0.4);   // 1/determinant * (4)
}

// Тест для исключения при нулевом определителе
TEST_F(S21MatrixTest, InverseMatrix_ZeroDeterminant) {
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 4.0;  // Определитель равен 0

  EXPECT_THROW(matrix1.InverseMatrix(), std::runtime_error);
}

//Проверка на равенство матриц
TEST_F(S21MatrixTest, EqualMatrices) {
  // Проверка, что равные матрицы действительно равны
  matrix2 = matrix1;
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST_F(S21MatrixTest, UnequalMatrices) {
  // Проверка, что разные матрицы не равны
  EXPECT_FALSE(matrix1 == matrix3);
}

TEST_F(S21MatrixTest, EqualMatricesWithSmallDifference) {
  // Проверка на равенство матриц с очень маленькой разницей
  S21Matrix matrix4 = S21Matrix(2, 2);
  matrix4(0, 0) = 1.0;
  matrix4(0, 1) = 2.0;
  matrix4(1, 0) = 3.0;
  matrix4(1, 1) = 4.0000001;  // очень маленькое отличие

  EXPECT_TRUE(matrix1 == matrix4);
}

TEST_F(S21MatrixTest, DifferentDimensions) {
  // Проверка на равенство матриц разных размеров
  S21Matrix matrix5 = S21Matrix(3, 3);  // 3x3 матрица
  EXPECT_FALSE(matrix1 == matrix5);
}

// Умножает текущую матрицу на число
TEST_F(S21MatrixTest, MulNumber_Positive) {
  // Умножение на положительное число
  matrix1.MulNumber(2.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 8.0);
}

TEST_F(S21MatrixTest, MulNumber_Negative) {
  // Умножение на отрицательное число
  matrix1.MulNumber(-1.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -2.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), -3.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), -4.0);
}

TEST_F(S21MatrixTest, MulNumber_Zero) {
  // Умножение на ноль
  matrix1.MulNumber(0.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 0.0);
}

// Тесты для оператора =
TEST_F(S21MatrixTest, AssignmentOperator_CopiesValues) {
  S21Matrix result = matrix1;  // Используем оператор присваивания
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST_F(S21MatrixTest, AssignmentOperator_HandlesMemory) {
  S21Matrix result = matrix1;  // Копируем матрицу
  result(0, 0) = 10.0;  // Изменяем значение в скопированной матрице
  EXPECT_NE(result(0, 0),
            matrix1(0, 0));  // Убедимся, что оригинальная матрица не изменилась
}

TEST_F(S21MatrixTest, AssignmentOperator_LargerMatrixToSmaller) {
  S21Matrix matrixSmaller(2, 2);
  matrixSmaller = matrix3;  // Присваиваем матрицу большего размера к меньшей
  EXPECT_DOUBLE_EQ(matrixSmaller.getRows(),
                   3);  // Проверяем, что размер матрицы изменился
  EXPECT_DOUBLE_EQ(matrixSmaller.getCols(), 3);
  EXPECT_DOUBLE_EQ(matrixSmaller(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrixSmaller(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(matrixSmaller(2, 2), 9.0);
}

// Тесты для оператора +

TEST_F(S21MatrixTest, AdditionOfTwoMatrices) {
  S21Matrix expected(2, 2);
  expected(0, 0) = 6.0;
  expected(0, 1) = 8.0;
  expected(1, 0) = 10.0;
  expected(1, 1) = 12.0;

  S21Matrix result = matrix1 + matrix2;

  // Проверка на равенство матриц (результат сложения)
  for (int i = 0; i < expected.getRows(); ++i) {
    for (int j = 0; j < expected.getCols(); ++j) {
      EXPECT_DOUBLE_EQ(expected(i, j), result(i, j));
    }
  }
}

// Тест для случая, когда размеры матриц не совпадают
TEST_F(S21MatrixTest, AdditionOfMatricesWithDifferentSizes) {
  S21Matrix differentSizeMatrix(3, 3);  // 3x3 матрица
  EXPECT_THROW(matrix1 + differentSizeMatrix, std::invalid_argument);
}

// Тесты для оператора -

TEST_F(S21MatrixTest, Subtraction) {
  S21Matrix result =
      matrix1 - matrix2;  // Ожидаем, что result будет равен (-4, -4, -4, -4)

  EXPECT_DOUBLE_EQ(result(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -4.0);
}

TEST_F(S21MatrixTest, Subtraction_DifferentDimensions) {
  S21Matrix matrix4 = S21Matrix(2, 3);  // 2x3 матрица
  EXPECT_THROW(matrix1 - matrix4, std::invalid_argument);
}

TEST_F(S21MatrixTest, Subtraction_ZeroMatrix) {
  S21Matrix result =
      matrix1 - zeroMatrix;  // Ожидаем, что result будет равен matrix1

  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

// Тест для случая, когда размеры матриц не совпадают
TEST_F(S21MatrixTest, SubtractionOfMatricesWithDifferentSizes) {
  S21Matrix differentSizeMatrix(3, 3);  // 3x3 матрица
  EXPECT_THROW(matrix1 - differentSizeMatrix, std::invalid_argument);
}

// Тесты для оператора +=
TEST_F(S21MatrixTest, AddMatrices_SameDimensions) {
  S21Matrix result = matrix1;  // Копируем matrix1 в result
  result += matrix2;  // Используем перегруженный оператор +=

  // Проверяем, что результат сложения верный
  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST_F(S21MatrixTest, AddMatrices_DifferentDimensions) {
  // Ожидаем, что будет выброшено исключение
  EXPECT_THROW(matrix1 += matrix3, std::invalid_argument);
}

// Тест на сложение с нулевой матрицей
TEST_F(S21MatrixTest, OperatorPlusEquals_ZeroMatrix) {
  matrix1 += zeroMatrix;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 4.0);
}

// Тест на сложение с самой собой
TEST_F(S21MatrixTest, OperatorPlusEquals_SelfAddition) {
  S21Matrix result = matrix1;
  result += matrix1;

  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}

// Тест на сложение с отрицательными значениями
TEST_F(S21MatrixTest, OperatorPlusEquals_NegativeValues) {
  S21Matrix negativeMatrix(2, 2);
  negativeMatrix(0, 0) = -1.0;
  negativeMatrix(0, 1) = -2.0;
  negativeMatrix(1, 0) = -3.0;
  negativeMatrix(1, 1) = -4.0;

  matrix1 += negativeMatrix;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 0.0);
}

// Тесты для оператора -=
TEST_F(S21MatrixTest, SubtractMatrices_ValidInput) {
  // Тест корректного выполнения операции -=
  matrix1 -= matrix2;
  EXPECT_DOUBLE_EQ(matrix1(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), -4.0);
}

TEST_F(S21MatrixTest, SubtractMatrices_EqualMatrices) {
  // Тест вычитания одинаковых матриц
  S21Matrix m = matrix1;
  m -= matrix1;
  EXPECT_DOUBLE_EQ(m(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 0.0);
}

TEST_F(S21MatrixTest, SubtractMatrices_DifferentDimensions) {
  // Тест на выброс исключения при разных размерах матриц
  EXPECT_THROW(matrix1 -= matrix3, std::invalid_argument);
}

TEST_F(S21MatrixTest, SubtractMatrices_EmptyMatrix) {
  // Тест вычитания матрицы из пустой матрицы
  zeroMatrix -= matrix1;
  EXPECT_DOUBLE_EQ(zeroMatrix(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(zeroMatrix(0, 1), -2.0);
  EXPECT_DOUBLE_EQ(zeroMatrix(1, 0), -3.0);
  EXPECT_DOUBLE_EQ(zeroMatrix(1, 1), -4.0);
}

// Тест на проверку оператора * на число
TEST_F(S21MatrixTest, MultiplyByScalar) {
  double scalar = 2.0;
  S21Matrix result = matrix1 * scalar;

  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}

TEST_F(S21MatrixTest, MultiplyByZero) {
  double scalar = 0.0;
  S21Matrix result = matrix1 * scalar;

  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}

TEST_F(S21MatrixTest, MultiplyByNegativeScalar) {
  double scalar = -1.0;
  S21Matrix result = matrix1 * scalar;

  EXPECT_DOUBLE_EQ(result(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -2.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -3.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -4.0);
}

TEST_F(S21MatrixTest, MultiplyByOne) {
  double scalar = 1.0;
  S21Matrix result = matrix1 * scalar;

  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

// Тест на проверку оператора *= на число
TEST_F(S21MatrixTest, TestOperatorMultiplyEquals) {
  // Умножаем матрицу на число
  double num = 2.0;
  matrix1 *= num;

  // Проверяем значения после умножения
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 8.0);
}

TEST_F(S21MatrixTest, TestOperatorMultiplyEqualsByZero) {
  // Умножаем матрицу на 0
  double num = 0.0;
  matrix1 *= num;

  // Проверяем значения после умножения на 0
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 0.0);
}

TEST_F(S21MatrixTest, TestOperatorMultiplyEqualsNegative) {
  // Умножаем матрицу на отрицательное число
  double num = -1.0;
  matrix1 *= num;

  // Проверяем значения после умножения на -1
  EXPECT_DOUBLE_EQ(matrix1(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -2.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), -3.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), -4.0);
}

// Тест на проверку оператора *= матрица

// Тест на корректное умножение двух матриц
TEST_F(S21MatrixTest, MultiplyMatrices) {
  A *= B;

  EXPECT_DOUBLE_EQ(A.getRows(), 2);

  EXPECT_DOUBLE_EQ(A(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 154.0);
}

// Тест на несовпадение размеров
TEST_F(S21MatrixTest, MultiplyMatricesSizeMismatch) {
  S21Matrix C(4, 2);
  // Инициализация матриц A и B

  EXPECT_THROW(A *= C, std::invalid_argument);
}

// Тест на умножение на нулевую матрицу
TEST_F(S21MatrixTest, MultiplyByZeroMatrix) {
  matrix1 *= zeroMatrix;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 0.0);
}

// Тест на работу с пустыми матрицами
TEST_F(S21MatrixTest, OperatorMultiplyAssignEmptyMatrix) {
  S21Matrix C;

  EXPECT_THROW(A *= C, std::invalid_argument);
}

// Тест на корректное умножение двух матриц
TEST_F(S21MatrixTest, MultiplyMatrices1) {
  S21Matrix res = A * B;

  EXPECT_DOUBLE_EQ(res.getRows(), 2);

  EXPECT_DOUBLE_EQ(res(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(res(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(res(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(res(1, 1), 154.0);
}

// Тест на несовпадение размеров
TEST_F(S21MatrixTest, MultiplyMatricesSizeMismatch1) {
  S21Matrix C(4, 2);
  // Инициализация матриц A и B

  EXPECT_THROW(A * C, std::invalid_argument);
}

// Тест на умножение на нулевую матрицу
TEST_F(S21MatrixTest, MultiplyByZeroMatrix1) {
  S21Matrix res = matrix1 * zeroMatrix;

  EXPECT_DOUBLE_EQ(res(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(res(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(res(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(res(1, 1), 0.0);
}

// Тест на работу с пустыми матрицами
TEST_F(S21MatrixTest, OperatorMultiplyAssignEmptyMatrix1) {
  S21Matrix C;
  EXPECT_THROW(A * C, std::invalid_argument);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
