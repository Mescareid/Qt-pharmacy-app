#pragma once

#include "entities.h"
#include <string>
#include <ostream>
#include <vector>

using std::ostream;
using std::vector;
using std::string;

class ExceptieValidator {
public:
	vector<string> mesaje_validare;
	ExceptieValidator(const vector<string> mesaje) : mesaje_validare{ mesaje } {}
};

class Validator {
public:
	void Valideaza(const Medicament& medicament);
};

void testeValidator();