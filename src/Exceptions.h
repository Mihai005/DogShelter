#pragma once
#include "Domain.h"
#include <vector>
#include <typeinfo>

class Exceptions : public exception
{
private:
	string message;
public:
	Exceptions(const string& message) : message{ message } {}
	const char* what() const noexcept override
	{
		return message.c_str();
	}
};

class DogValidator {
public:
	static void validateBreed(string breed)
	{
		if (breed.empty())
			throw Exceptions("Invalid breed!");
	}
	static void validateName(string name)
	{
		if (name.empty())
			throw Exceptions("Invalid name!");
		for (char c : name)
			if (!isalpha(c))
				throw Exceptions("Invalid name!");
	}
	static void validateAge(string age)
	{
		if (age.size() == 0)
			throw Exceptions("Invalid age!");
		for (char c : age)
			if (!isdigit(c))
				throw Exceptions("Invalid age!");
	}
	static void validatePhotograph(string link)
	{
		if (link.empty())
			throw Exceptions("Invalid link!");
		if (link.substr(0, 4) != "http")
			throw Exceptions("Invalid link!");
	}
};

class OptionValidator {
public:
	static void validateMenuAdmin(string option) {
		if (option != "0" && option != "1" && option != "2" && option != "3" && option != "4")
			throw Exceptions("Please enter a valid input!");
	}
	static void validateMenuUser(string optionuser) {
		if (optionuser != "0" && optionuser != "1" && optionuser != "2" && optionuser != "3" && optionuser != "4")
			throw Exceptions("Please enter a valid input!");
	}
	static void validateMenu(int option) {
		if (option != 0 && option != 1 && option != 2)
			throw Exceptions("Invalid option!");
	}
	static void validateAdminUpdate(string option)
	{
		if (option.compare("1") != 0 && option.compare("2") != 0 && option.compare("3") != 0)
			throw Exceptions("Invalid option!");
	}
	static void validateUserAdoption(string answer)
	{
		if (answer.compare("yes") != 0 && answer.compare("no") != 0 && answer.compare("0") != 0)
			throw Exceptions("Invalid option!");
	}
};

class RepositoryValidator {
public:
	static void validateAdd()
	{
		throw Exceptions("Dog already exists!");
	}
	static void validateRemove()
	{
		throw Exceptions("Dog does not exist!");
	}
};
