#include "file_repository.h"
#include <fstream>

using std::string;

void RepositoryFile::CitesteDinFisier() {
	std::ifstream in(nume_fisier);

	if (!in.is_open())
		throw ExceptieRepository("Nu se poate deschide fisierul: " + nume_fisier);

	while (!in.eof()) {
		int id;
		in >> id;
		string denumire;
		in >> denumire;
		double pret;
		in >> pret;
		string producator;
		in >> producator;
		string substanta_activa;
		in >> substanta_activa;

		if (in.eof())
			break;

		Medicament medicament{ id, denumire, pret, producator, substanta_activa };
		Repository::Adauga(medicament);
	}
	in.close();

}

void RepositoryFile::ScrieInFisier() {
	std::ofstream out(nume_fisier);

	if (!out.is_open())
		throw ExceptieRepository("Nu se poate deschide fisierul: " + nume_fisier);

	vector<Medicament> ListaCopiata = ReturneazaListaDinRepository();

	for (const auto& medicament : ListaCopiata) {
		const Medicament* pointer = &medicament;
		if (pointer != nullptr)
			out << medicament.getId() << ' ' << medicament.getDenumire() << ' ' << medicament.getPret() << ' ' << medicament.getProducator()
			<< ' ' << medicament.getSubstanta() << '\n';
	}

	out.close();
}
