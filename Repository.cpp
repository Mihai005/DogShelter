#include "Repository.h"
#include <cassert>
#include <algorithm>
#include <fstream>
#include <sstream>


void Repository::addDogRepo(Dog dog)
{
	/// adds a dog to the repository
	//this->dogs.addElement(dog);
	this->dogs.push_back(dog);
}

void Repository::updateDogBreed(Dog* dog, string breed)
{
	/// updates the breed of a dog
	dog->setBreed(breed);
}

void Repository::updateDogName(Dog* dog, string name)
{
	/// updates the name of a dog
	dog->setName(name);
}

void Repository::updateDogAge(Dog* dog, int age)
{
	/// updates the age of a dog
	dog->setAge(age);
}

int Repository::getSizeRepo()
{
	/// returns the size of the repository
	//return this->dogs.getSize();
	return this->dogs.size();
}

int Repository::getSizeAdoptionList()
{
	/// returns the size of the adoption list
	//return this->adoptionList.getSize();
	return this->adoptionList.size();
}

int Repository::removeDogRepo(Dog dog)
{
	/// returns the index of a dog in the repository
	vector<Dog>::iterator pos = find(this->dogs.begin(), this->dogs.end(), dog);
	this->dogs.erase(pos);
	return 0;
}

Dog* Repository::getElements()
{
	/// returns the elements of the repository
	//return this->dogs.getElements();
	return this->dogs.data();
}

Dog* Repository::getElementsAdoption()
{
	/// returns the elements of the adoption list
	//return this->adoptionList.getElements();
	return this->adoptionList.data();
}

Dog* Repository::getElementRepo(int pos)
{
	/// returns the element from a given position
	//return this->dogs.getElement(pos);
	return &this->dogs[pos];
}

void Repository::addAdoptionListRepo(Dog* dog)
{
	/// adds a dog to the adoption list
	//this->adoptionList.addElement(*dog);
	this->adoptionList.push_back(*dog);
}

RepositoryFile::RepositoryFile(string filename)
{
	this->filename = filename;
}

void RepositoryFile::writeToFile()
{
	ofstream file("Dogs.txt");
	if (!file.is_open())
		return;
	for (auto& dog : this->dogs)
	{
		file << dog.getBreed() << "," << dog.getName() << "," << dog.getAge() << "," << dog.getPhotograph() << "\n";
	}
	file.close();
}

void RepositoryFile::writeAdoptionList()
{
	ofstream file(this->filename);
	if (!file.is_open())
		return;
	for (auto& dog : this->adoptionList)
	{
		file << dog.getBreed() << "," << dog.getName() << "," << dog.getAge() << "," << dog.getPhotograph() << "\n";
	}
	file.close();
}

void RepositoryFile::addDogRepo(Dog dog)
{
	/// adds a dog to the repository
	Repository::addDogRepo(dog);
	this->writeToFile();
}

void RepositoryFile::updateDogBreed(Dog* dog, string breed)
{
	/// updates the breed of a dog
	Repository::updateDogBreed(dog, breed);
	this->writeToFile();
}

void RepositoryFile::updateDogName(Dog* dog, string name)
{
	/// updates the name of a dog
	Repository::updateDogName(dog, name);
	this->writeToFile();
}

void RepositoryFile::updateDogAge(Dog* dog, int age)
{
	/// updates the age of a dog
	Repository::updateDogAge(dog, age);
	this->writeToFile();
}

void RepositoryFile::addAdoptionListRepo(Dog* d)
{
	/// adds a dog to the adoption list
	Repository::addAdoptionListRepo(d);
	this->writeAdoptionList();
}

int RepositoryFile::getSizeRepo()
{
	/// returns the size of the repository
	return Repository::getSizeRepo();
}

Dog* RepositoryFile::getElements()
{
	/// returns the elements of the repository
	return Repository::getElements();
}

Dog* RepositoryFile::getElementRepo(int pos)
{
	/// returns the element from a given position
	return Repository::getElementRepo(pos);
}

Dog* RepositoryFile::getElementsAdoption()
{
	/// returns the elements of the adoption list
	return Repository::getElementsAdoption();
}

int RepositoryFile::getSizeAdoptionList()
{
	/// returns the size of the adoption list
	return Repository::getSizeAdoptionList();
}

int RepositoryFile::removeDogRepo(Dog dog)
{
	/// returns the index of a dog in the repository
	int index = Repository::removeDogRepo(dog);
	this->writeToFile();
	return index;
}

void RepositoryFile::readFromFile()
{
	ifstream file(this->filename);
	if (!file.is_open())
		return;
	this->dogs.clear();
	string line;
	while (getline(file, line))
	{
		if (line == "")
			continue;
		vector<string> tokens;
		stringstream ss(line);
		string token;
		while (getline(ss, token, ','))
			tokens.push_back(token);
		if (tokens.size() != 4)
			continue;
		Dog d;
		d.CreateDog(tokens[0], tokens[1], stoi(tokens[2]), tokens[3]);
		this->addDogRepo(d);
	}
	file.close();
}

RepositoryFileCSV::RepositoryFileCSV(string filename) : RepositoryFile{ filename }
{

}

RepositoryFileHTML::RepositoryFileHTML(string filename) : RepositoryFile{ filename }
{

}

void RepositoryFileHTML::addAdoptionListRepo(Dog* dog)
{
	/// adds a dog to the adoption list
	Repository::addAdoptionListRepo(dog);
	ofstream file(filename);
	Dog* dogs = this->getElementsAdoption();
	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "<title>Adopted Dogs</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<table border=\"1\">\n";
	file << "<tr>\n";
	file << "<td>Breed</td>\n";
	file << "<td>Name</td>\n";
	file << "<td>Age</td>\n";
	file << "<td>Photograph</td>\n";
	file << "</tr>\n";
	for (int i = 0; i < this->getSizeAdoptionList(); i++)
	{
		Dog d = dogs[i];
		file << "<tr>\n";
		file << "<td>" << d.getBreed() << "</td>\n";
		file << "<td>" << d.getName() << "</td>\n";
		file << "<td>" << d.getAge() << "</td>\n";
		file << "<td><a href=" << d.getPhotograph() << ">Link</a></td>\n";
		file << "</tr>\n";
	}
	file << "</table>\n";
	file << "</body>\n";
	file << "</html>\n";
	file.close();
}