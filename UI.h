#pragma once

#include "Service.h"

class UI {
private:
	Service service;
public:
	UI(Service service);
	int run();
	~UI();
	int choosefile();
	void defaultshelter();
private:
	void choosemode(string& option);
	void printMenuAdmin(string& optionadmin);
	void printMenuUser(string& optionuser);
	//void defaultshelter();

	void printDogsUI();
	void addDogUI();
	void deleteDogUI();
	void updateDogUI();

	void printDogsUserUI();
	void printDogsByBreedUI();
	void printAdoptionListUI();
	void seeAdoptionListUI();

};