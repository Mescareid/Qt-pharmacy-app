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
#include "MyListModel.h"
#include "MyTableModel.h"

using std::vector;
using std::string;

class FarmacieModelGUI : public QWidget {
private:
	Service& service;

	QLabel* labelId = new QLabel{ "Id-ul medicamentului:" };
	QLabel* labelDenumire = new QLabel{ "Denumirea medicamentului:" };
	QLabel* labelPret = new QLabel{ "Pretul medicamentului:" };
	QLabel* labelProducator = new QLabel{ "Producatorul medicamentului:" };
	QLabel* labelSubstanta = new QLabel{ "Substanta activa a medicamentului:" };

	QLineEdit* editId;
	QLineEdit* editDenumire;
	QLineEdit* editPret;
	QLineEdit* editProducator;
	QLineEdit* editSubstanta;

	QPushButton* butonAdaugaMedicament;
	QPushButton* butonStergeMedicament;

	QPushButton* butonModificaMedicament;
	QPushButton* butonUndo;

	QPushButton* butonImagini;
	QPushButton* butonReteta;

	QPushButton* butonReload;

	//QTableWidget* tabelMedicamente;
	//QListWidget* lista;

	QTableView* tabelModel = new QTableView;
	QListView* listaCuModel = new QListView;
	MyListModel* model;

	QPushButton* butonSorteazaDenumire;
	QPushButton* butonSorteazaProducator;
	QPushButton* butonSorteazaSubstantaPret;

	QPushButton* butonFiltreazaPret;
	QPushButton* butonFiltreazaSubstanta;

	void initializeazaGUI();

	void conecteazaSignalsSlots();
	void reloadLista(vector<Medicament> medicamente);

public:
	FarmacieModelGUI(Service& service) : service{ service } {
		initializeazaGUI();
		model = new MyListModel{ service.ReturneazaLista() };
		listaCuModel->setModel(model);
		listaCuModel->setUniformItemSizes(true);
		tabelModel->setModel(model);
		conecteazaSignalsSlots();
		reloadLista(service.ReturneazaLista());
	}

	void guiAdaugaMedicament();

	void guiStergeMedicament();

	void guiModificaMedicament();

	void guiUndo();
};