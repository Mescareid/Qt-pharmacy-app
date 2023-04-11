#pragma once

#include "entities.h"
#include "repository.h"
#include "validator.h"
#include "undo.h"
#include "Observer.h"
#include <memory>

using std::unique_ptr;

class Service : public Observable{
private:
	Repository& repository;
	Validator& validator;

	std::vector<unique_ptr<ActiuneUndo>> ActiuniUndo;

public:
	Service(Repository& repo, Validator& valid) noexcept : repository{ repo }, validator{ valid } {}

	void AdaugaMedicament(const int id, const string denumire, double pret, string producator, string substanta);

	void StergeMedicament(const int id);

	void ModificaMedicament(const int id, string denumire, double pret, string producator, string substanta);

	void VerificaExistentaID(const int id);

	void AdaugaInReteta(const size_t id);

	void AdaugaRandomInReteta(const int medicamente_de_adaugat);

	void GolesteReteta() noexcept;

	void ExportReteta(string nume_fisier);

	const vector<Medicament>& ReturneazaLista() const noexcept {
		return repository.ReturneazaListaDinRepository();
	}

	const vector<Medicament>& ReturneazaReteta() const noexcept {
		return repository.ReturneazaRetetaDinRepository();
	}

	const size_t Dimensiune() const noexcept {
		return repository.DimensiuneLista();
	}

	const size_t DimensiuneReteta() const noexcept {
		return repository.DimensiuneReteta();
	}

	int NumarUnicDeDenumiri();


	vector<Medicament> ReturneazaMedicament(const int id);

	vector<Medicament> FiltrareListaPret();

	vector<Medicament> FiltrareListaSubstanta();

	vector<Medicament> SortareLista(int alegere);

	void Undo();
};

void testeService();