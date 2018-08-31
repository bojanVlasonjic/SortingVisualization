#include "MyWindow.h"

void readFile(string putanja, vector<Flight> &letovi);
void writeToFile(string putanja, vector<Flight> &letovi);

MyWindow::MyWindow(Point xy, int w, int h, const string& title) :
	Window(xy, w, h, title),
	ucitButton(Point(x_max() - 100, 30), 70, 20, "Ucitaj", cb_ucitavanje),
	ucitavanjePushed(false),
	ulazPutanja(Point(x_max() - 350, 30), 200, 20, "Ulazna putanja:"),
	sortButton(Point(x_max() - 100, 90), 70, 30, "Sortiraj", cb_sortiranje),
	sortiranjePushed(false),
	kriterijumText(Point(x_max() - 400, 80), "Kriterijum: Destination/Departure/FlightNo/GateNo"),
	kriterijum(Point(x_max() - 350, 90), 200, 20, "Kriterijum sortiranja:"),
	algoritamText(Point(x_max() - 400, 130), "Algoritam: Selection sort/Quick sort"),
	algoritam(Point(x_max() - 350, 140), 200, 20, "Algoritam sortiranja:"),
	upisButton(Point(x_max() - 100, 200), 70, 20, "Upisi", cb_upisivanje),
	upisivanjePushed(false),
	izlazPutanja(Point(x_max() - 350, 200), 200, 20, "Izlazna putanja:"),
	prethodniRaspored(Point(x_max() - (x_max() - 110), 240), 800, 30, "Preth_raspored:"),
	trenutniRaspored( Point(x_max() - (x_max()-110) , 280), 800, 30, "Tren_raspored:"),
	slIterButton(Point(x_max() - 100, 330), 70, 20, "Sl_Iter", cb_slIter),
	slIterPushed(false),
	brIter(Point(x_max() - (x_max() - 110), 320), 30, 20, "Broj iteracije"),
	brPomer(Point(x_max() - (x_max() - 110), 340), 30, 20, "Broj pomeranja"),
	brPoredj(Point(x_max() - (x_max() - 110), 360), 30, 20, "Broj poredjenja")

{
	kriterijumText.set_font_size(12);
	algoritamText.set_font_size(12);
	kriterijumText.set_color(Color::black);
	algoritamText.set_color(Color::black);

	attach(ucitButton);
	attach(ulazPutanja);
	attach(kriterijumText);
	attach(kriterijum);
	attach(algoritamText);
	attach(algoritam);
	attach(sortButton);
	attach(upisButton);
	attach(izlazPutanja);
	attach(prethodniRaspored);
	attach(trenutniRaspored);
	attach(slIterButton);
	attach(brIter);
	attach(brPomer);
	attach(brPoredj);
}

void MyWindow::prikaz() {

	show();
	vector<Flight> letovi;
	vector<Flight> sortirajuciLetovi;
	int kritParam = 0;
	int algParam = 0;
	stack<pair<int, int>> stek;

	

	while (true) {

		slIterButton.hide();
		//upisButton.hide();

		ucitavanjePushed = false;
		sortiranjePushed = false;
		upisivanjePushed = false;
		slIterPushed = false;
	
		std::string putanja;
		SelectionSort s;
		QuickSort qs;
		std::string raspored;
		
		std::string krit;
		std::string alg;

		while (!ucitavanjePushed && !sortiranjePushed && !upisivanjePushed)
			Fl::wait();

		if (sortiranjePushed) {
			
			if (letovi.size() == 0) {
				printf("\n Niste ucitali podatke");
				continue;
			}
			
			krit = kriterijum.get_string();
			alg = algoritam.get_string();

			if (krit.compare("") == 0 || alg.compare("") == 0) {
				printf("\n Niste uneli odgovarajuc kriterijum ili algoritam");
				continue;
			}

			kritParam = proveriKriterijum(krit);

			if (kritParam == 0) {
				printf("\n Niste uneli odgovarajuc kriterijum");
				continue;
			}

			algParam = proveriAlgoritam(alg);

			if (algParam == 0) {
				printf("\n Niste uneli odgovarajuc algoritam");
				continue;
			}

			ucitButton.hide();
			sortButton.hide();
			slIterButton.show();
			upisButton.hide();
			prethodniRaspored.put("");
			slIterPodaci(letovi, kritParam, 0, 0, 0);
			sortirajuciLetovi = letovi;

			while (!slIterPushed) {
				Fl::wait();

				if (slIterPushed) {
					if (algParam == 1) {
						raspored = popuniRaspored(sortirajuciLetovi, kritParam);
						prethodniRaspored.put(raspored);
						s.sort(sortirajuciLetovi, kritParam);
						slIterPodaci(sortirajuciLetovi, kritParam, s.getNumIter(), s.getNumMoves(), s.getNumCmps());
						if (s.getNumIter() < sortirajuciLetovi.size() - 1) {
							slIterPushed = false;
						}
						else {
							slIterPushed = true;
							ucitButton.show();
							sortButton.show();
							upisButton.show();
							slIterButton.hide();
							s.resetNumCmps();
							s.resetNumIter();
							s.resetNumMoves();

						}


					}
					else if (algParam == 2) {
						raspored = popuniRaspored(sortirajuciLetovi, kritParam);
						prethodniRaspored.put(raspored);
						qs.sortiraj(sortirajuciLetovi, kritParam, stek);
						slIterPodaci(sortirajuciLetovi, kritParam, qs.getNumIter(), qs.getNumMoves(), qs.getNumCmps());

						if (!stek.empty()) {
							slIterPushed = false;
						}
						else {
							slIterPushed = true;
							ucitButton.show();
							sortButton.show();
							upisButton.show();
							slIterButton.hide();
							qs.resetNumCmps();
							qs.resetNumIter();
							qs.resetNumMoves();

						}

					}

				}

			}

		}


		if (ucitavanjePushed) {

			putanja = ulazPutanja.get_string();
			readFile(putanja, letovi);
			
		}

		if (upisivanjePushed) {
			putanja = izlazPutanja.get_string();
			writeToFile(putanja, sortirajuciLetovi);

		}


	}

}


void MyWindow::slIterPodaci(vector<Flight> &letovi, int kritParam, int brIt, int brPom, int brPor) {

	std::string raspored;
	raspored = popuniRaspored(letovi, kritParam);
	trenutniRaspored.put(raspored);
	brIter.put(brIt);
	brPomer.put(brPom);
	brPoredj.put(brPor);


}

int proveriKriterijum(std::string krit) {

	if (krit.compare("Destination") == 0 || krit.compare("destination") == 0)
		return 1;
	else if (krit.compare("Departure") == 0 || krit.compare("departure") == 0)
		return 2;
	else if (krit.compare("FlightNo") == 0 || krit.compare("flightNo") == 0 || krit.compare("flightno") == 0)
		return 3;
	else if (krit.compare("GateNo") == 0 || krit.compare("gateno") == 0 || krit.compare("gateNo") == 0)
		return 4;
	else
		return 0;

}

int proveriAlgoritam(std::string alg) {

	if (alg.compare("Selection sort") == 0 || alg.compare("selection sort") == 0)
		return 1;
	else if (alg.compare("Quick sort") == 0 || alg.compare("quick sort") == 0)
		return 2;
	else
		return 0;
}

std::string popuniRaspored(vector<Flight> letovi, int krit) {

	std::string linija;

	for (int i = 0; i < letovi.size(); i++) {
		
		switch (krit) {
			case 1:
				linija.append(letovi[i].getDestination());
				if (i != letovi.size()-1)
					linija.append("->");
				break;

			case 2:
				linija.append(letovi[i].getDeparture());
				if (i != letovi.size()-1)
					linija.append("->");
				break;

			case 3:
				linija.append(letovi[i].getFlightNo());
				if (i != letovi.size()-1)
					linija.append("->");
				break;

			case 4:
				linija.append(letovi[i].getGateNo());
				if (i != letovi.size()-1)
					linija.append("->");
				break;
		}

	}

	return linija;
}

void MyWindow::ucitavanje() {

	ucitavanjePushed = true;

}

void MyWindow::cb_ucitavanje(Address, Address rb) {

	reference_to<MyWindow>(rb).ucitavanje();

}

void MyWindow::sortiranje() {

	sortiranjePushed = true;

}

void MyWindow::cb_sortiranje(Address, Address rb) {

	reference_to<MyWindow>(rb).sortiranje();

}

void MyWindow::upisivanje() {

	upisivanjePushed = true;

}

void MyWindow::cb_upisivanje(Address, Address rb) {

	reference_to<MyWindow>(rb).upisivanje();

}

void MyWindow::slIter() {
	slIterPushed = true;
}

void MyWindow::cb_slIter(Address, Address rb) {

	reference_to<MyWindow>(rb).slIter();
}
