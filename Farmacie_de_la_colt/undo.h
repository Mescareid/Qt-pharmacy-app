#pragma once
#include "repository.h"
#include "entities.h"

class ActiuneUndo {
public:
	virtual void Undo() = 0;

	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Medicament medicament;
	Repository& repository;
public:
	UndoAdauga(Repository& repository, Medicament& medicament) : repository{ repository }, medicament{ medicament } {}

	void Undo() override {
		repository.Sterge(medicament.getId());
	}
};

class UndoSterge : public ActiuneUndo {
private:
	Medicament medicament;
	Repository& repository;
public:
	UndoSterge(Repository& repository, Medicament& medicament) : repository{ repository }, medicament{ medicament } {}

	void Undo() override {
		repository.Adauga(medicament);
	}
};

class UndoModifica : public ActiuneUndo {
private:
	int id;
	Medicament medicament;
	Repository& repository;
public:
	UndoModifica(Repository& repository, Medicament& medicament, int id) : repository{ repository }, medicament{ medicament }, id{ id } {}

	void Undo() override {
		repository.Modifica(id, medicament);
	}
};