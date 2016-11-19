#include "TSPSolver.h"

TSPSolver::TSPSolver(const string name)
	: fileName(name), matrix(NULL), n(0)
{
	bestRoute.cost = -1;
	bestRoute.tab = NULL;
}

TSPSolver::~TSPSolver()
{
	this->restart();
}

void TSPSolver::restart()
{
	bestRoute.cost = -1;

	if (matrix != NULL) delete matrix;
	if (bestRoute.tab != NULL) delete[] bestRoute.tab;
}

void TSPSolver::runParallel()
{
	Route route;
	const int pos = 2;

#pragma omp parallel num_threads(n - 1) private(route) shared(pos)
	{
		try
		{
			route.cost = -1;
			route.tab = new int[n + 1];

			int id = omp_get_thread_num() + 1;
			GenPermutation generator(n, pos, id);
			generator.start([&](int * p) -> void {
				costCalculate(p, &route);
			});

#pragma omp critical
			{
				if ((bestRoute.cost > route.cost) || bestRoute.cost == -1)
				{
					bestRoute.tab = route.tab;
					bestRoute.cost = route.cost;
				}
			}
		}
		catch (exception & e)
		{
			cout << "Exception: " << e.what() << endl;
			cout << "Thread no. " << omp_get_thread_num();
		}
	}
}

void TSPSolver::costCalculate(const int * const p, Route * const pRoute)
{
	double cost = 0.0;
	bool isPossible = true;
	for (int i = 0; i < n; i++)
	{
		double next = matrix->get(p[i], p[i + 1]);
		if (next == 0)
		{
			isPossible = false;
			break;
		}
		cost += next;
	}
	if (((cost < pRoute->cost) && isPossible) || pRoute->cost == -1)
	{
		copy(p, p + n + 1, pRoute->tab);
		pRoute->cost = cost;
	}
}

void TSPSolver::runSequential()
{
	bestRoute.tab = new int[n + 1];

	GenPermutation generator(n, 1, 0);
	generator.start([&](int * p) -> void {
		costCalculate(p, &bestRoute);
	});
}


void TSPSolver::show() const
{
	cout << "Best route: ";
	for (int i = 0; i < n + 1; i++)
		cout << bestRoute.tab[i] << " ";

	cout << endl << "Cost: " << bestRoute.cost << endl;
}

void TSPSolver::solve(const bool seq = false)
{
	ifstream file(fileName, ios::in);
	if (!file.is_open())
		throw exception("Unable to open file.");

	int size, row = 0, col = 0;
	file >> size;
	matrix = new Matrix(size);

	while (!file.eof())
	{
		double val;

		file >> val;
		(*matrix).set(row, col % size, val);

		++col;
		if (col % size == 0)
			if (++row == size) break;
	}
	n = size;
	file.close();

	if (seq) runSequential();
	else runParallel();
}
