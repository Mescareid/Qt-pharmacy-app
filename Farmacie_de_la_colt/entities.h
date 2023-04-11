#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Medicament {
private:
	int id = 0;
	string denumire;
	double pret = 0;
	string producator;
	string substanta_activa;

public:
	Medicament(const int& id, const string& denumire, const double& pret, const string& producator, const string& substanta_activa) :
		id{ id }, denumire{ denumire }, pret{ pret }, producator{ producator }, substanta_activa{ substanta_activa }{}

	Medicament(const Medicament& medicament) :id{ medicament.id }, denumire{ medicament.denumire }, pret{ medicament.pret },
		producator{ medicament.producator }, substanta_activa{ medicament.substanta_activa } {}

	Medicament() = default;

	int getId() const noexcept {
		return this->id;
	}

	string getDenumire() const {
		return this->denumire;
	}

	double getPret() const noexcept {
		return this->pret;
	}

	string getProducator() const {
		return this->producator;
	}

	string getSubstanta() const {
		return this->substanta_activa;
	}

	Medicament& operator=(const Medicament& medicament);
};

void testeDomain();
