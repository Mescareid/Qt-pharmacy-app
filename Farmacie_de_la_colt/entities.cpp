#include "entities.h"
#include <assert.h>

Medicament& Medicament::operator=(const Medicament& medicament) {
	this->id = medicament.getId();
	this->pret = medicament.getPret();
	this->denumire = medicament.getDenumire();
	this->producator = medicament.getProducator();
	this->substanta_activa = medicament.getSubstanta();

	return *this;
}

void testConstructor() {
	Medicament medicament{ 12, "paracetamol", 420.523, "pfizer", "adrenalina" };
	Medicament medicament2{ medicament };
	assert(medicament.getId() == 12);
	assert(medicament2.getDenumire() == "paracetamol");
	assert(medicament2.getPret() == 420.523);
	assert(medicament.getProducator() == "pfizer");
	assert(medicament2.getSubstanta() == "adrenalina");
}

void testOperator() {
	Medicament medicament{ 12, "paracetamol", 420.523, "pfizer", "adrenalina" };
	Medicament medicament2{ 1, "nurofen", 79, "pfi", "noradrenalina" };

	medicament = medicament2;
	assert(medicament.getId() == 1);
	assert(medicament.getPret() == 79);
}

void testeDomain() {
	testConstructor();
	testOperator();
}