#pragma once

#include <iostream>
#include <string>

using namespace std;

class Dog {
private:
	string breed;
	string name;
	string photograph;
	int age;

public:
	Dog();
	void CreateDog(string breed, string name, int age, string photograph);
	const string getBreed();
	const string getName();
	const int getAge();
	const string getPhotograph();

	void setBreed(string b);
	void setName(string n);
	void setAge(int a);
	void setPhotograph(string p);

	string Representation() const {
		string representation = "Breed: ";
		representation += breed;
		representation += ", Name: ";
		representation += name;
		representation += ", Age: ";
		representation += to_string(age);
		representation += ", Photograph: ";
		representation += photograph;
		return representation;
	}

	bool operator==(const Dog& d) const {
		return ((this->name == d.name) && (this->breed == d.breed) && (this->age == d.age));
	}

	~Dog();

};