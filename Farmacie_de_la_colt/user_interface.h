#pragma once

#include "service.h"


class Consola {
private:
	Service& service;

	void AdaugaInput();

	void StergeMedicament();

	void ModificaMedicament();

	void TiparesteLista(const vector<Medicament>& medicamente);

	void CautaMedicament();

	void FiltrareLista();

	void SortareLista();

	void TiparesteReteta(const vector<Medicament>& reteta);

	void AdaugaMedicamentInReteta();

	void AdaugaMedicamenteRandomInReteta();

	void GolesteReteta();

	void ExportReteta();

	void Undo();

public:
	Consola(Service& service) noexcept : service{ service } {}

	void AfiseazaMeniu();

	void Start();
};