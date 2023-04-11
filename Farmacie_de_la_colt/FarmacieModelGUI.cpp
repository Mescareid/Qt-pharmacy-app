#include "FarmacieModelGUI.h"
#include <QSpinBox>
#include "RetetaGUI.h"
#include "ImaginiGUI.h"

using std::to_string;

void FarmacieModelGUI::initializeazaGUI() {
	QHBoxLayout* layoutPrincipal = new QHBoxLayout;
	this->setLayout(layoutPrincipal);

	QWidget* left = new QWidget;
	QVBoxLayout* layoutLeft = new QVBoxLayout;
	left->setLayout(layoutLeft);

	QWidget* form = new QWidget;
	QFormLayout* layoutForm = new QFormLayout;
	form->setLayout(layoutForm);

	editId = new QLineEdit;
	editDenumire = new QLineEdit;
	editPret = new QLineEdit;
	editProducator = new QLineEdit;
	editSubstanta = new QLineEdit;

	layoutForm->addRow(labelId, editId);
	layoutForm->addRow(labelDenumire, editDenumire);
	layoutForm->addRow(labelPret, editPret);
	layoutForm->addRow(labelProducator, editProducator);
	layoutForm->addRow(labelSubstanta, editSubstanta);

	layoutLeft->addWidget(form);

	//butoane adauga/sterge
	QHBoxLayout* butoaneAdaugaSterge = new QHBoxLayout;

	butonAdaugaMedicament = new QPushButton("Adauga medicament");
	butonStergeMedicament = new QPushButton("Sterge medicament");
	butoaneAdaugaSterge->addWidget(butonStergeMedicament);
	butoaneAdaugaSterge->addWidget(butonAdaugaMedicament);

	layoutLeft->addLayout(butoaneAdaugaSterge);

	//butoane undo/modifica

	QHBoxLayout* butoaneUndoModifica = new QHBoxLayout;

	butonUndo = new QPushButton("Undo");
	butoaneUndoModifica->addWidget(butonUndo);
	butonModificaMedicament = new QPushButton("Modifica medicament");
	butoaneUndoModifica->addWidget(butonModificaMedicament);

	layoutLeft->addLayout(butoaneUndoModifica);

	//buton reload

	QHBoxLayout* layoutReteta = new QHBoxLayout;
	butonImagini = new QPushButton("Imagini");
	butonReteta = new QPushButton("Meniu Reteta");
	layoutReteta->addWidget(butonImagini);
	layoutReteta->addWidget(butonReteta);

	layoutLeft->addLayout(layoutReteta);

	butonReload = new QPushButton("Reload");
	layoutLeft->addWidget(butonReload);


	//lista

	QWidget* Right = new QWidget;
	QVBoxLayout* layoutLista = new QVBoxLayout;

	//lista = new QListWidget;

	QLabel* informatii = new QLabel{ "Id\t\tDenumire\tPret\tProducator\tSubstanta activa" };

	QHBoxLayout* butoaneSortari = new QHBoxLayout;

	butonSorteazaDenumire = new QPushButton("Sorteaza Denumire");
	butoaneSortari->addWidget(butonSorteazaDenumire);

	butonSorteazaProducator = new QPushButton("Sorteaza Producator");
	butoaneSortari->addWidget(butonSorteazaProducator);

	butonSorteazaSubstantaPret = new QPushButton("Sorteaza Substanta+Pret");
	butoaneSortari->addWidget(butonSorteazaSubstantaPret);

	QHBoxLayout* butoaneFiltrari = new QHBoxLayout;

	butonFiltreazaPret = new QPushButton("Filtreaza dupa pret");
	butoaneFiltrari->addWidget(butonFiltreazaPret);

	butonFiltreazaSubstanta = new QPushButton("Filtreaza dupa substanta");
	butoaneFiltrari->addWidget(butonFiltreazaSubstanta);

	Right->setLayout(layoutLista);
	layoutLista->addWidget(informatii);
	layoutLista->addWidget(listaCuModel);
	layoutLista->addLayout(butoaneSortari);
	layoutLista->addLayout(butoaneFiltrari);

	layoutPrincipal->addWidget(left);
	layoutPrincipal->addWidget(Right);
	//layoutPrincipal->addWidget(lista);
	//layoutPrincipal->addWidget(tabelModel);
	//layoutPrincipal->addWidget(right);
}

void FarmacieModelGUI::reloadLista(vector<Medicament> medicamente) {
	//this->lista->clear();
	model->seteazaLista(medicamente);
}

void FarmacieModelGUI::conecteazaSignalsSlots() {
	QObject::connect(butonAdaugaMedicament, &QPushButton::clicked, this, &FarmacieModelGUI::guiAdaugaMedicament);

	QObject::connect(butonStergeMedicament, &QPushButton::clicked, this, &FarmacieModelGUI::guiStergeMedicament);

	QObject::connect(butonUndo, &QPushButton::clicked, this, &FarmacieModelGUI::guiUndo);

	QObject::connect(butonModificaMedicament, &QPushButton::clicked, this, &FarmacieModelGUI::guiModificaMedicament);

	QObject::connect(butonReteta, &QPushButton::clicked, [&]() {
		auto retetaGUI = new RetetaGUI{ service };
		retetaGUI->show();
		});
	QObject::connect(butonImagini, &QPushButton::clicked, [&]() {
		auto imaginiGUI = new ImaginiGUI(service);
		imaginiGUI->show();
		});

	QObject::connect(butonReload, &QPushButton::clicked, [&]() {
		reloadLista(service.ReturneazaLista());
		});

	QObject::connect(butonSorteazaDenumire, &QPushButton::clicked, [&]() {
		reloadLista(service.SortareLista(1));
		});

	QObject::connect(butonSorteazaProducator, &QPushButton::clicked, [&]() {
		reloadLista(service.SortareLista(2));
		});

	QObject::connect(butonSorteazaSubstantaPret, &QPushButton::clicked, [&]() {
		reloadLista(service.SortareLista(3));
		});

	QObject::connect(butonFiltreazaPret, &QPushButton::clicked, [&]() {
		reloadLista(service.FiltrareListaPret());
		});

	QObject::connect(butonFiltreazaSubstanta, &QPushButton::clicked, [&]() {
		reloadLista(service.FiltrareListaSubstanta());
		});

	QObject::connect(listaCuModel->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (listaCuModel->selectionModel()->selectedIndexes().isEmpty()) {
			editId->setText("");
			editDenumire->setText("");
			editPret->setText("");
			editProducator->setText("");
			editSubstanta->setText("");
			return;
		}
		auto index = listaCuModel->selectionModel()->selectedIndexes().at(0);
		auto linie = index.data(Qt::DisplayRole).toString();
		auto stringTabel = linie.toStdString();

		vector<string> campuri;

		char* dup = strdup(stringTabel.c_str());
		auto token = strtok(dup, "\t");

		while (token != NULL) {
			campuri.push_back(token);
			token = strtok(NULL, "\t");
		}
		free(dup);

		//sau cauti medicamentul dupa id si e mai usor

		editId->setText(QString::fromStdString(campuri.at(0)));
		editDenumire->setText(QString::fromStdString(campuri.at(1)));
		editPret->setText(QString::fromStdString(campuri.at(2)));
		editProducator->setText(QString::fromStdString(campuri.at(3)));
		editSubstanta->setText(QString::fromStdString(campuri.at(4)));

		});
}

void FarmacieModelGUI::guiAdaugaMedicament() {
	try {
		int id = editId->text().toInt();
		string denumire = editDenumire->text().toStdString();
		double pret = editPret->text().toDouble();
		string producator = editProducator->text().toStdString();
		string substanta = editSubstanta->text().toStdString();

		editId->clear();
		editDenumire->clear();
		editPret->clear();
		editProducator->clear();
		editSubstanta->clear();

		this->service.AdaugaMedicament(id, denumire, pret, producator, substanta);

		reloadLista(this->service.ReturneazaLista());

		QMessageBox::information(this, "Info", QString::fromStdString("Medicament adaugat cu succes."));
	}
	catch (ExceptieRepository& exceptie) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exceptie.getRepositoryMesaj()));
	}
	catch (ExceptieValidator& exceptie) {
		for (const auto& mesaj : exceptie.mesaje_validare) {
			const string* pointer = &mesaj;
			if (pointer != nullptr)
				QMessageBox::warning(this, "Warning", QString::fromStdString(mesaj));

		}
	}
}

void FarmacieModelGUI::guiStergeMedicament() {
	try {
		int id = editId->text().toInt();
		service.StergeMedicament(id);
		reloadLista(service.ReturneazaLista());

		QMessageBox::information(this, "Info", QString::fromStdString("Stergere efectuata cu succes."));
	}
	catch (ExceptieRepository& exceptie) {
		QMessageBox::warning(this, "Warning", "Nu este selectat niciun camp din tabel!!");
	}
}

void FarmacieModelGUI::guiModificaMedicament() {
	try {
		int id = editId->text().toInt();
		string denumire = editDenumire->text().toStdString();
		double pret = editPret->text().toDouble();
		string producator = editProducator->text().toStdString();
		string substanta = editSubstanta->text().toStdString();

		editId->clear();
		editDenumire->clear();
		editPret->clear();
		editProducator->clear();
		editSubstanta->clear();

		this->service.ModificaMedicament(id, denumire, pret, producator, substanta);

		reloadLista(this->service.ReturneazaLista());

		QMessageBox::information(this, "Info", QString::fromStdString("Medicament modificat cu succes."));
	}
	catch (ExceptieRepository& exceptie) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exceptie.getRepositoryMesaj()));
	}
	catch (ExceptieValidator& exceptie) {
		for (const auto& mesaj : exceptie.mesaje_validare) {
			const string* pointer = &mesaj;
			if (pointer != nullptr)
				QMessageBox::warning(this, "Warning", QString::fromStdString(mesaj));

		}
	}
}

void FarmacieModelGUI::guiUndo() {
	try {
		service.Undo();
		reloadLista(service.ReturneazaLista());
		QMessageBox::information(this, "Info", QString::fromStdString("Operatie efectuata cu succes."));
	}
	catch (ExceptieRepository& exceptie) {
		QMessageBox::warning(this, "Warning", "Nu se mai pot face operatii undo!");
	}
}
