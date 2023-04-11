#include "user_interface.h"
#include <iostream>

using std::cin;
using std::cout;

void Consola::AfiseazaMeniu() {
	cout << "1. Adauga un medicament nou in lista.\n";
	cout << "2. Sterge un medicament din lista.\n";
	cout << "3. Modifica un medicament din lista.\n";
	cout << "4. Afiseaza medicamentele din lista.\n";
	cout << "5. Cauta un medicament dupa id.\n";
	cout << "6. Filtreaza medicamentele dupa pret sau substanta activa.\n";
	cout << "7. Meniu de sortari.\n";
	cout << "8. Adauga un medicament in reteta.\n";
	cout << "9. Adauga medicamente random in reteta.\n";
	cout << "s. Afiseaza medicamentele din reteta.\n";
	cout << "-. Goleste reteta.\n";
	cout << "e. Export la reteta intr-un fisier dorit.\n";
	cout << "u. Undo.\n";
	cout << "h. Afiseaza din nou acest meniu.\n";
	cout << "x|0. Iesire din aplicatie...\n";
}

void Consola::Start() {
	AfiseazaMeniu();
	const Service* pointer_service = &service;
	while (true) {
		char alegere;
		cout << ">>>";
		cin >> alegere;

		try {
			switch (alegere) {
			case '1':
				AdaugaInput();
				break;
			case '2':
				StergeMedicament();
				break;
			case '3':
				ModificaMedicament();
				break;
			case '4':
				if (pointer_service != nullptr)
					TiparesteLista(service.ReturneazaLista());
				break;
			case '5':
				CautaMedicament();
				break;
			case '6':
				FiltrareLista();
				break;
			case '7':
				SortareLista();
				break;
			case '8':
				AdaugaMedicamentInReteta();
				break;
			case '9':
				AdaugaMedicamenteRandomInReteta();
				break;
			case 's':
				if (pointer_service != nullptr)
					TiparesteReteta(service.ReturneazaReteta());
				break;
			case '-':
				GolesteReteta();
				break;
			case 'e':
				ExportReteta();
				break;
			case 'h':
				AfiseazaMeniu();
				break;
			case 'u':
				Undo();
				break;
			case 'x':
				return;
			case '0':
				return;
			default:
				cout << "Comanda invalida\n";
				break;
			}
		}
		catch (const ExceptieRepository& mesaj_repository) {
			cout << mesaj_repository.getRepositoryMesaj() << '\n';
		}
		catch (const ExceptieValidator& mesaje_validare) {
			for (const auto& mesaj : mesaje_validare.mesaje_validare) {
				const string* pointer = &mesaj;
				if (pointer != nullptr)
					cout << mesaj;
			}
		}
	}

}


void Consola::AdaugaInput() {
	int id;
	double pret;
	string denumire, producator, substanta_activa;

	cout << "Introduceti ID-ul noului medicament: ";
	cin >> id;
	cout << "Introduceti denumirea noului medicament: ";
	cin >> denumire;
	cout << "Introduceti pretul noului medicament: ";
	cin >> pret;
	cout << "Introduceti numele producatorului: ";
	cin >> producator;
	cout << "Introduceti substanta activa a medicamentului: ";
	cin >> substanta_activa;

	service.AdaugaMedicament(id, denumire, pret, producator, substanta_activa);

	cout << "Medicament adaugat cu succes!\n";
}

void Consola::StergeMedicament() {
	int id;
	cout << "Introduceti ID-ul medicamentului de sters: ";
	cin >> id;

	service.StergeMedicament(id);
	cout << "Medicament sters cu succes!\n";
}

void Consola::ModificaMedicament() {
	int id;
	cout << "Introduceti ID-ul medicamentului pe care vreti sa il modificati:";
	cin >> id;

	service.VerificaExistentaID(id);

	double pret;
	string denumire, producator, substanta_activa;
	cout << "Introduceti denumirea medicamentului nou: ";
	cin >> denumire;
	cout << "Introduceti pretul medicamentului nou: ";
	cin >> pret;
	cout << "Introduceti numele producatorului nou: ";
	cin >> producator;
	cout << "Introduceti substanta activa a medicamentului nou: ";
	cin >> substanta_activa;

	service.ModificaMedicament(id, denumire, pret, producator, substanta_activa);

	cout << "Medicamentul a fost modificat cu succes!\n";
}

void Consola::TiparesteLista(const vector<Medicament>& medicamente) {
	if (medicamente.size() == 0) {
		cout << "Lista de medicamente este goala.\n";
		return;
	}


	cout << "\nMedicamentele din lista:\n\n";
	int indice = 0;

	for (const auto& medicament : medicamente) {
		const Medicament* pointer = &medicament;
		if (pointer != nullptr) {
			++indice;
			cout << "Medicamentul " << indice << ":\n";
			cout << "ID: " << medicament.getId() << '\n';
			cout << "Denumire: " << medicament.getDenumire() << '\n';
			cout << "Pret: " << medicament.getPret() << '\n';
			cout << "Producator: " << medicament.getProducator() << '\n';
			cout << "Substanta activa: " << medicament.getSubstanta() << '\n';
			cout << '\n';
		}
	}
}

void Consola::CautaMedicament() {
	int id;
	cout << "Introduceti ID-ul medicamentului pe care vreti sa il cautati:";
	cin >> id;

	service.VerificaExistentaID(id);

	vector<Medicament> medicament_cautat = service.ReturneazaMedicament(id);

	TiparesteLista(medicament_cautat);
}

void Consola::FiltrareLista() {
	cout << "Optiuni filtrare medicamente:\n";
	cout << "1. Filtrare medicamente cu pretul mai mic de 100.\n";
	cout << "2. Filtrare medicamente care au codeina drept substanta activa.\n";
	cout << "Introduce alegerea:";

	int alegere;
	cin >> alegere;

	vector<Medicament> lista_filtrata;

	if (alegere == 1)
		lista_filtrata = service.FiltrareListaPret();
	else
		lista_filtrata = service.FiltrareListaSubstanta();

	TiparesteLista(lista_filtrata);
}

void Consola::SortareLista() {
	cout << "Optiuni sortare medicamente:\n";
	cout << "1. Sortare crescatoare dupa denumire.\n";
	cout << "2. Sortare crescatoare dupa producator.\n";
	cout << "3. Sortare crescatoare dupa substanta activa + pret.\n";
	cout << "Introduce alegerea:";

	int alegere;
	cin >> alegere;

	vector<Medicament> lista_sortata = service.SortareLista(alegere);
	TiparesteLista(lista_sortata);
}

void Consola::AdaugaMedicamentInReteta() {
	size_t id;
	cout << "Introduceti ID-ul medicamentului care trebuie introdus in reteta:";
	cin >> id;

	service.AdaugaInReteta(id);
	cout << "Reteta are " << service.DimensiuneReteta() << " medicamente.\n";
}

void Consola::AdaugaMedicamenteRandomInReteta() {
	if (service.Dimensiune() == 0) {
		cout << "Lista de medicamente este goala!\n";
		return;
	}

	int numar_de_medicamente;
	cout << "Introduceti numarul de medicamente random care trebuie introduse in reteta:";
	cin >> numar_de_medicamente;

	service.AdaugaRandomInReteta(numar_de_medicamente);

	cout << numar_de_medicamente << " medicamente au fost adaugate cu succes in reteta!\n";
	cout << "Reteta are " << service.DimensiuneReteta() << "medicamente.\n";
}

void Consola::TiparesteReteta(const vector<Medicament>& reteta) {
	if (reteta.size() == 0) {
		cout << "Reteta este goala.\n";
		return;
	}


	cout << "\nMedicamentele din reteta:\n\n";
	int indice = 0;

	for (const auto& medicament : reteta) {
		const Medicament* pointer = &medicament;
		if (pointer != nullptr) {
			++indice;
			cout << "Medicamentul " << indice << ":\n";
			cout << "ID: " << medicament.getId() << '\n';
			cout << "Denumire: " << medicament.getDenumire() << '\n';
			cout << "Pret: " << medicament.getPret() << '\n';
			cout << "Producator: " << medicament.getProducator() << '\n';
			cout << "Substanta activa: " << medicament.getSubstanta() << '\n';
			cout << '\n';
		}
	}
}

void Consola::GolesteReteta() {
	service.GolesteReteta();
	cout << "Reteta golita cu succes!\n";
}

void Consola::ExportReteta() {
	cout << "Introduceti numele fisierului HTML in care doriti sa exportati reteta: ";
	string nume_fisier;
	cin >> nume_fisier;

	service.ExportReteta(nume_fisier);
	cout << "Export reusit in fisierul " + nume_fisier << '\n';
}

void Consola::Undo() {
	service.Undo();
	cout << "Operatie realizata cu succes!\n";
}