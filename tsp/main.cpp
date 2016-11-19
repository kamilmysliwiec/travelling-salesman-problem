#include <stdio.h>
#include <conio.h>
#include <iomanip>   
#include "TSPSolver.h"

int main()
{
	cin.get();
	cin.get();
	try
	{
		TSPSolver tsp("we11.txt"); 

		double time = omp_get_wtime();

		cout << "       Parallel: " << endl;
		tsp.solve(false);
		tsp.show();

		cout << "       " << omp_get_wtime() - time << "s" << endl << endl;
		tsp.restart();

		time = omp_get_wtime(); 
		cout << "       Sequential: " << endl;
		tsp.solve(true);
		tsp.show();

		cout << "       " << omp_get_wtime() - time << "s" << endl;
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}
	cin.get();
	return 0;
}

