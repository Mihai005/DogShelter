#pragma once

#include "Domain.h"
#include <vector>
#include <typeinfo>

class Repository {
protected:
	vector<Dog> dogs;
	vector<Dog> adoptionList;
public:
	Repository() = default;
	virtual void addDogRepo(Dog dog) = 0;
	virtual void updateDogBreed(Dog* dog, string breed) = 0;
	virtual void updateDogName(Dog* dog, string name) = 0;
	virtual void updateDogAge(Dog* dog, int age) = 0;
	virtual void addAdoptionListRepo(Dog* dog) = 0;
	virtual int getSizeRepo() = 0;
	virtual Dog* getElements() = 0;
	virtual Dog* getElementRepo(int pos) = 0;
	virtual Dog* getElementsAdoption() = 0;
	virtual int getSizeAdoptionList() = 0;
	virtual int removeDogRepo(Dog dog) = 0;
	virtual ~Repository() = default;

	virtual string getFileName() const = 0;
};

class RepositoryFile : public Repository {
protected:
	string filename;
public:
	RepositoryFile(string filename);
	virtual void addDogRepo(Dog dog) override;
	virtual void updateDogBreed(Dog* dog, string breed) override;
	virtual void updateDogName(Dog* dog, string name) override;
	virtual void updateDogAge(Dog* dog, int age) override;
	virtual void addAdoptionListRepo(Dog* dog) override;
	virtual int getSizeRepo() override;
	virtual Dog* getElements() override;
	virtual Dog* getElementRepo(int pos) override;
	virtual Dog* getElementsAdoption() override;
	virtual int getSizeAdoptionList() override;
	virtual int removeDogRepo(Dog dog) override;
	virtual ~RepositoryFile() = default;

	void readFromFile();
	void writeToFile();
	void writeAdoptionList();

	virtual string getFileName() const = 0;
};

class RepositoryFileCSV : public RepositoryFile {
public:
	RepositoryFileCSV(string filename);
	~RepositoryFileCSV() = default;
	string getFileName() const override { return this->filename; };
};

class RepositoryFileHTML : public RepositoryFile {
public:
	RepositoryFileHTML(string filename);
	void addAdoptionListRepo(Dog* dog) override;
	~RepositoryFileHTML() = default;
	string getFileName() const override { return this->filename; };
};