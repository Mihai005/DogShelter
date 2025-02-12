#include "UI.h"
#include "Exceptions.h"
#include <exception>
#include <crtdbg.h>
#include <fstream>
#include <sstream>

using namespace std;

UI::UI(Service service) : service(service)
{

}

void UI::printMenuAdmin(string& optionadminstr)
{
	cout << "Choose one option:\n";
	cout << "1. Add dog.\n";
	cout << "2. Delete dog.\n";
	cout << "3. Update dog.\n";
	cout << "4. Print dogs.\n";
	cout << "0. Logout.\n";
	cout << "Option: ";
	getline(cin, optionadminstr);
	cout << "\n";
	OptionValidator::validateMenuAdmin(optionadminstr);
}

void UI::printMenuUser(string& optionuser)
{
	cout << "Choose one option:\n";
	cout << "1. See the dogs one by one\n";
	cout << "2. See the dogs by breed and less than age\n";
	cout << "3. See the adoption list\n";
	cout << "4. See the adoption list in the system\n";
	cout << "0. Logout.\n";
	cout << "Option: ";
	getline(cin, optionuser);
	cout << "\n";
	OptionValidator::validateMenuUser(optionuser);
}

void UI::defaultshelter()
{
	if (this->service.getSizeService() != 0)
		return;
	string breed, name, age, photograph;
	ifstream file("Dogs.txt");
	string line;
	while (getline(file, line)) {
		string breed, name, ageStr, photograph;
		stringstream ss(line);
		getline(ss, breed, ',');
		getline(ss, name, ',');
		getline(ss, ageStr, ',');
		getline(ss, photograph);
		int age = stoi(ageStr);
		Dog d = Dog();
		d.CreateDog(breed, name, age, photograph);
		this->service.addDogService(d);
	}
	file.close();
}

int UI::run()
{
	this->defaultshelter();
	int option;
	string input;
	cout << "Welcome to 'Keep calm and adopt a pet!' shelter!\n";
	bool ok;
	do {
		try {
			ok = true;
			this->choosemode(input);
		}
		catch (exception& e) {
			ok = false;
			cout << e.what() << "\n";
		}
	} while (!ok);
	option = stoi(input);
	if (option == 1)
	{
		string optionadminstr;
		while (true) {
			do {
				try {
					ok = true;
					this->printMenuAdmin(optionadminstr);
				}
				catch (exception& e) {
					ok = false;
					cout << e.what() << "\n";
				}
			} while (!ok);
			int optionadmin = stoi(optionadminstr);
			switch (optionadmin) {
			case 1:
				this->addDogUI();
				break;
			case 2:
				this->deleteDogUI();
				break;
			case 3:
				this->updateDogUI();
				break;
			case 4:
				this->printDogsUI();
				break;
			case 0:
				this->run();
				return 0;
			}
		}
	}
	else
	{
		string optionuser;
		while (true) {
			do {
				try {
					ok = true;
					this->printMenuUser(optionuser);
				}
				catch (exception& e) {
					ok = false;
					cout << e.what() << "\n";
				}
			} while (!ok);
			int optionuserint = stoi(optionuser);
			switch (optionuserint) {
			case 1:
				this->printDogsUserUI();
				break;
			case 2:
				this->printDogsByBreedUI();
				break;
			case 3:
				this->printAdoptionListUI();
				break;
			case 4:
				this->seeAdoptionListUI();
				break;
			case 0:
				this->run();
				return 0;
			}
		}
	}
}

void UI::printDogsUI()
{
	Dog* beginIterator = this->service.getElement();
	Dog* endIterator = beginIterator + this->service.getSizeService();
	if (beginIterator == endIterator)
		cout << "There aren't any dogs in the shelter!";
	for (Dog* ptr = beginIterator; ptr != endIterator; ++ptr)
	{
		Dog& d = *ptr;
		cout << d.Representation() << "\n";
	}
	cout << "\n";
}

void UI::addDogUI()
{
	bool ok;
	string breed;
	do {
		try {
			ok = true;
			cout << "Enter the breed of the dog: ";
			getline(cin, breed);
			DogValidator::validateBreed(breed);
		}
		catch (exception& e)
		{
			ok = false;
			cout << e.what() << "\n";
		}
	} while (!ok);
	string name;
	do {
		try {
			ok = true;
			cout << "Enter the name of the dog: ";
			getline(cin, name);
			DogValidator::validateName(name);
		}
		catch (exception& e)
		{
			ok = false;
			cout << e.what() << "\n";
		}
	} while (!ok);
	string age;
	do {
		try {
			ok = true;
			cout << "Enter the age of the dog: ";
			getline(cin, age);
			DogValidator::validateAge(age);
		}
		catch (exception& e)
		{
			ok = false;
			cout << e.what() << "\n";
		}
	} while (!ok);
	int ageint = stoi(age);
	string photograph;
	do {
		try {
			ok = true;
			cout << "Enter the link to the photograph: ";
			getline(cin, photograph);
			DogValidator::validatePhotograph(photograph);
		}
		catch (exception& e)
		{
			ok = false;
			cout << e.what() << "\n";
		}
	} while (!ok);
	Dog d = Dog();
	d.CreateDog(breed, name, ageint, photograph);
	try {
		ok = true;
		this->service.checkAlreadyExists(d);
	}
	catch (exception& e)
	{
		ok = false;
		cout << e.what() << "\n";
	}
	if (ok == true)
	{
		this->service.addDogService(d);

		ofstream file("Dogs.txt");
		Dog* dogs = this->service.getElement();
		for (int i = 0; i < this->service.getSizeService(); i++)
		{
			Dog d = dogs[i];
			file << d.getBreed() << "," << d.getName() << "," << d.getAge() << "," << d.getPhotograph() << "\n";
		}
		file.close();

		cout << "The dog was added!\n";
	}
}

void UI::choosemode(string& input)
{
	cout << "Please choose how you want to login:\n";
	cout << "1. admin\n";
	cout << "2. user\n";
	cout << "0. Exit\n";
	cout << "Option: ";
	getline(cin, input);
	int choice = stoi(input);
	OptionValidator::validateMenu(choice);
	if (choice == 1)
		cout << "Welcome admin\n";
	else if (choice == 2)
		cout << "Welcome user\n";
	else if (choice == 0)
		exit(0);
}

void UI::deleteDogUI()
{
	string name;
	cout << "Enter the name of the dog: ";
	getline(cin, name);
	string breed;
	cout << "Enter the breed of the dog: ";
	getline(cin, breed);
	string age;
	cout << "Enter the age of the dog: ";
	getline(cin, age);
	try {
		DogValidator::validateAge(age);
	}
	catch (exception& e)
	{
		cout << "Dog not found!\n";
		return;
	}
	int ageint = stoi(age);
	bool ok = false;
	try {
		ok = true;
		this->service.searchDogService(name, breed, ageint);
	}
	catch (exception& e)
	{
		ok = false;
		cout << e.what() << "\n";
	}
	if (ok == true) {
		Dog* d = this->service.searchDogService(name, breed, ageint);
		this->service.removeDogService(d);
		cout << "The dog was removed!\n";
	}
	ofstream file("Dogs.txt");
	Dog* dogs = this->service.getElement();
	for (int i = 0; i < this->service.getSizeService(); i++)
	{
		Dog d = dogs[i];
		file << d.getBreed() << "," << d.getName() << "," << d.getAge() << "," << d.getPhotograph() << "\n";
	}
	file.close();
}

void UI::updateDogUI()
{
	string option;
	bool ok;
	do {
		try {
			ok = true;
			cout << "List of possible updates: \n";
			cout << "1. Update breed\n";
			cout << "2. Update name\n";
			cout << "3. Update age\n";
			cout << "0. Go back\n";
			cout << "What do you want to update?: ";
			getline(cin, option);
			if (option == "0")
				return;
			OptionValidator::validateAdminUpdate(option);
		}
		catch (exception& e)
		{
			ok = false;
			cout << e.what() << "\n";
		}
	} while (!ok);
	int optionint = stoi(option);
	cout << "Enter the name of the dog: ";
	string name;
	getline(cin, name);
	cout << "Enter the breed of the dog: ";
	string breed;
	getline(cin, breed);
	string age;
	cout << "Enter the age of the dog: ";
	getline(cin, age);
	try {
		DogValidator::validateAge(age);
	}
	catch (exception& e)
	{
		cout << "Dog not found!\n";
		return;
	}
	int ageint = stoi(age);
	try {
		this->service.searchDogService(name, breed, ageint);
	}
	catch (exception& e)
	{
		cout << e.what() << "\n";
		return;
	}
	string new_breed;
	string new_name;
	string new_age;
	Dog* d = this->service.searchDogService(name, breed, ageint);
	switch (optionint)
	{
	case 1:
		cout << "Enter the new breed: ";
		getline(cin, new_breed);
		try {
			DogValidator::validateBreed(new_breed);
		}
		catch (exception& e)
		{
			cout << e.what() << "\n";
			return;
		}
		this->service.updateBreedService(d, new_breed);
		break;
	case 2:
		cout << "Enter the new name: ";
		getline(cin, new_name);
		try {
			DogValidator::validateName(new_name);
		}
		catch (exception& e)
		{
			cout << e.what() << "\n";
			return;
		}
		this->service.updateNameService(d, new_name);
		break;
	case 3:
		cout << "Enter the new age: ";
		getline(cin, new_age);
		try {
			DogValidator::validateAge(new_age);
		}
		catch (exception& e)
		{
			cout << e.what() << "\n";
			return;
		}
		int new_ageint = stoi(new_age);
		this->service.updateAgeService(d, new_ageint);
		break;
	}

	cout << "The dog was updated!\n";

	ofstream file("Dogs.txt");
	Dog* dogs = this->service.getElement();
	for (int i = 0; i < this->service.getSizeService(); i++)
	{
		Dog d = dogs[i];
		file << d.getBreed() << "," << d.getName() << "," << d.getAge() << "," << d.getPhotograph() << "\n";
	}
	file.close();
}

void UI::printDogsUserUI()
{
	int j = 0;
	j = this->service.getSizeService();
	Dog* d = this->service.getElement();
	if (j == 0)
		cout << "There aren't any dogs in the shelter!";
	int i = 0;
	while (i < j)
	{
		cout << d[i].Representation() << "\n";
		string answer;
		bool ok;
		do {
			try {
				ok = true;
				cout << "Do you want to adopt this dog? (yes/no)\n";
				cout << "0. Go back\n";
				cout << "Answer: ";
				getline(cin, answer);
				OptionValidator::validateUserAdoption(answer);
			}
			catch (exception& e)
			{
				ok = false;
				cout << e.what() << "\n";
			}
		} while (!ok);
		if (answer == "yes")
		{
			this->service.addAdoptionListService(&d[i]);
			this->service.removeDogService(&d[i]);
			cout << "You adopted the dog!\n";
			ofstream file2("Dogs.txt");
			Dog* dogs2 = this->service.getElement();
			for (int i = 0; i < this->service.getSizeService(); i++)
			{
				Dog d = dogs2[i];
				file2 << d.getBreed() << "," << d.getName() << "," << d.getAge() << "," << d.getPhotograph() << "\n";
			}
			file2.close();
		}
		else if (answer == "no")
			i++;
		else
			return;
		if (i == j)
			i = 0;
	}
}

void UI::printDogsByBreedUI()
{
	string breed, age;
	cout << "Enter the breed: ";
	getline(cin, breed);
	if (breed.empty())
	{
		int j = 0;
		j = this->service.getSizeService();
		Dog* d = this->service.getElement();
		if (j == 0)
			cout << "There aren't any dogs in the shelter!";
		for (int i = 0; i < j; i++)
			cout << d[i].Representation() << "\n";
		cout << "\n";
		return;
	}
	cout << "Enter the age: ";
	getline(cin, age);
	try {
		DogValidator::validateAge(age);
	}
	catch (exception& e)
	{
		cout << "Invalid age!\n";
		return;
	}
	int ageint = stoi(age);
	int j = 0;
	j = this->service.getSizeService();
	Dog* d = this->service.getElement();
	if (j == 0)
		cout << "There aren't any dogs in the shelter!";
	bool found = false;
	for (int i = 0; i < j; i++)
		if (d[i].getBreed() == breed && d[i].getAge() <= ageint)
		{
			cout << d[i].Representation() << "\n";
			found = true;
		}
	if (found == false)
		cout << "There aren't any dogs with the given breed and less than age!\n";
}

void UI::printAdoptionListUI()
{
	Dog* beginIterator = this->service.getElementAdoption();
	Dog* endIterator = beginIterator + this->service.getSizeServiceAdoption();
	if (beginIterator == endIterator)
		cout << "There aren't any dogs in the adoption list!";
	for (Dog* ptr = beginIterator; ptr != endIterator; ++ptr)
	{
		Dog& d = *ptr;
		cout << d.Representation() << "\n";
	}
	cout << "\n";
}

int UI::choosefile()
{
	string optionfile;
	optionfile = this->service.getOptionFile();
	int optionfileint;
	if (optionfile == "csv")
		optionfileint = 1;
	else
		optionfileint = 2;
	return optionfileint;
}

void UI::seeAdoptionListUI()
{
	int optionfileint = this->choosefile();
	if (this->service.getSizeServiceAdoption() == 0)
	{
		cout << "There aren't any dogs in the adoption list!\n";
		return;
	}
	if (optionfileint == 1)
	{
		string filename = "AdoptedDogs.csv";
		string command = "notepad.exe " + filename;
		system(command.c_str());
	}
	else if (optionfileint == 2)
	{
		string filename = "file:///C:/Users/Mihai/Documents/GitHub/oop-a6-7-Mihai005/a6-7/AdoptedDogs.html";
		string command = "\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" " + filename;
		system(command.c_str());
	}
	else
	{
		cout << "Invalid option!\n";
		return;
	}
}

UI::~UI()
{

}