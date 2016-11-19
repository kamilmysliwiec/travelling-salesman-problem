#pragma once
#include <exception>
#include <algorithm>
#include <functional>

using std::exception;
using std::fill;
using std::function;

class GenPermutation
{
	public:
		GenPermutation(const int, const int, const int);
		~GenPermutation();

		void start(std::function<void(int *)>);
		 
	private: 
		void init(const int);
		void swap(int *, int *);  
		 
		int * c, * p, n, pos;
		bool *pr;
};

