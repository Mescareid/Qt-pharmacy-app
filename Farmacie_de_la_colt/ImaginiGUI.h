#pragma once

#include <qwidget.h>
#include <qpainter.h>
#include <random>
#include "service.h"
#include "Observer.h"

class ImaginiGUI : public QWidget , public Observer{
private:
	Service& service;

public:
	ImaginiGUI(Service& service) : service{ service } {
		service.addObserver(this);
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* paintEvent) override{
		QPainter painter{ this };

		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, 600);

		

		//window size 600x435

		QImage poza_prea_mare("drugs.png");
		QImage pastila = poza_prea_mare.scaled(40, 40, Qt::KeepAspectRatio);

		int NumarDeImaginiDeSpawnat = service.ReturneazaReteta().size();
		
		for (int i{ 0 }; i < NumarDeImaginiDeSpawnat; ++i) {
			int x = dist(mt);
			int y = dist(mt) % 435;
			painter.drawImage(x, y, pastila);
		}
	}
};