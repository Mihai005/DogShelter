#pragma once

#include "Repository.h"
#include <memory>

class Action
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
};

class ActionAdd : public Action
{
	private:
	Repository& repo;
	Dog dog;
	public:
		ActionAdd(Repository& repo, Dog dog) : repo{ repo }, dog{ dog } {}
		void executeUndo() override
		{
			repo.removeDogRepo(dog);
		}
		void executeRedo() override
		{
			repo.addDogRepo(dog);
		}
};

class ActionRemove : public Action
{
	private:
	Repository& repo;
	Dog dog;
	public:
		ActionRemove(Repository& repo, Dog dog) : repo{ repo }, dog{ dog } {}
		void executeUndo() override
		{
			repo.addDogRepo(dog);
		}
		void executeRedo() override
		{
			repo.removeDogRepo(dog);
		}
};

class ActionUpdate : public Action
{
	private:
	Repository& repo;
	Dog* dog;
	string name;
	string breed;
	int age;

	public:
		ActionUpdate(Repository& repo, Dog* dog, string name, string breed, int age) : repo{ repo }, dog{ dog }, name{ name }, breed{ breed }, age{ age } {}
		void executeUndo() override
		{
			string n, b;
			int a;
			n = dog->getName();
			b = dog->getBreed();
			a = dog->getAge();
			repo.updateDogName(dog, name);
			repo.updateDogBreed(dog, breed);
			repo.updateDogAge(dog, age);
			this->name = n;
			this->breed = b;
			this->age = a;

		}
		void executeRedo() override
		{
			string n, b;
			int a;
			n = dog->getName();
			b = dog->getBreed();
			a = dog->getAge();
			repo.updateDogName(dog, name);
			repo.updateDogBreed(dog, breed);
			repo.updateDogAge(dog, age);
			this->name = n;
			this->breed = b;
			this->age = a;
		}
};
