#pragma once
#include <stdexcept>
#include <iostream>

using namespace std; 

class Matrix
{
	public:
		Matrix(const int);
		~Matrix();

		void set(const unsigned int, const unsigned int, const double);
		double get(const unsigned int, const unsigned int) const;
		void show() const;

	private:
		double ** matrix;
		int size;
};