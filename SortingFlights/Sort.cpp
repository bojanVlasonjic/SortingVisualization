//============================================================================
// Name        : Sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of the sort classes
//============================================================================

#include "Sort.h"

using namespace std;


void SelectionSort::sort(std::vector<Flight>& letovi, int krit) {

	int minIndex;
	int rez;
	Flight temp;

		for (int i = num_iter; i < letovi.size() - 1; i++) {

			num_iter++;
			minIndex = i;

			for (int j = i + 1; j < letovi.size(); j++) {

				num_cmps++;
				rez = letovi[j].compare(krit, letovi[minIndex]);

				if (rez > 0)
					minIndex = j;

			}

			if (minIndex != i) {
				num_moves++;
				temp = letovi[i];
				letovi[i] = letovi[minIndex];
				letovi[minIndex] = temp;
			}

			return;
			
		}

		
}


void QuickSort::swap(Flight* f1, Flight* f2) {

	Flight temp = *f1;
	*f1 = *f2;
	*f2 = temp;
}

int QuickSort::partition(vector<Flight> &letovi, int start, int end, int krit) {

	Flight pivot = letovi[end]; 
	int pIndex = start;
	int rez;

	for (int j = start; j < end ; j++)
	{

		rez = letovi[j].compare(krit, pivot);
		num_cmps++;
		if (rez > 0)
		{
			num_moves++;
			swap(&letovi[j], &letovi[pIndex]);
			pIndex++;
			
		}
	}
	
	swap(&letovi[pIndex], &letovi[end]);
	return pIndex;

}


void QuickSort::sort(vector<Flight> &letovi, int krit)  {
	
}

void QuickSort::sortiraj(vector<Flight> &letovi, int krit, stack<pair<int, int>> &stek) {

	int start = num_iter;
	int end = letovi.size()-1;

	if(stek.empty())
		stek.push(make_pair(start, end));

	while (!stek.empty()) {
		num_iter++;
		start = stek.top().first;
		end = stek.top().second;
		stek.pop();

		int pivot = partition(letovi, start, end, krit);

		if (pivot - 1 > start)
			stek.push(make_pair(start, pivot - 1));

		if (pivot + 1 < end)
			stek.push(make_pair(pivot + 1, end));

		return;
	}

}



unsigned long Sort::getNumCmps() {

	return num_cmps;

}

unsigned long Sort::getNumIter() {

	return num_iter;
}

unsigned long Sort::getNumMoves() {

	return num_moves;
}

void Sort::resetNumCmps() {

	num_cmps = 0;
}

void Sort::resetNumIter() {

	num_iter = 0;
}

void Sort::resetNumMoves() {

	num_moves = 0;
}