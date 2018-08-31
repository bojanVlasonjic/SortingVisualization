#pragma once

#include "Window.h"
#include "GUI.h"
#include <string>
#include "Sort.h"

using namespace Graph_lib;



class MyWindow: public Window {

public:
	MyWindow(Point xy, int w, int h, const string& title);
	void prikaz();
	void slIterPodaci(vector<Flight> &letovi, int kritParam, int brIter, int brPomer, int brPoredj);

private:
	
	Button ucitButton;
	In_box ulazPutanja;

	Text kriterijumText;
	Text algoritamText;

	Button sortButton;
	In_box kriterijum;
	In_box algoritam;

	Button upisButton;
	In_box izlazPutanja;

	Button slIterButton;

	Out_box prethodniRaspored;
	Out_box trenutniRaspored;

	Out_box brIter;
	Out_box brPoredj;
	Out_box brPomer;

	bool ucitavanjePushed;
	static void cb_ucitavanje(Address, Address ); // veza izmedju dugmeta i akcije
	void ucitavanje(); //akcija kada se dugme pritisne
	
	bool sortiranjePushed;
	static void cb_sortiranje(Address, Address);
	void sortiranje();
	
	bool upisivanjePushed;
	static void cb_upisivanje(Address, Address);
	void upisivanje();

	bool slIterPushed;
	static void cb_slIter(Address, Address);
	void slIter();


};

int proveriKriterijum(std::string krit);
int proveriAlgoritam(std::string alg);
std::string popuniRaspored(vector<Flight> letovi, int krit);

