#include "Farmacie_de_la_colt.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include "user_interface.h"
#include "file_repository.h"
#include <vector>
#include <assert.h>
#include "FarmacieGUI.h"
#include "FarmacieModelGui.h"
#include <QListWidget>
#include <QSpinBox>

using std::cin;
using std::cout;

void Teste() {
	testeDomain();
	testeRepository();
	testeValidator();
	testeService();
}

int main(int argc, char *argv[])
{
	Teste();

	RepositoryFile repository{ "fisier.html" };
	//Repository repository;
	Validator validator;
	Service service{ repository, validator };

    QApplication a(argc, argv);
    //Farmacie_de_la_colt w;


	FarmacieGUI gui{ service };
	//FarmacieModelGUI gui{ service };
	gui.show();

    return a.exec();
}
