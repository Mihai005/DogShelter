#include "Service.h"
#include "Exceptions.h"
#include <cassert>

int Service::getSizeService()
{
	/// getter for the size of the repository
	return this->repo->getSizeRepo();
}

int Service::getSizeServiceAdoption()
{
	/// getter for the size of the adoption list
	return this->repo->getSizeAdoptionList();
}

Dog* Service::getElement()
{
	/// getter for the elements of the repository
	return this->repo->getElements();
}

Dog* Service::getElementAdoption()
{
	/// getter for the elements of the adoption list
	return this->repo->getElementsAdoption();
}

Dog* Service::searchDogService(string name, string breed, int age)
{
	/// searches for a dog in the repository
	/// input: name, breed, age - strings
	/// output: the dog if it exists, an exception otherwise
	Dog* beginIterator = this->repo->getElements(); // Get pointer to beginning of the array
	Dog* endIterator = beginIterator + this->repo->getSizeRepo(); // Get pointer to end of the array

	for (Dog* ptr = beginIterator; ptr != endIterator; ++ptr)
	{
		Dog& d = *ptr;
		if (d.getName() == name && d.getBreed() == breed && d.getAge() == age)
			return &d;
	}
	//throw exception("Dog does not exist!");
	RepositoryValidator::validateRemove();
}

void Service::updateBreedService(Dog* d, string breed)
{
	/// updates the breed of a dog
	this->undoActions.push_back(new ActionUpdate(*this->repo, d, d->getName(), d->getBreed(), d->getAge()));
	this->redoActions.clear();
	this->repo->updateDogBreed(d, breed);
}

void Service::updateNameService(Dog* d, string name)
{
	/// updates the name of a dog
	this->undoActions.push_back(new ActionUpdate(*this->repo, d, d->getName(), d->getBreed(), d->getAge()));
	this->redoActions.clear();
	this->repo->updateDogName(d, name);
}

void Service::updateAgeService(Dog* d, int age)
{
	/// updates the age of a dog
	this->undoActions.push_back(new ActionUpdate(*this->repo, d, d->getName(), d->getBreed(), d->getAge()));
	this->redoActions.clear();
	this->repo->updateDogAge(d, age);
}

void Service::removeDogService(Dog* d)
{
	Dog* copy = new Dog(*d);
	this->repo->removeDogRepo(*d);
	this->undoActions.push_back(new ActionRemove(*this->repo, *copy));
	this->redoActions.clear();
}

void Service::addDogService(Dog d)
{
	/// adds a dog to the repository
	this->repo->addDogRepo(d);
	this->undoActions.push_back(new ActionAdd(*this->repo, d));
	this->redoActions.clear();
}

void Service::addAdoptionListService(Dog* d)
{
	/// adds a dog to the adoption list
	this->repo->addAdoptionListRepo(d);
}

int Service::checkInput(string breed, string name, int age, string link)
{
	/// checks if the input is valid
	if (breed.size() == 0 || (breed[0] >= '0' && breed[0] <= '9'))
		throw Exceptions("Invalid breed!");
	if (name.size() == 0 || (name[0] >= '0' && name[0] <= '9'))
		throw Exceptions("Invalid name!");
	if (age < 0)
		throw Exceptions("Invalid age!");
	if (link.substr(0, 4) != "http")
		throw Exceptions("Invalid link!");
	return 1;
}

int Service::checkAlreadyExists(Dog d)
{
	/// checks if a dog already exists in the repository
	/// input: d - Dog
	/// output: 1 if the dog already exists, 0 otherwise
	Dog* beginIterator = this->repo->getElements(); // Get pointer to beginning of the array
	Dog* endIterator = beginIterator + this->repo->getSizeRepo(); // Get pointer to end of the array
	for (Dog* ptr = beginIterator; ptr != endIterator; ++ptr)
	{
		Dog& dog = *ptr;
		if (dog == d)
			RepositoryValidator::validateAdd();
	}
	return 1;
}

string Service::getOptionFile()
{
	string option = this->repo->getFileName();
	if (option.compare("AdoptedDogs.csv") == 0)
		return "csv";
	else
		return "html";
}

Service::~Service()
{

}

void Service::undo()
{
	if (this->undoActions.empty())
		throw Exceptions("No more undos!");

	auto action = this->undoActions.back();
	this->undoActions.pop_back();
	action->executeUndo();
	this->redoActions.push_back(action); 

}

void Service::redo()
{
	if (this->redoActions.empty())
		throw Exceptions("No more redos!");

	auto action = this->redoActions.back();
	this->redoActions.pop_back();
	action->executeRedo();
	this->undoActions.push_back(action); 
}