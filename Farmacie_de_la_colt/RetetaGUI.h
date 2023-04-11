#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <qlistwidget.h>
#include "service.h"
#include "Observer.h"

using std::vector;
using std::string;

class RetetaGUI : public QWidget, public Observer{
	Service& service;

	QLabel* labelId = new QLabel{ "Id-ul medicamentului:" };
	QLineEdit* editId;

	QLabel* labelRandom = new QLabel{ "Numarul de medicamente de adaugat:" };
	QLineEdit* editRandom;

	QLabel* labelExport = new QLabel{ "Locatia de export: " };
	QLineEdit* editExport;

	QPushButton* butonAdaugaMedicament;
	QPushButton* butonAdaugaRandom;
	QPushButton* butonGolesteReteta;
	QPushButton* butonExport;

	QListWidget* listaReteta;

	void initializeazaGUI();

	void conecteazaSignalsSlots();
	void reloadLista(vector<Medicament> medicamente);

	void update() override {
		reloadLista(service.ReturneazaReteta());
	}

public:
	RetetaGUI(Service& service) : service{ service } {
		initializeazaGUI();
		conecteazaSignalsSlots();
		reloadLista(service.ReturneazaReteta());
	}

	void guiAdaugaMedicamentInReteta();

	void guiAdaugaRandomInReteta();

	void guiGolesteReteta();

	void guiExport();
};