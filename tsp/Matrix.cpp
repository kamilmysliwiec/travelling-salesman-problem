#include "Matrix.h"

Matrix::Matrix(const int size) : size(size)
{
	if (size <= 0) throw exception("");

	matrix = new double*[size];
	for (int i = 0; i < size; i++)
		matrix[i] = new double[size];
}

Matrix::~Matrix()
{
	for (int i = 0; i < size; i++)
		delete[] matrix[i];

	delete[] matrix;
}

void Matrix::set(const unsigned int row, const unsigned col, const double val)
{
	if (row >= size || col >= size)
		throw out_of_range("Out of range");

	matrix[row][col] = val;
}

double Matrix::get(const unsigned int r, const unsigned int c) const
{
	if (r >= size || c >= size)
		throw out_of_range("Out of range");

	return matrix[r][c];
}

void Matrix::show() const
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cout << matrix[i][j] << endl;
}