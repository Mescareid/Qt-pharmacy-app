/********************************************************************************
** Form generated from reading UI file 'Farmacie_de_la_colt.ui'
**
** Created by: Qt User Interface Compiler version 6.0.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FARMACIE_DE_LA_COLT_H
#define UI_FARMACIE_DE_LA_COLT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Farmacie_de_la_coltClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Farmacie_de_la_coltClass)
    {
        if (Farmacie_de_la_coltClass->objectName().isEmpty())
            Farmacie_de_la_coltClass->setObjectName(QString::fromUtf8("Farmacie_de_la_coltClass"));
        Farmacie_de_la_coltClass->resize(600, 400);
        menuBar = new QMenuBar(Farmacie_de_la_coltClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Farmacie_de_la_coltClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Farmacie_de_la_coltClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Farmacie_de_la_coltClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Farmacie_de_la_coltClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Farmacie_de_la_coltClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Farmacie_de_la_coltClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Farmacie_de_la_coltClass->setStatusBar(statusBar);

        retranslateUi(Farmacie_de_la_coltClass);

        QMetaObject::connectSlotsByName(Farmacie_de_la_coltClass);
    } // setupUi

    void retranslateUi(QMainWindow *Farmacie_de_la_coltClass)
    {
        Farmacie_de_la_coltClass->setWindowTitle(QCoreApplication::translate("Farmacie_de_la_coltClass", "Farmacie_de_la_colt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Farmacie_de_la_coltClass: public Ui_Farmacie_de_la_coltClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FARMACIE_DE_LA_COLT_H
