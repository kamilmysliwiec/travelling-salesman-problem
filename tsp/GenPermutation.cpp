#include "GenPermutation.h"

GenPermutation::GenPermutation(const int n, const int pos, const int id) : n(n), pos(pos)
{
	if (n <= 0 || pos < 0) throw exception("");
	
	c = new int[n];
	pr = new bool[n];
	p = new int[n + 1];
	
	init(id);
}

void GenPermutation::init(const int id)
{
	p[n] = 0;
	for (int i = 0; i < n; i++) p[i] = i;

	fill(pr, pr + n, true);
	fill(c, c + n, pos);
	c[n - 1] = 0;

	if (id > 1)
	{
		swap(&p[id], &p[1]);
	}
} 

void GenPermutation::start(std::function<void(int *)> costCalculate)
{
	int x, i = pos; costCalculate(p);
	int k_pos = pos > 1 ? pos : pos - 1;
	while (i < n - 1) 
	{
		i = pos;
		x = 0;
		while (c[i] == n - 1 - i + pos) 
		{
			pr[i] = !pr[i];
			c[i] = pos;
			if (pr[i]) x++;
			i++;
		}
		if (i < n - 1)
		{
			int k;
			if (pr[i]) k = c[i] + x;
			else k = n - i + k_pos - c[i] + x;

			swap(&p[k], &p[k + 1]);
			costCalculate(p);
			c[i] = c[i] + 1;
		}
	}
}

void GenPermutation::swap(int * a, int * b)
{
	int pom = *a;
	*a = *b; 
	*b = pom;
} 

GenPermutation::~GenPermutation()
{
	delete[] c;
	delete[] p;
	delete[] pr;
}
