#include "repository.h"
#include <assert.h>
#include "file_repository.h"

/*ostream& operator<<(ostream& out, const ExceptieRepository& exceptie) {
	out << exceptie.getMesaj();
	return out;
}*/

size_t Repository::DimensiuneLista() noexcept {
	return ListaMedicamente.size();

}

const Medicament& Repository::CautaMedicament(int id) const {
	for (const auto& medicament : ListaMedicamente) {
		const Medicament* pointer = &medicament;
		if (pointer != nullptr)
			if (medicament.getId() == id)
				return medicament;
	}

	//daca am ajuns aici nu am gasit medicamentul cautat
	throw ExceptieRepository("Nu exista medicamentul cu ID-ul cautat!\n");
}

bool Repository::VerificaExistentaID(const int id) const {
	for (const auto& medicament : ListaMedicamente) {
		const Medicament* pointer = &medicament;
		if (pointer != nullptr)
			if (medicament.getId() == id)
				return true;
	}
	throw ExceptieRepository("Nu exista medicamentul cu ID-ul cautat!\n");
}

bool Repository::ExistaInLista(const Medicament& medicament) const {
	try {
		CautaMedicament(medicament.getId());
		return true;
	}
	catch (ExceptieRepository&) {
		return false;
	}
}

void Repository::Adauga(const Medicament& medicament) {
	if (ExistaInLista(medicament))
		throw ExceptieRepository("Exista deja medicament cu ID-ul introdus!\n");

	ListaMedicamente.push_back(medicament);
}

void Repository::Sterge(const int id) {
	int pozitie{ 0 };
	bool gasit{ false };

	for (const auto& medicament : ListaMedicamente) {
		const Medicament* pointer = &medicament;
		if (pointer != nullptr)
			if (medicament.getId() == id) {
				gasit = true;
				break;
			}
		++pozitie;
	}
	if (gasit)
		ListaMedicamente.erase(ListaMedicamente.begin() + pozitie);
	else
		throw ExceptieRepository("Nu exista medicamentul cu ID-ul cautat!\n");
}

void Repository::Modifica(const int id, const Medicament& medicament_nou) {
	bool gasit{ false };
	for (auto& medicament : ListaMedicamente) {
		const Medicament* pointer = &medicament;
		if (pointer != nullptr)
			if (medicament.getId() == id) {
				medicament = medicament_nou;
				gasit = true;
				break;
			}
	}
	if (!gasit)
		throw ExceptieRepository("Nu exista medicamentul cu ID-ul cautat!\n");
}


void testExistaSiCauta() {
	Medicament medicament{ 12, "paracetamol", 420.523, "pfizer", "adrenalina" };
	Medicament medicament2{ 1, "nurofen", 79, "pfi", "noradrenalina" };
	Medicament medicament3{ 12, "nurofen", 79, "pfi", "noradrenalina" };

	Repository repository;
	repository.Adauga(medicament);
	repository.Adauga(medicament2);

	Medicament medicament_gasit{ repository.CautaMedicament(1) };
	assert(medicament_gasit.getId() == 1);
	assert(medicament_gasit.getPret() == 79);

	ExceptieRepository exceptieRepository{ "eror" };

	try {
		Medicament medicament_gasit2 = repository.CautaMedicament(2);
	}
	catch (const ExceptieRepository& exceptie) {
		assert(exceptie.getRepositoryMesaj().size() > 0);
	}

	const bool gasit = repository.VerificaExistentaID(1);
	assert(gasit == true);

	try {
		repository.VerificaExistentaID(2);
	}
	catch (const ExceptieRepository& exceptie) {
		assert(exceptie.getRepositoryMesaj().size() > 0);
	}
}

void testAdaugaStergeMedicamente() {
	Medicament medicament{ 12, "paracetamol", 420.523, "pfizer", "adrenalina" };
	Medicament medicament2{ 1, "nurofen", 79, "pfi", "noradrenalina" };
	Medicament medicament3{ 12, "nurofen", 79, "pfi", "noradrenalina" };

	Repository repository;
	repository.Adauga(medicament);
	repository.Adauga(medicament2);

	assert(repository.DimensiuneLista() == 2);

	try {
		repository.Adauga(medicament);
	}
	catch (const ExceptieRepository& exceptie) {
		assert(exceptie.getRepositoryMesaj().size() > 0);
	}
	repository.Sterge(1);

	assert(repository.DimensiuneLista() == 1);

	try {
		repository.Sterge(1);
	}
	catch (const ExceptieRepository& exceptie) {
		assert(exceptie.getRepositoryMesaj().size() > 0);
	}
	repository.Modifica(12, medicament3);

	assert(repository.DimensiuneLista() == 1);

	try {
		repository.Modifica(1, medicament2);
	}
	catch (const ExceptieRepository& exceptie) {
		assert(exceptie.getRepositoryMesaj().size() > 0);
	}
}

void testReturneazaLista() {
	vector<Medicament> medicamente;
	Medicament medicament{ 12, "paracetamol", 420.523, "pfizer", "adrenalina" };
	Medicament medicament2{ 1, "nurofen", 79, "pfi", "noradrenalina" };

	Repository repository;
	repository.Adauga(medicament);
	repository.Adauga(medicament2);

	medicamente = repository.ReturneazaListaDinRepository();

	assert(medicamente.size() == 2);
}

//void testFileRepository() {
//	RepositoryFile repository{ "testRepositoryFile.html" };
//
//	Medicament medicament{ 12, "paracetamol", 420.523, "pfizer", "adrenalina" };
//	Medicament medicament2{ 1, "nurofen", 79, "pfi", "noradrenalina" };
//
//	repository.Adauga(medicament);
//	repository.Adauga(medicament2);
//
//	vector<Medicament> medicamente = repository.ReturneazaListaDinRepository();
//
//	assert(medicamente.size() == 2);
//}

void testeRepository() {
	testExistaSiCauta();
	testAdaugaStergeMedicamente();
	testReturneazaLista();
	testeReteta();
	//testFileRepository();
}