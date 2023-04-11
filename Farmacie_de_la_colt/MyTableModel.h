#pragma once

#include <QAbstractTableModel>
#include "entities.h"
#include <vector>
#include <qdebug.h>

using std::vector;

class MyTableModel : public QAbstractItemModel {
private:
	vector<Medicament> medicamente;
public:
	MyTableModel(vector<Medicament> medicamente) : medicamente{ medicamente } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return medicamente.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		/*if (role == Qt::ForegroundRole) {
			Medicament medicament = medicamente[index.row()];
			if (medicament.getPret() > 0) {
				return QBrush{ Qt::red };
			}
		}*/
		if (role == Qt::DisplayRole) {

			Medicament medicament = medicamente[index.row()];
			if (index.column() == 0) {
				return QString::number(medicament.getId());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(medicament.getDenumire());
			}
			else if (index.column() == 2) {
				return QString::number(medicament.getPret());
			}
			else if (index.column() == 3) {
				return QString::fromStdString(medicament.getProducator());
			}
			else if (index.column() == 4) {
				return QString::fromStdString(medicament.getSubstanta());
			}
		}

		return QVariant{};
	}

	void seteazaLista(const vector<Medicament>& medicamente2) {
		this->medicamente = medicamente2;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}
};