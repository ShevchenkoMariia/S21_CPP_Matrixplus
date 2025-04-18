#include "s21_matrix_oop.h"

// Параметризированный конструктор с количеством строк и столбцов.
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw length_error("Matrix size must be greater or equal than 0");
  }
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = (double*)calloc(cols_, sizeof(double));
  }
}

// Конструктор копирования.
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Конструктор переноса.
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(other.matrix_) {  // noexcept - не генерирунтся никаких исключений
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

// Деструктор
S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

/*
 * Реализуй доступ к приватным полям `rows_` и `cols_` через accessor и mutator.
 * При увеличении размера матрица дополняется нулевыми элементами, при
 * уменьшении лишнее просто отбрасывается.
 */

// accessor
int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }

void S21Matrix::get(int& rows, int& cols) const {
  rows = getRows();
  cols = getCols();
}

// mutator
void S21Matrix::setRows(int rows) {
  if (rows != rows_) {
    S21Matrix newMatrix(rows, cols_);
    int countRows = (rows > rows_) ? rows_ : rows;
    for (int i = 0; i < countRows; i++) {
      for (int j = 0; j < cols_; j++) {
        newMatrix.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = newMatrix;
  }
}

void S21Matrix::setCols(int cols) {
  if (cols != cols_) {
    S21Matrix newMatrix(rows_, cols);
    int countCols = (cols > cols_) ? cols_ : cols;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < countCols; j++) {
        newMatrix.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = newMatrix;
  }
}

void S21Matrix::set(int rows, int cols) {
  if (rows != rows_) this->setRows(rows);
  if (cols != cols_) this->setCols(cols);
}

//перегруз оператора =
const S21Matrix& S21Matrix::operator=(
    const S21Matrix& other) {  //проверить слово конст
  if (this == &other) return *this;
  if (matrix_ != NULL) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

//перегруз оператора +
S21Matrix S21Matrix::operator+(
    const S21Matrix& right) const {  //проверить const
  //условие что строки и столбики равны
  if (rows_ != right.rows_ || cols_ != right.cols_) {
    throw std::invalid_argument(
        "Error: Matrices must have the same dimensions");
  }
  S21Matrix sumMatrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      sumMatrix.matrix_[i][j] = matrix_[i][j] + right.matrix_[i][j];
    }
  }
  return sumMatrix;
}

//перегруз оператора +=
const S21Matrix& S21Matrix::operator+=(const S21Matrix& right) {
  //условие что строки и столбики равны
  if (rows_ != right.rows_ || cols_ != right.cols_) {
    throw std::invalid_argument(
        "Error: Matrices must have the same dimensions");
  }
  return *this = *this + right;
}

//перегруз оператора -
S21Matrix S21Matrix::operator-(
    const S21Matrix& right) const {  //проверить const
  //условие что строки и столбики равны
  if (rows_ != right.rows_ || cols_ != right.cols_) {
    throw std::invalid_argument(
        "Error: Matrices must have the same dimensions");
  }
  S21Matrix subMatrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      subMatrix.matrix_[i][j] = matrix_[i][j] - right.matrix_[i][j];
    }
  }
  return subMatrix;
}

//перегруз оператора -=
const S21Matrix& S21Matrix::operator-=(const S21Matrix& right) {
  //условие что строки и столбики равны
  if (rows_ != right.rows_ || cols_ != right.cols_) {
    throw std::invalid_argument(
        "Error: Matrices must have the same dimensions");
  }
  return *this = *this - right;
}

//перегруз оператора * на число
S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix mulNumber(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      mulNumber.matrix_[i][j] = matrix_[i][j] * num;
    }
  }
  return mulNumber;
}

//перегруз оператора *= на число
const S21Matrix& S21Matrix::operator*=(const double num) {
  return *this = *this * num;
}

//перегруз оператора * матриц
S21Matrix S21Matrix::operator*(const S21Matrix& right) const {
  //Число столбцов первой матрицы не равно числу строк второй матрицы
  if (cols_ != right.rows_) {
    throw std::invalid_argument(
        "Error: the number of columns in the first matrix is not equal to the "
        "number of rows in the second matrix");
  }
  S21Matrix multMatrix(rows_, right.cols_);
  for (int i = 0; i < multMatrix.rows_; i++) {
    for (int j = 0; j < multMatrix.cols_; j++) {
      for (int a = 0; a < cols_; a++) {
        multMatrix.matrix_[i][j] += matrix_[i][a] * right.matrix_[a][j];
      }
    }
  }
  return multMatrix;
}

//перегруз оператора *= матрицы
const S21Matrix& S21Matrix::operator*=(const S21Matrix& right) {
  //Число столбцов первой матрицы не равно числу строк второй матрицы
  if (cols_ != right.rows_) {
    throw std::invalid_argument(
        "Error: the number of columns in the first matrix is not equal to the "
        "number of rows in the second matrix");
  }
  return *this = *this * right;
}

//Проверка на равенство матриц
bool S21Matrix::operator==(const S21Matrix& right) const {
  //Число столбцов и строк равны
  if (rows_ != right.rows_ || cols_ != right.cols_) {
    return false;
  }
  bool result = 1;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - right.matrix_[i][j]) > 0.000001) {
        result = 0;
        break;
      }
    }
  }
  return result;
}

// перегруз оператора (), используется для доступа к элементам без изменения их
// значений
double S21Matrix::operator()(int i, int j) const {
  //выход за границы массива
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Error: index outside the matrix");
  }
  return matrix_[i][j];
}

// перегруз оператора (), может использоваться для изменения значения
double& S21Matrix::operator()(int i, int j) {
  //выход за границы массива
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Error: index outside the matrix");
  }
  return this->matrix_[i][j];
}

void S21Matrix::print() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      printf("%f ", matrix_[i][j]);
    }
    printf("\n");
  }
}

// заполнение матрицы рандомными числами от 0 до 10
void S21Matrix::randomFilling() {
  srand(time(0));
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = rand() % 10;
    }
  }
}

//Прибавляет вторую матрицу к текущей | различная размерность матриц.
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Error: Matrices must have the same dimensions");
  }
  *this = *this + other;
}

//Вычитает из текущей матрицы другую | различная размерность матриц.
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Error: Matrices must have the same dimensions");
  }
  *this = *this - other;
}

//Умножает текущую матрицу на вторую. | число столбцов первой матрицы не равно
//числу строк второй матрицы.
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Error: the number of columns in the first matrix is not equal to the "
        "number of rows in the second matrix");
  }
  *this = *this * other;
}

//Проверяет матрицы на равенство между собой
bool S21Matrix::EqMatrix(const S21Matrix& other) { return *this == other; }

//Умножает текущую матрицу на число.
void S21Matrix::MulNumber(const double num) { *this = *this * num; }

//Создает новую транспонированную матрицу из текущей и возвращает ее.
S21Matrix S21Matrix::Transpose() {
  S21Matrix trMatrix(cols_, rows_);
  for (int i = 0; i < trMatrix.rows_; i++) {
    for (int j = 0; j < trMatrix.cols_; j++) {
      trMatrix.matrix_[i][j] = matrix_[j][i];
    }
  }
  return trMatrix;
}

//Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее. |
//Матрица не является квадратной.
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Error: matrix is not square");
  }
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < res.rows_; i++) {
    for (int j = 0; j < res.cols_; j++) {
      S21Matrix submatrix = minorMatrix(this, i, j);
      double determinant = submatrix.Determinant();
      if ((i + j) % 2 != 0) determinant *= -1;
      res.matrix_[i][j] = determinant;
    }
  }
  return res;
}

//Вычисляет и возвращает определитель текущей матрицы. | Матрица не является
//квадратной.
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Error: matrix is not square");
  }
  double det = 0.0;
  if (rows_ == 1) {
    det = matrix_[0][0];
  } else if (rows_ == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else if (rows_ > 2) {
    int rowDel = 0;
    for (int i = 0; i < cols_; i++) {
      S21Matrix submatrix = minorMatrix(this, rowDel, i);
      double determinant = submatrix.Determinant();
      if (i % 2 != 0) {
        determinant *= -1.0;
      }
      det += matrix_[0][i] * determinant;
    }
  }
  return det;
}

// Находим минор матрицы
S21Matrix S21Matrix::minorMatrix(S21Matrix* A, int rowDel, int colDel) {
  if (rowDel >= A->rows_ || colDel >= A->cols_) {
    throw std::out_of_range("Error: Row or column index is out of range");
  }

  S21Matrix submatrix(A->rows_ - 1, A->cols_ - 1);
  // Заполняем подматрицу
  for (int i = 0, a = 0; i < submatrix.rows_; i++, a++)
    for (int j = 0, b = 0; j < submatrix.cols_; j++, b++) {
      if (a == rowDel) a++;
      if (b == colDel) b++;
      submatrix.matrix_[i][j] = A->matrix_[a][b];
    }
  return submatrix;
}

//Вычисляет и возвращает обратную матрицу. | Определитель матрицы равен 0.
S21Matrix S21Matrix::InverseMatrix() {
  double determinant = this->Determinant();
  if (determinant == 0)
    throw std::runtime_error("Error: Determinant is equal to 0");

  S21Matrix res;
  if (rows_ == 1) {
    S21Matrix res1(rows_, cols_);
    res1.matrix_[0][0] = 1.0 / matrix_[0][0];
    res = res1;
  } else {
    S21Matrix calcCompl(this->CalcComplements());
    S21Matrix transpose(calcCompl.Transpose());
    transpose.MulNumber(1.0 / determinant);
    res = transpose;
  }
  return res;
}
