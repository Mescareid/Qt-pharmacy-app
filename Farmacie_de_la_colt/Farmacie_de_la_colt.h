#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Farmacie_de_la_colt.h"

class Farmacie_de_la_colt : public QMainWindow
{
    Q_OBJECT

public:
    Farmacie_de_la_colt(QWidget *parent = Q_NULLPTR);

private:
    Ui::Farmacie_de_la_coltClass ui;
};
