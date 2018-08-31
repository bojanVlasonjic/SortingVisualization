//============================================================================
// Name        : main.cpp
// Author      :
// Date        :
// Copyrht   :
// Description :
//============================================================================

//C:\\Users\\bojan\\Desktop\\OOP2\\projekat\\src\\VS15\\inputFileExample.txt

#include <iostream>
#include "MyWindow.h"
#include "Graph.h"
#include <fstream>
#include <string>
#include "Flight.h"
#include <vector>
#include "Sort.h"

using namespace std;


/*function readFile
  params: string putanja - putanja do odgovarajuceg ulaznog fajla
  descr: Ucita podatke iz ulaznog fajla kao objekte klase Flight, i ubaci ih u 'vektor<Flight> letovi'
*/
void readFile(string putanja, vector<Flight> &letovi) {
		
	letovi.clear(); //u slucaju da korisnik odabere opciju ucitavanja nekoliko puta

	ifstream ifs(putanja);

	if (!ifs) {
		cout << "Nije ucitan fajl" << endl;
		return;
	}

	Flight f;

	string header;
	getline(ifs, header); //ignorisem zaglavlje

	while (ifs >> f) {

		f.toString();
		letovi.push_back(f);

	}

	ifs.close();

}

void writeToFile(string putanja, vector<Flight> &letovi) {

	if (letovi.size() == 0) {

		printf("Niste ucitali podatke iz ulaznog file-a");
		return;
	}

	ofstream ofs(putanja);

	if (!ofs) {
		printf("Niste uneli odgovarajucu putanju.");
		return;
	}

	vector<Flight>::iterator it;

	for (it = letovi.begin(); it != letovi.end(); it++) {

		ofs << *it;

	}

	ofs.close();

}


int main()
{
	
	MyWindow win(Point(50, 50), 1000, 600, "Meni");
	win.prikaz();
	return gui_main();
	

}



