//============================================================================
// Name        : Flight.h
// Author      : Bojan Vlasonjic
// Date        : 30.12.2017.
// Copyright   : 
// Description :
//============================================================================
#pragma once
#include <string>
#include <iostream>

using namespace std;

class Flight
{
	// your definition goes here

public:

	Flight();
	Flight(std::string dest, std::string dep, std::string fn, std::string gn);

	std::string getFlightNo();
	std::string getDeparture();
	std::string getDestination();
	std::string getGateNo();

	int compare(int krit, Flight f);

	void toString();

	friend istream& operator >> (istream& in, Flight &f);
	

private:
	std::string destination;
	std::string departure;
	std::string flightNo;
	std::string gateNo;
};

ostream& operator<<(ostream& out, Flight f);
int poredjenje(string s1, string s2);
int poredjenjeVreme(string s1, string s2);