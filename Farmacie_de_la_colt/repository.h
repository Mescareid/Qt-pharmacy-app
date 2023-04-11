#pragma once
#include <vector>
#include <ostream>
#include "entities.h"

using std::vector;
using std::ostream;

class ExceptieRepository {
private:
	string mesaj;
public:
	ExceptieRepository(const string mesaj) : mesaj{ mesaj } {}

	string getRepositoryMesaj() const {
		return this->mesaj;
	}
};

class Repository {
private:
	vector<Medicament> ListaMedicamente;

	vector<Medicament> Reteta;

	bool ExistaInLista(const Medicament& medicament) const;

public:
	Repository() = default;

	virtual ~Repository() = default;

	bool VerificaExistentaID(const int id) const;

	virtual void Adauga(const Medicament& medicament);

	void AdaugaInReteta(const size_t id);

	void AdaugaRandomInReteta(const int medicamente_de_adaugat);

	void GolesteReteta() noexcept;

	size_t DimensiuneReteta() noexcept;

	virtual void Sterge(const int id);

	virtual void Modifica(const int id, const Medicament& medicament);

	virtual const Medicament& CautaMedicament(int id) const;

	size_t DimensiuneLista() noexcept;

	const vector<Medicament>& ReturneazaListaDinRepository() const noexcept {
		return this->ListaMedicamente;
	}

	const vector<Medicament>& ReturneazaRetetaDinRepository() const noexcept {
		return this->Reteta;
	}
};

void testeReteta();

void testeRepository();