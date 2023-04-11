#pragma once

#include <algorithm>
#include <vector>

using std::vector;

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
	vector<Observer*> interesati;
protected:
	void notify() {
		for (auto observat : interesati) {
			observat->update();
		}
	}

public:
	void addObserver(Observer* observer) {
		interesati.push_back(observer);
	}

	void removeObserver(Observer* observer) {
		interesati.erase(std::remove(interesati.begin(), interesati.end(), observer));
	}
};