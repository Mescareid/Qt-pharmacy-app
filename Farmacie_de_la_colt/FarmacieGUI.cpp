#include "FarmacieGUI.h"
#include <QSpinBox>
#include "RetetaGUI.h"
#include "ImaginiGUI.h"

using std::to_string;

void FarmacieGUI::initializeazaGUI() {
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


	//partea dreapta

	QWidget* right = new QWidget;
	QVBoxLayout* layoutRight = new QVBoxLayout;
	right->setLayout(layoutRight);

	int numarLinii = 10;
	int numarColoane = 5;
	this->tabelMedicamente = new QTableWidget{ numarLinii, numarColoane };

	QStringList tabelHeader;

	tabelHeader << "ID" << "Denumire" << "Pret" << "Producator" << "Substanta activa";
	this->tabelMedicamente->setHorizontalHeaderLabels(tabelHeader);

	this->tabelMedicamente->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	layoutRight->addWidget(tabelMedicamente);

	//lista

	QWidget* Right = new QWidget;
	QVBoxLayout* layoutLista = new QVBoxLayout;

	lista = new QListWidget;

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
	layoutLista->addWidget(lista);
	layoutLista->addLayout(butoaneSortari);
	layoutLista->addLayout(butoaneFiltrari);

	layoutPrincipal->addWidget(left);
	layoutPrincipal->addWidget(Right);
	layoutPrincipal->addWidget(right);
}

void FarmacieGUI::reloadLista(vector<Medicament> medicamente) {
	this->tabelMedicamente->clearContents();
	this->lista->clear();
	this->tabelMedicamente->setRowCount(medicamente.size());

	int numarLinie{ 0 };
	for (const auto& medicament : medicamente) {
		auto id = QString::number(medicament.getId());
		auto denumire = QString::fromStdString(medicament.getDenumire());
		auto pret = QString::number(medicament.getPret());
		auto producator = QString::fromStdString(medicament.getProducator());
		auto substanta = QString::fromStdString(medicament.getSubstanta());

		this->tabelMedicamente->setItem(numarLinie, 0, new QTableWidgetItem(id));
		this->tabelMedicamente->setItem(numarLinie, 1, new QTableWidgetItem(denumire));
		this->tabelMedicamente->setItem(numarLinie, 2, new QTableWidgetItem(pret));
		this->tabelMedicamente->setItem(numarLinie, 3, new QTableWidgetItem(producator));
		this->tabelMedicamente->setItem(numarLinie, 4, new QTableWidgetItem(substanta));
		++numarLinie;

		auto linieTabel = id + '\t' + denumire + '\t' + pret + '\t' + producator + '\t' + substanta;

		lista->addItem(linieTabel);
	}
}

void FarmacieGUI::conecteazaSignalsSlots() {
	QObject::connect(butonAdaugaMedicament, &QPushButton::clicked, this, &FarmacieGUI::guiAdaugaMedicament);

	QObject::connect(butonStergeMedicament, &QPushButton::clicked, this, &FarmacieGUI::guiStergeMedicament);

	QObject::connect(butonUndo, &QPushButton::clicked, this, &FarmacieGUI::guiUndo);

	QObject::connect(butonModificaMedicament, &QPushButton::clicked, this, &FarmacieGUI::guiModificaMedicament);

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

	QObject::connect(lista, &QListWidget::itemSelectionChanged, [&]() {
		auto itemSelectat = lista->selectedItems();
		if (itemSelectat.isEmpty()) {
			editId->setText("");
			editDenumire->setText("");
			editPret->setText("");
			editProducator->setText("");
			editSubstanta->setText("");
		}
		else{
			auto item = itemSelectat.at(0);
			auto linieTabel = item->text();
			auto stringTabel = linieTabel.toStdString();

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
		}
		});
}

void FarmacieGUI::guiAdaugaMedicament() {
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

void FarmacieGUI::guiStergeMedicament() {
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

void FarmacieGUI::guiModificaMedicament(){
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

void FarmacieGUI::guiUndo(){
	try {
		service.Undo();
		reloadLista(service.ReturneazaLista());
		QMessageBox::information(this, "Info", QString::fromStdString("Operatie efectuata cu succes."));
	}
	catch (ExceptieRepository& exceptie) {
		QMessageBox::warning(this, "Warning", "Nu se mai pot face operatii undo!");
	}
}
