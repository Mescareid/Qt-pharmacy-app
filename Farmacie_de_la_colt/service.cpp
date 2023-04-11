#include "service.h"
#include <assert.h>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

void Service::AdaugaMedicament(const int id, const string denumire, double pret, string producator, string substanta) {
	Medicament medicament{ id, denumire, pret, producator, substanta };
	validator.Valideaza(medicament);
	repository.Adauga(medicament);

	ActiuniUndo.push_back(std::make_unique<UndoAdauga>(repository, medicament));
}

void Service::StergeMedicament(const int id) {
	VerificaExistentaID(id);
	vector<Medicament> element = ReturneazaMedicament(id);
	Medicament medicament = element.at(0);
	repository.Sterge(id);

	ActiuniUndo.push_back(std::make_unique<UndoSterge>(repository, medicament));
}

void Service::ModificaMedicament(const int id, string denumire, double pret, string producator, string substanta) {
	VerificaExistentaID(id);
	vector<Medicament> element = ReturneazaMedicament(id);
	Medicament medicamentUndo = element.at(0);

	Medicament medicament{ id, denumire, pret, producator, substanta };
	validator.Valideaza(medicament);
	repository.Modifica(id, medicament);

	ActiuniUndo.push_back(std::make_unique<UndoModifica>(repository, medicamentUndo, id));
}

void Service::VerificaExistentaID(const int id) {
	repository.VerificaExistentaID(id);
}

vector<Medicament> Service::ReturneazaMedicament(const int id) {
	vector<Medicament> lista_medicamente = ReturneazaLista();

	vector<Medicament> element;

	auto IdCorect = [id](Medicament medicament) { return id == medicament.getId(); };

	/*for (const auto& medicament : lista_medicamente) {
		auto* pointer = &medicament;
		if (pointer != nullptr)
			if (medicament.getId() == id)
				element.push_back(medicament);
	}*/

	auto iterator = std::find_if(lista_medicamente.begin(), lista_medicamente.end(), IdCorect);

	element.push_back(*iterator);

	return element;
}

vector<Medicament> Service::FiltrareListaPret() {
	vector<Medicament> lista_medicamente = ReturneazaLista();

	vector<Medicament> elemente;

	for (const auto& medicament : lista_medicamente) {
		auto* pointer = &medicament;
		if (pointer != nullptr)
			if (medicament.getPret() <= 100)
				elemente.push_back(medicament);
	}


	return elemente;
}

vector<Medicament> Service::FiltrareListaSubstanta() {
	vector<Medicament> lista_medicamente = ReturneazaLista();

	vector<Medicament> elemente;
	string codeina = "codeina";

	for (const auto& medicament : lista_medicamente) {
		auto* pointer = &medicament;
		if (pointer != nullptr)
			if (medicament.getSubstanta() == codeina)
				elemente.push_back(medicament);
	}


	return elemente;
}

vector<Medicament> Service::SortareLista(int alegere) {
	vector<Medicament> lista_medicamente = ReturneazaLista();

	if (alegere == 1) {
		sort(lista_medicamente.begin(), lista_medicamente.end(), [](Medicament medicament1, Medicament medicament2) {
			return medicament1.getDenumire() < medicament2.getDenumire(); });
	}
	else if (alegere == 2) {
		sort(lista_medicamente.begin(), lista_medicamente.end(), [](Medicament medicament1, Medicament medicament2) {
			return medicament1.getProducator() < medicament2.getProducator(); });
	}
	else {
		sort(lista_medicamente.begin(), lista_medicamente.end(), [](Medicament medicament1, Medicament medicament2) {
			if (medicament1.getSubstanta() < medicament2.getSubstanta())
				return true;
			if (medicament2.getSubstanta() < medicament1.getSubstanta())
				return false;

			//medicament1.getSubstanta() == medicament2.getSubstanta()

			if (medicament1.getPret() < medicament2.getPret())
				return true;
			if (medicament2.getPret() < medicament1.getPret())
				return false;

			return false;
			});
	}

	return lista_medicamente;
}

void Service::Undo() {
	if (ActiuniUndo.size() == 0)
		throw ExceptieRepository("Nu se mai pot face operatii de tip undo!\n");

	ActiuniUndo.back()->Undo();
	ActiuniUndo.pop_back();
}

void testAdaugaStergeModifica() {
	Repository repository;
	Validator validator;
	Service service{ repository, validator };

	service.AdaugaMedicament(12, "paracetamol", 420.523, "pfizer", "codeina");
	assert(service.Dimensiune() == 1);

	service.VerificaExistentaID(12);

	service.ModificaMedicament(12, "nurofen", 79, "pfi", "codeina");
	assert(service.Dimensiune() == 1);

	vector<Medicament> medicamente = service.ReturneazaLista();

	assert(medicamente.size() == 1);

	service.StergeMedicament(12);

	assert(service.Dimensiune() == 0);
}

void testCautaFiltreazaSorteaza() {
	Repository repository;
	Validator validator;
	Service service{ repository, validator };

	service.AdaugaMedicament(12, "paraceol", 20.523, "r", "codeina");
	service.AdaugaMedicament(1, "paacetamol", 420.3, "fizer", "cipralex");
	service.AdaugaMedicament(2, "pacetamol", 4203, "zer", "piracetam");
	service.AdaugaMedicament(23, "racetamol", 4.523, "izer", "methanol");
	service.AdaugaMedicament(5, "paatamol", 4203, "pfizer", "piracetam");
	service.AdaugaMedicament(8, "paracemol", 40.23, "pfir", "cipralex");

	vector<Medicament> element = service.ReturneazaMedicament(1);
	assert(element.at(0).getPret() == 420.3);

	vector<Medicament> filtrare_pret = service.FiltrareListaPret();
	vector<Medicament> filtrare_substanta = service.FiltrareListaSubstanta();

	assert(filtrare_pret.at(0).getId() == 12);
	assert(filtrare_substanta.at(0).getSubstanta() == "codeina");

	vector<Medicament> sortare_dupa_denumire = service.SortareLista(1);
	vector<Medicament> sortare_dupa_producator = service.SortareLista(2);
	vector<Medicament> sortare_dupa_substanta_si_pret = service.SortareLista(3);

	assert(sortare_dupa_denumire.at(0).getId() == 1);
	assert(sortare_dupa_producator.at(0).getId() == 1);
	assert(sortare_dupa_substanta_si_pret.at(0).getId() == 8);
}

void testUndo() {
	Repository repository;
	Validator validator;
	Service service{ repository, validator };

	try {
		service.Undo();
	}
	catch (const ExceptieRepository& exceptie) {
		assert(exceptie.getRepositoryMesaj().size() > 0);
	}

	service.AdaugaMedicament(12, "paraceol", 20.523, "r", "codeina");
	service.AdaugaMedicament(1, "paacetamol", 420.3, "fizer", "cipralex");
	service.AdaugaMedicament(2, "pacetamol", 4203, "zer", "piracetam");

	service.Undo();

	assert(service.Dimensiune() == 2);

	service.StergeMedicament(12);

	assert(service.Dimensiune() == 1);

	service.Undo();

	assert(service.Dimensiune() == 2);

	service.ModificaMedicament(1, "pacetamol", 4203, "zer", "piracetam");

	service.Undo();
}

void testeService() {
	testAdaugaStergeModifica();
	testCautaFiltreazaSorteaza();
	testUndo();
}

int Service::NumarUnicDeDenumiri() {
	vector<Medicament> lista_sortata = SortareLista(1);
	int numar_denumiri_unice{ 0 };

	for (int i{ 0 }; i < lista_sortata.size() - 1; ++i)
		if (lista_sortata.at(i).getDenumire() != lista_sortata.at(i + 1).getDenumire())
			++numar_denumiri_unice;

	return numar_denumiri_unice;
}