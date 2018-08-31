//============================================================================
// Name        : Sort.h
// Author      : 
// Date        :
// Copyright   : 
// Description : Sort interface class and various sorting algorithms in C++
//============================================================================
#pragma once

#include "Flight.h"
#include <vector>
#include "MyWindow.h"
#include <stack>


// Sort class
class Sort
{
protected:
	// number of comparisons performed in sort function
	unsigned long num_cmps = 0; //broj poredjenja
	unsigned long num_iter = 0; //broj iteracije
	unsigned long num_moves = 0; //broj pomeranja
public:
	// main entry point
	virtual void sort(std::vector<Flight>& data, int krit) = 0;
	// returns number of comparisons
	unsigned long getNumCmps();
	// resets the number of comparisons
	void resetNumCmps();

	unsigned long getNumIter();
	void resetNumIter();

	unsigned long getNumMoves();
	void resetNumMoves();
};

// SelectionSort class
class SelectionSort : public Sort
{
public:
	// main entry point
	void sort(std::vector<Flight>& data, int krit);
};

class QuickSort : public Sort {

public:
	void swap(Flight* f1, Flight* f2);
	int partition(vector<Flight> &data, int low, int high, int krit);
	void sort(vector<Flight> &data, int krit);
	void sortiraj(vector<Flight> &data, int krit, stack<pair<int, int>> &stek);
};

