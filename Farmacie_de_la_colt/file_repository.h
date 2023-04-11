#pragma once
#include "repository.h"

using std::string;

class RepositoryFile : public Repository {
private:
	string nume_fisier;

	void ScrieInFisier();

	void CitesteDinFisier();

public:
	RepositoryFile(string nume_fisier) : Repository(), nume_fisier{ nume_fisier } {
		CitesteDinFisier();
	}

	void Adauga(const Medicament& medicament) override {
		Repository::Adauga(medicament);
		ScrieInFisier();
	}

	void Sterge(const int id) override {
		Repository::Sterge(id);
		ScrieInFisier();
	}

	void Modifica(const int id, const Medicament& medicament) override {
		Repository::Modifica(id, medicament);
		ScrieInFisier();
	}
};