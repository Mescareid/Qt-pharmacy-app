#include "RetetaGUI.h"

using std::to_string;

void RetetaGUI::initializeazaGUI(){
	QHBoxLayout* layoutPrincipal = new QHBoxLayout;
	this->setLayout(layoutPrincipal);


	//partea stanga
	QWidget* left = new QWidget;
	QVBoxLayout* layoutLeft = new QVBoxLayout;
	left->setLayout(layoutLeft);

	QWidget* form = new QWidget;
	QFormLayout* layoutForm = new QFormLayout;
	form->setLayout(layoutForm);

	editId = new QLineEdit;
	editRandom = new QLineEdit;

	layoutForm->addRow(labelId, editId);
	layoutForm->addRow(labelRandom, editRandom);

	layoutLeft->addWidget(form);


	//butoane

	QVBoxLayout* butoaneReteta = new QVBoxLayout;

	butonAdaugaMedicament = new QPushButton("Adauga medicamentul in reteta");
	butonAdaugaRandom = new QPushButton("Adauga random medicamente in reteta");
	butonGolesteReteta = new QPushButton("Goleste medicamentele din reteta");
	butoaneReteta->addWidget(butonAdaugaMedicament);
	butoaneReteta->addWidget(butonAdaugaRandom);
	butoaneReteta->addWidget(butonGolesteReteta);

	layoutLeft->addLayout(butoaneReteta);

	//partea dreapta

	QWidget* right = new QWidget;
	QVBoxLayout* layoutLista = new QVBoxLayout;

	listaReteta = new QListWidget;

	QLabel* informatii = new QLabel{ "Id\t\tDenumire\tPret\tProducator\tSubstanta activa" };

	QHBoxLayout* Export = new QHBoxLayout;

	Export->addWidget(labelExport);

	editExport = new QLineEdit;
	Export->addWidget(editExport);

	butonExport = new QPushButton{ "Export" };
	Export->addWidget(butonExport);

	right->setLayout(layoutLista);
	layoutLista->addWidget(informatii);
	layoutLista->addWidget(listaReteta);
	layoutLista->addLayout(Export);

	layoutPrincipal->addWidget(left);
	layoutPrincipal->addWidget(right);

}

void RetetaGUI::conecteazaSignalsSlots(){
	service.addObserver(this);
	QObject::connect(butonAdaugaMedicament, &QPushButton::clicked, this, &RetetaGUI::guiAdaugaMedicamentInReteta);

	QObject::connect(butonAdaugaRandom, &QPushButton::clicked, this, &RetetaGUI::guiAdaugaRandomInReteta);

	QObject::connect(butonGolesteReteta, &QPushButton::clicked, this, &RetetaGUI::guiGolesteReteta);

	QObject::connect(butonExport, &QPushButton::clicked, this, &RetetaGUI::guiExport);
}

void RetetaGUI::reloadLista(vector<Medicament> medicamente){
	this->listaReteta->clear();

	for (const auto& medicament : medicamente) {
		auto id = QString::number(medicament.getId());
		auto denumire = QString::fromStdString(medicament.getDenumire());
		auto pret = QString::number(medicament.getPret());
		auto producator = QString::fromStdString(medicament.getProducator());
		auto substanta = QString::fromStdString(medicament.getSubstanta());

		auto linieTabel = id + '\t' + denumire + '\t' + pret + '\t' + producator + '\t' + substanta;

		listaReteta->addItem(linieTabel);
	}
}

void RetetaGUI::guiAdaugaMedicamentInReteta(){
	try {
		int id = editId->text().toInt();

		editId->clear();
		service.AdaugaInReteta(id);
		reloadLista(service.ReturneazaReteta());
	}
	catch (ExceptieRepository& exceptie) {
		QMessageBox::warning(this, "Warning", "Nu exista medicamentul cu id-ul cautat in lista de medicamente!");
	}
}

void RetetaGUI::guiAdaugaRandomInReteta() {
	int numar_random = editRandom->text().toInt();

	editRandom->clear();
	service.AdaugaRandomInReteta(numar_random);
	reloadLista(service.ReturneazaReteta());
}

void RetetaGUI::guiGolesteReteta() {
	service.GolesteReteta();
	reloadLista(service.ReturneazaReteta());
}

void RetetaGUI::guiExport() {
	try {
		string nume_fisier = editExport->text().toStdString();
		editExport->clear();
		service.ExportReteta(nume_fisier);
		QMessageBox::information(this, "Export", "Export realizat cu succes");
	}
	catch (ExceptieRepository& exceptie) {
		QMessageBox::warning(this, "Warning", "Eroare deschidere fisier");
	}
	
}
