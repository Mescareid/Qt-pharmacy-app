#include "validator.h"
#include <assert.h>

void Validator::Valideaza(const Medicament& medicament) {
	vector<string> mesaje_validare;
	if (medicament.getId() < 0)
		mesaje_validare.push_back("ID-ul nu poate fi negativ!\n");
	if (medicament.getDenumire().size() == 0)
		mesaje_validare.push_back("Denumirea produsului nu poate fi vida!\n");
	if (medicament.getPret() < 0)
		mesaje_validare.push_back("Pretul produsului nu poate fi negativ!\n");
	if (medicament.getProducator().size() == 0)
		mesaje_validare.push_back("Numele producatorului nu poate fi vid!\n");
	string codeina = "codeina";
	string piracetam = "piracetam";
	string methanol = "methanol";
	string cipralex = "cipralex";
	bool gasit = false;
	if (medicament.getSubstanta() == codeina || medicament.getSubstanta() == piracetam ||
		medicament.getSubstanta() == methanol || medicament.getSubstanta() == cipralex)
		gasit = true;

	if (!gasit)
		mesaje_validare.push_back("Denumirea substantei active nu este conforma!\n");

	if (mesaje_validare.size() > 0)
		throw(ExceptieValidator(mesaje_validare));
}

void testeValidator() {
	Medicament medicament{ 12, "paracetamol", 420.523, "pfizer", "codeina" };
	Validator validator;
	validator.Valideaza(medicament);
	assert(true);

	Medicament medicament_invalid{ -1, "", -123, "", "heroina" };

	try {
		validator.Valideaza(medicament_invalid);
	}
	catch (const ExceptieValidator& mesaje) {
		assert(mesaje.mesaje_validare.size() == 5);
	}
}