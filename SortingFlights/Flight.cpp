//============================================================================
// Name        : Flight.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of the Flight class
//============================================================================

#include "Flight.h"

Flight::Flight() {

}

Flight::Flight(std::string dest, std::string dep, std::string fn, std::string gn) : destination(dest), departure(dep), flightNo(fn), gateNo(gn) {


}

std::string Flight::getFlightNo() {

	return flightNo;
}

std::string Flight::getDeparture() {

	return departure;
}

std::string Flight::getDestination() {

	return destination;
}

std::string Flight::getGateNo() {

	return gateNo;
}

istream& operator >> (istream& in, Flight& f) {

	string dest;
	string dep;
	string fn;
	string gn;

	in >> dest >> dep >> fn >> gn;

	//kako bih uklonio ';' iz stringova
	f.destination = dest.substr(0, dest.size() - 1);
	f.departure = dep.substr(0, dep.size() - 1);
	f.flightNo = fn.substr(0, fn.size() - 1);
	f.gateNo = gn.substr(0, gn.size() - 1);
	

	return in;
}

ostream& operator<<(ostream& out, Flight f) {

	out << f.getDestination() << ";  " << f.getDeparture() << ";  " << f.getFlightNo() << ";  " << f.getGateNo() << ";" << endl;
	return out;

}


void Flight::toString() {

	cout << destination << " " << departure << " " << flightNo << " " << gateNo << endl;
}

int Flight::compare(int krit, Flight f) {

	int rezultat;

	switch (krit) {

	case 2:
		if (departure.length() < 5 || f.getDeparture().length() < 5) {
			rezultat = poredjenjeVreme(departure, f.getDeparture());
			return rezultat;
		}
		rezultat = poredjenje(departure, f.getDeparture());
		return rezultat;

	case 1:
		rezultat = poredjenje(destination, f.getDestination());
		return rezultat;
	
	case 3:
		rezultat = poredjenje(flightNo, f.getFlightNo());
		return rezultat;
		
	case 4:
		rezultat = poredjenje(gateNo, f.getGateNo());
		return rezultat;

	default:
		cout << "Pogresan parametar" << endl;
		return 0;

	}

	

}

int poredjenje(string s1, string s2) {

	if (s1 < s2)
		return 1;
	else if (s1 > s2)
		return -1;
	else
		return 0;
}

//U slucaju da je u text file-u vreme zadato u formatu 7:42, umesto 07:42
//Uvodim pretpostavku da je vreme uvek u formatu hh:mm ili h:mm
int poredjenjeVreme(string s1, string s2) {
	int rez;

	if (s1.at(0) == '0')
		s1 = s1.substr(1, s1.size() - 1);
	if (s2.at(0) == '0')
		s2 = s2.substr(1, s2.size() - 1);

	if (s1.length() < s2.length())
		rez = 1;
	else if (s1.length() > s2.length())
		rez = -1;
	else
		rez = poredjenje(s1, s2);

	return rez;
}