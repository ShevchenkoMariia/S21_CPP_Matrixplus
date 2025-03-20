#ifndef _S21_MATRIX_OOP_H_
#define _S21_MATRIX_OOP_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdexcept>

using namespace std;

class S21Matrix {
    private:
        // Attributes
        int rows_, cols_;         // Rows and columns
        double **matrix_;         // Pointer to the memory where the matrix is allocated

    public:
        S21Matrix(): rows_(0), cols_(0), matrix_(nullptr) {} // Дефолтный конструктор.
        S21Matrix(int rows, int cols); // Параметризированный конструктор (строи и столбцы).
	S21Matrix(const S21Matrix& other); // Конструктор копирования.
        S21Matrix(S21Matrix&& other) noexcept;  // Конструктор переноса.

        ~S21Matrix(); // Деструктор.

	// Accessor
        void get(int& rows, int& cols) const;
	int getRows() const;
	int getCols() const;

	// Mutator
	void set(int rows, int cols);
	void setRows(int rows);
	void setCols(int cols);

        // перегруз операторов
        const S21Matrix& operator=(const S21Matrix& other); //пересмотреть
        S21Matrix operator+(const S21Matrix& right) const;
        S21Matrix operator-(const S21Matrix& right) const;
        S21Matrix operator*(const S21Matrix& right) const;
	S21Matrix operator*(const double num);
	double operator() (int i, int j) const;
	double& operator() (int i, int j);
        bool operator==(const S21Matrix& right) const;
	const S21Matrix& operator+=(const S21Matrix& right);
	const S21Matrix& operator-=(const S21Matrix& right);
	const S21Matrix& operator*=(const S21Matrix& right);
	const S21Matrix& operator*=(const double num);

        bool EqMatrix(const S21Matrix& other); // Проверяет матрицы на равенство между собой.
        void SumMatrix(const S21Matrix& other); // Прибавляет вторую матрицу к текущей.
        void SubMatrix(const S21Matrix& other); // Вычитает из текущей матрицы другую.
        void MulNumber(const double num); // Умножает текущую матрицу на число.
        void MulMatrix(const S21Matrix& other); // Умножает текущую матрицу на вторую.
        S21Matrix Transpose(); // Создает новую транспонированную матрицу из текущей и возвращает ее.
        S21Matrix CalcComplements(); // Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее.
        S21Matrix InverseMatrix(); //Вычисляет и возвращает обратную матрицу.
        double Determinant(); //Вычисляет и возвращает определитель текущей матрицы.

	/*Вспомагательные функции*/

	S21Matrix minorMatrix(S21Matrix* A, int rowDel, int colDel); // Минор матрицы.
	void randomFilling(); // рандомное заполнение матрицы числами от 0 до 10;
        void print(); // Вывод матрицы.
};
#endif
