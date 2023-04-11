#pragma once

#include <QAbstractListModel>
#include "entities.h"
#include <vector>
#include <qdebug.h>
#include <string.h>

using std::vector;

class MyListModel : public QAbstractListModel {
private:
	vector<Medicament> medicamente;

public:
	MyListModel(const vector<Medicament>& medicamente) : medicamente{ medicamente } {}

	int rowCount(const QModelIndex &parent = QModelIndex()) const override {
		return medicamente.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			qDebug() << "get row:" << index.row();
			auto id = medicamente[index.row()].getId();
			auto denumire = medicamente[index.row()].getDenumire();
			auto pret = medicamente[index.row()].getPret();
			auto producator = medicamente[index.row()].getProducator();
			auto substanta = medicamente[index.row()].getSubstanta();

			auto tab = QString::fromStdString("\t");
			QString linie = QString::number(id) + tab + QString::fromStdString(denumire)
				+ tab + QString::number(pret) + tab + QString::fromStdString(producator) + tab +
				QString::fromStdString(substanta);
			
			return linie;
		}
		if (role == Qt::UserRole) {
			auto denumire = medicamente[index.row()].getDenumire();
			return QString::fromStdString(denumire);
		}

		return QVariant{};
	}
	void seteazaLista(const vector<Medicament>& medicamente2) {
		this->medicamente = medicamente2;
		/*QModelIndex index;
		int row = index.row();
		int column = index.column();
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(),0);
		emit dataChanged(topLeft, bottomR);*/

		auto index = createIndex(rowCount(), 0);

		emit dataChanged(index, index);
	}
};