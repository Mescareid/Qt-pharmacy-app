#include "repository.h"
#include "service.h"
#include <assert.h>
#include <random>
#include <fstream>
#include <string.h>
#include <ios>


//std::mt19937 mt{ std::random_device{}() };
//std::uniform_int_distribution<> dist(0, v.size() - 1);
//int rndNr = dist(mt);// numar aleator intre [0,size-1]



void Repository::AdaugaInReteta(const size_t id) {
	for (const auto& medicament : ListaMedicamente) {
		auto* pointer = &medicament;
		if (pointer != nullptr) {
			if (medicament.getId() == id) {
				Reteta.push_back(medicament);
				return;
			}
		}
	}

	throw ExceptieRepository("Nu exista medicamentul cu ID-ul cautat!\n");
}

void Repository::AdaugaRandomInReteta(const int medicamente_de_adaugat) {
	for (int i{ 0 }; i < medicamente_de_adaugat; ++i) {
		std::mt19937 mt{ std::random_device{}() };
		const std::uniform_int_distribution<size_t> dist(0, ListaMedicamente.size() - 1);
		const size_t indice_random = dist(mt);// numar aleator intre [0,size-1]
		Reteta.push_back(ListaMedicamente.at(indice_random));
	}
}

void Repository::GolesteReteta() noexcept {
	Reteta.clear();
}

size_t Repository::DimensiuneReteta() noexcept {
	return Reteta.size();
}

void Service::AdaugaInReteta(const size_t id) {
	repository.AdaugaInReteta(id);
	notify();
}

void Service::AdaugaRandomInReteta(const int medicamente_de_adaugat) {
	repository.AdaugaRandomInReteta(medicamente_de_adaugat);
	notify();
}

void Service::GolesteReteta() noexcept {
	repository.GolesteReteta();
	notify();
}

void Service::ExportReteta(string nume_fisier) {
	std::fstream fisier;

	fisier.open(nume_fisier, std::ios_base::out);

	if (!fisier.is_open())
		throw ExceptieRepository("Nu se poate deschide fisierul: " + nume_fisier);

	vector<Medicament> ExportReteta = ReturneazaReteta();

	for (const auto& medicament : ExportReteta) {
		const Medicament* pointer = &medicament;
		if (pointer != nullptr)
			fisier << medicament.getId() << ' ' << medicament.getDenumire() << ' ' << medicament.getPret() << ' ' << medicament.getProducator()
			<< ' ' << medicament.getSubstanta() << '\n';
	}

	fisier.close();
}

void testeReteta() {
	Medicament medicament{ 12, "paracetamol", 420.523, "pfizer", "adrenalina" };
	Medicament medicament2{ 1, "nurofen", 79, "pfi", "noradrenalina" };

	Repository repository;
	Validator validator;
	Service service{ repository, validator };
	repository.Adauga(medicament);
	repository.Adauga(medicament2);

	service.AdaugaInReteta(12);
	service.AdaugaInReteta(1);

	assert(service.DimensiuneReteta() == 2);

	try {
		repository.AdaugaInReteta(3);
	}
	catch (const ExceptieRepository& exceptie) {
		assert(exceptie.getRepositoryMesaj().size() > 0);
	}

	assert(service.DimensiuneReteta() == 2);

	service.GolesteReteta();
	assert(service.DimensiuneReteta() == 0);

	service.AdaugaRandomInReteta(4);
	assert(service.DimensiuneReteta() == 4);

	vector<Medicament> reteta = service.ReturneazaReteta();

	assert(reteta.size() == 4);

	service.ExportReteta("testExport.html");
}
