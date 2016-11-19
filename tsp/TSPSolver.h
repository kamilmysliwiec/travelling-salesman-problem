#pragma once
#include <omp.h> 
#include <fstream> 
#include <string>
#include "Matrix.h"
#include "GenPermutation.h"
#include "Route.h"

using std::string;

class TSPSolver
{
	public:
		TSPSolver(const string);
		~TSPSolver();

		void show() const;
		void solve(const bool);
		void runParallel();
		void runSequential();
		 
		void restart();
		void costCalculate(const int * const, Route * const);

	private:
		string fileName;
		Matrix * matrix;
		Route bestRoute;
		int n;
};