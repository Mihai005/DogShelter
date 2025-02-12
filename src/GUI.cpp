#include "GUI.h"
#include <QMainWindow>

GUI::GUI(Service& service) : service{ service }
{
	this->chooseMode();
}

void GUI::userMode()
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("User Mode: ");
	label->setAlignment(Qt::AlignCenter);
	QPushButton* button1 = new QPushButton("Show dogs one by one");
	QPushButton* button2 = new QPushButton("See dogs with given breed and less than age");
	QPushButton* button3 = new QPushButton("See the adoption list");
	QPushButton* button4 = new QPushButton("See the adoption list in the system");
	QPushButton* button5 = new QPushButton("See the adoption list in Table View");
	QPushButton* button6 = new QPushButton("Go back");
	QVBoxLayout* Mainlayout = new QVBoxLayout();
	Mainlayout->addWidget(label);
	QHBoxLayout* layout = new QHBoxLayout();

	layout->addWidget(button1);
	layout->addWidget(button2);
	layout->addWidget(button3);
	layout->addWidget(button4);
	layout->addWidget(button5);
	layout->addWidget(button6);

	Mainlayout->addLayout(layout);

	connect(button1, &QPushButton::clicked, this, &GUI::printDogsUser);
	connect(button2, &QPushButton::clicked, this, &GUI::printDogsByBreed);
	connect(button3, &QPushButton::clicked, this, &GUI::printAdoptionList);
	connect(button4, &QPushButton::clicked, this, &GUI::printAdoptionListSystem);
	connect(button5, &QPushButton::clicked, this, &GUI::adoptionListTable);
	connect(button6, &QPushButton::clicked, this, &GUI::chooseModeGoBack);

	window->setLayout(Mainlayout);
	window->show();
}

void GUI::adminMode()
{
	window->close();
	window = new QWidget{};

	QVBoxLayout* Mainlayout = new QVBoxLayout(this);

	QLabel* label = new QLabel("Admin Mode: ");
	label->setAlignment(Qt::AlignCenter);

	QPushButton* button1 = new QPushButton("Show dogs");
	QPushButton* button2 = new QPushButton("Add dog");
	QPushButton* button3 = new QPushButton("Remove dog");
	QPushButton* button4 = new QPushButton("Update dog");
	QPushButton* button5 = new QPushButton("Undo");
	QPushButton* button6 = new QPushButton("Redo");
	QPushButton* button7 = new QPushButton("Go back");

	Mainlayout->addWidget(label);
	Mainlayout->addWidget(button1);
	Mainlayout->addWidget(button2);
	Mainlayout->addWidget(button3);
	Mainlayout->addWidget(button4);
	Mainlayout->addWidget(button5);
	Mainlayout->addWidget(button6);
	Mainlayout->addWidget(button7);

	connect(button1, &QPushButton::clicked, this, &GUI::printDogsAdmin);
	connect(button2, &QPushButton::clicked, this, &GUI::addDog);
	connect(button3, &QPushButton::clicked, this, &GUI::removeDog);
	connect(button4, &QPushButton::clicked, this, &GUI::updateDog);
	connect(button5, &QPushButton::clicked, this, &GUI::undo);
	connect(button6, &QPushButton::clicked, this, &GUI::redo);
	connect(button7, &QPushButton::clicked, this, &GUI::chooseModeGoBack);

	QShortcut* shortcutUndo = new QShortcut(QKeySequence("Ctrl+Z"), window);
	QShortcut* shortcutRedo = new QShortcut(QKeySequence("Ctrl+Y"), window);
	shortcutUndo->setContext(Qt::ApplicationShortcut);
	shortcutRedo->setContext(Qt::ApplicationShortcut);
	connect(shortcutUndo, &QShortcut::activated, this, &GUI::undo);
	connect(shortcutRedo, &QShortcut::activated, this, &GUI::redo);

	window->setLayout(Mainlayout);
	window->show();
}

void GUI::printDogsAdmin()
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Dogs: ");
	label->setAlignment(Qt::AlignCenter);
	QVBoxLayout* Mainlayout = new QVBoxLayout();
	QPushButton* button = new QPushButton("Go back");
	Mainlayout->addWidget(label);
	Mainlayout->addWidget(button);

	Dog* beginIterator = this->service.getElement();
	Dog* endIterator = beginIterator + this->service.getSizeService();
	for (Dog* ptr = beginIterator; ptr != endIterator; ++ptr)
	{
		Dog& d = *ptr;
		QLabel* dog = new QLabel(QString::fromStdString(d.Representation()));
		Mainlayout->addWidget(dog);
	}

	connect(button, &QPushButton::clicked, this, &GUI::adminMode);

	window->setLayout(Mainlayout);
	window->show();
}

void GUI::chooseMode()
{
	window = new QWidget{};
	mainLayout = new QHBoxLayout{ this };
	QLabel* label = new QLabel("Choose Mode: ");
	label->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(label);
	QPushButton* button1 = new QPushButton("Admin Mode");
	QPushButton* button2 = new QPushButton("User Mode");
	connect(button1, &QPushButton::clicked, this, &GUI::adminMode);
	connect(button2, &QPushButton::clicked, this, &GUI::userMode);

	QVBoxLayout* Mainlayout = new QVBoxLayout();
	Mainlayout->addWidget(label);
	QHBoxLayout* layout = new QHBoxLayout();

	layout->addWidget(button1);
	layout->addWidget(button2);
	Mainlayout->addLayout(layout);

	window->setLayout(Mainlayout);
	window->show();
}

void GUI::chooseModeGoBack()
{
	window->close();
	window = new QWidget{};
	// Make two buttons, one for admin mode and one for user mode
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	//this->adoptionList = new QListWidget{ };
	//mainLayout->addWidget(adoptionList);
	//QGridLayout* gridLayout = new QGridLayout{ };

	QLabel* label = new QLabel("Choose Mode: ");
	label->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(label);
	QPushButton* button1 = new QPushButton("Admin Mode");
	QPushButton* button2 = new QPushButton("User Mode");
	// If admin button is pressed, call adminMode
	connect(button1, &QPushButton::clicked, this, &GUI::adminMode);
	// If user button is pressed, call userMode
	connect(button2, &QPushButton::clicked, this, &GUI::userMode);

	QVBoxLayout* Mainlayout = new QVBoxLayout();
	Mainlayout->addWidget(label);
	QHBoxLayout* layout = new QHBoxLayout();

	layout->addWidget(button1);
	layout->addWidget(button2);
	Mainlayout->addLayout(layout);

	window->setLayout(Mainlayout);
	window->show();
}

void GUI::addDog()
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Add Dog: ");
	label->setAlignment(Qt::AlignCenter);
	QFormLayout* Mainlayout = new QFormLayout();
	Mainlayout->addWidget(label);
	QLineEdit* breed = new QLineEdit{};
	QLineEdit* name = new QLineEdit{};
	QLineEdit* age = new QLineEdit{};
	QLineEdit* photo = new QLineEdit{};
	QPushButton* button = new QPushButton("Add Dog");
	QPushButton* button2 = new QPushButton("Go back");
	Mainlayout->addRow("Breed: ", breed);
	Mainlayout->addRow("Name: ", name);
	Mainlayout->addRow("Age: ", age);
	Mainlayout->addRow("Photo: ", photo);
	Mainlayout->addWidget(button);
	Mainlayout->addWidget(button2);
	connect(button, &QPushButton::clicked, [=]() {
		string breedString = breed->text().toStdString();
		string nameString = name->text().toStdString();
		string ageString = age->text().toStdString();
		string photoString = photo->text().toStdString();
		//input validation
		try {
			DogValidator::validateBreed(breedString);
			DogValidator::validateName(nameString);
			DogValidator::validateAge(ageString);
			DogValidator::validatePhotograph(photoString);
			Dog d = Dog();
			d.CreateDog(nameString, breedString, stoi(ageString), photoString);
			this->service.checkAlreadyExists(d);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		int ageint = stoi(ageString);
		Dog d = Dog();
		d.CreateDog(breedString, nameString, ageint, photoString);
		this->service.addDogService(d);

		//popup that says the dog was added
		QMessageBox msgBox;
		msgBox.setText("Dog added!");
		msgBox.exec();
		this->adminMode();
		});
	connect(button2, &QPushButton::clicked, this, &GUI::adminMode);
	window->setLayout(Mainlayout);
	window->show();
}

void GUI::removeDog()
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Remove Dog: ");
	label->setAlignment(Qt::AlignCenter);
	QFormLayout* Mainlayout = new QFormLayout();
	Mainlayout->addWidget(label);
	QLineEdit* name = new QLineEdit{};
	QLineEdit* breed = new QLineEdit{};
	QLineEdit* age = new QLineEdit{};
	QPushButton* button = new QPushButton("Remove Dog");
	QPushButton* button2 = new QPushButton("Go back");
	Mainlayout->addRow("Breed: ", breed);
	Mainlayout->addRow("Name: ", name);
	Mainlayout->addRow("Age: ", age);
	Mainlayout->addWidget(button);
	Mainlayout->addWidget(button2);
	connect(button, &QPushButton::clicked, [=]() {
		string nameString = name->text().toStdString();
		string breedString = breed->text().toStdString();
		string ageString = age->text().toStdString();
		//input validation
		try {
			DogValidator::validateBreed(breedString);
			DogValidator::validateName(nameString);
			DogValidator::validateAge(ageString);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		int ageint = stoi(ageString);
		try {
			this->service.searchDogService(nameString, breedString, ageint);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		Dog* d = this->service.searchDogService(nameString, breedString, ageint);
		this->service.removeDogService(d);

		//popup that says the dog was removed
		QMessageBox msgBox;
		msgBox.setText("Dog removed!");
		msgBox.exec();
		this->adminMode();
		});
	connect(button2, &QPushButton::clicked, this, &GUI::adminMode);
	window->setLayout(Mainlayout);
	window->show();
}

void GUI::updateDog()
{
	window->close();
	window = new QWidget{};
	QPushButton* button = new QPushButton("Update breed");
	QPushButton* button2 = new QPushButton("Update name");
	QPushButton* button3 = new QPushButton("Update age");
	QPushButton* button4 = new QPushButton("Go back");
	QVBoxLayout* Mainlayout = new QVBoxLayout();
	Mainlayout->addWidget(button);
	Mainlayout->addWidget(button2);
	Mainlayout->addWidget(button3);
	Mainlayout->addWidget(button4);
	connect(button, &QPushButton::clicked, this, &GUI::updateBreed);
	connect(button2, &QPushButton::clicked, this, &GUI::updateName);
	connect(button3, &QPushButton::clicked, this, &GUI::updateAge);
	connect(button4, &QPushButton::clicked, this, &GUI::adminMode);

	window->setLayout(Mainlayout);
	window->show();
}

void GUI::updateBreed()
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Enter the dog: ");
	label->setAlignment(Qt::AlignCenter);
	QFormLayout* Mainlayout = new QFormLayout();
	Mainlayout->addWidget(label);
	QLineEdit* name = new QLineEdit{};
	QLineEdit* breed = new QLineEdit{};
	QLineEdit* age = new QLineEdit{};
	QPushButton* button = new QPushButton("Search dog");
	QPushButton* button2 = new QPushButton("Go back");
	Mainlayout->addRow("Breed: ", breed);
	Mainlayout->addRow("Name: ", name);
	Mainlayout->addRow("Age: ", age);

	Mainlayout->addWidget(button);
	Mainlayout->addWidget(button2);

	connect(button, &QPushButton::clicked, [=]() {
		string nameString = name->text().toStdString();
		string breedString = breed->text().toStdString();
		string ageString = age->text().toStdString();
		//input validation
		try {
			DogValidator::validateBreed(breedString);
			DogValidator::validateName(nameString);
			DogValidator::validateAge(ageString);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		int ageint = stoi(ageString);
		try {
			this->service.searchDogService(nameString, breedString, ageint);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		Dog* d = this->service.searchDogService(nameString, breedString, ageint);
		this->updateBreedGUI(d);
		});
	connect(button2, &QPushButton::clicked, this, &GUI::updateDog);
	window->setLayout(Mainlayout);
	window->show();
}

void GUI::updateBreedGUI(Dog* d)
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Update Breed: ");
	label->setAlignment(Qt::AlignCenter);
	QFormLayout* Mainlayout = new QFormLayout();
	Mainlayout->addWidget(label);
	QLineEdit* breed = new QLineEdit{};
	QPushButton* button = new QPushButton("Update Breed");
	QPushButton* button2 = new QPushButton("Go back");
	Mainlayout->addRow("New Breed: ", breed);
	Mainlayout->addWidget(button);
	Mainlayout->addWidget(button2);
	connect(button, &QPushButton::clicked, [=]() {
		string breedString = breed->text().toStdString();
		//input validation
		try {
			DogValidator::validateBreed(breedString);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		this->service.updateBreedService(d, breedString);

		//popup that says the dog was updated
		QMessageBox msgBox;
		msgBox.setText("Dog updated!");
		msgBox.exec();
		this->adminMode();
		});
	connect(button2, &QPushButton::clicked, this, &GUI::updateBreed);
	window->setLayout(Mainlayout);
	window->show();
}

void GUI::updateName()
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Enter the dog: ");
	label->setAlignment(Qt::AlignCenter);
	QFormLayout* Mainlayout = new QFormLayout();
	Mainlayout->addWidget(label);
	QLineEdit* name = new QLineEdit{};
	QLineEdit* breed = new QLineEdit{};
	QLineEdit* age = new QLineEdit{};
	QPushButton* button = new QPushButton("Search dog");
	QPushButton* button2 = new QPushButton("Go back");
	Mainlayout->addRow("Breed: ", breed);
	Mainlayout->addRow("Name: ", name);
	Mainlayout->addRow("Age: ", age);

	Mainlayout->addWidget(button);
	Mainlayout->addWidget(button2);

	connect(button, &QPushButton::clicked, [=]() {
		string nameString = name->text().toStdString();
		string breedString = breed->text().toStdString();
		string ageString = age->text().toStdString();
		//input validation
		try {
			DogValidator::validateBreed(breedString);
			DogValidator::validateName(nameString);
			DogValidator::validateAge(ageString);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		int ageint = stoi(ageString);
		try {
			this->service.searchDogService(nameString, breedString, ageint);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		Dog* d = this->service.searchDogService(nameString, breedString, ageint);
		this->updateNameGUI(d);
		});
	connect(button2, &QPushButton::clicked, this, &GUI::updateDog);
	window->setLayout(Mainlayout);
	window->show();
}

void GUI::updateNameGUI(Dog* d)
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Update Name: ");
	label->setAlignment(Qt::AlignCenter);
	QFormLayout* Mainlayout = new QFormLayout();
	Mainlayout->addWidget(label);
	QLineEdit* name = new QLineEdit{};
	QPushButton* button = new QPushButton("Update Name");
	QPushButton* button2 = new QPushButton("Go back");
	Mainlayout->addRow("New Name: ", name);
	Mainlayout->addWidget(button);
	Mainlayout->addWidget(button2);
	connect(button, &QPushButton::clicked, [=]() {
		string nameString = name->text().toStdString();
		//input validation
		try {
			DogValidator::validateName(nameString);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		this->service.updateNameService(d, nameString);

		//popup that says the dog was updated
		QMessageBox msgBox;
		msgBox.setText("Dog updated!");
		msgBox.exec();
		this->adminMode();
		});
	connect(button2, &QPushButton::clicked, this, &GUI::updateName);
	window->setLayout(Mainlayout);
	window->show();
}

void GUI::updateAge()
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Enter the dog: ");
	label->setAlignment(Qt::AlignCenter);
	QFormLayout* Mainlayout = new QFormLayout();
	Mainlayout->addWidget(label);
	QLineEdit* name = new QLineEdit{};
	QLineEdit* breed = new QLineEdit{};
	QLineEdit* age = new QLineEdit{};
	QPushButton* button = new QPushButton("Search dog");
	QPushButton* button2 = new QPushButton("Go back");
	Mainlayout->addRow("Breed: ", breed);
	Mainlayout->addRow("Name: ", name);
	Mainlayout->addRow("Age: ", age);

	Mainlayout->addWidget(button);
	Mainlayout->addWidget(button2);

	connect(button, &QPushButton::clicked, [=]() {
		string nameString = name->text().toStdString();
		string breedString = breed->text().toStdString();
		string ageString = age->text().toStdString();
		//input validation
		try {
			DogValidator::validateBreed(breedString);
			DogValidator::validateName(nameString);
			DogValidator::validateAge(ageString);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		int ageint = stoi(ageString);
		try {
			this->service.searchDogService(nameString, breedString, ageint);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		Dog* d = this->service.searchDogService(nameString, breedString, ageint);
		this->updateAgeGUI(d);
		});
	connect(button2, &QPushButton::clicked, this, &GUI::updateDog);
	window->setLayout(Mainlayout);
	window->show();
}

void GUI::updateAgeGUI(Dog* d)
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Update Age: ");
	label->setAlignment(Qt::AlignCenter);
	QFormLayout* Mainlayout = new QFormLayout();
	Mainlayout->addWidget(label);
	QLineEdit* age = new QLineEdit{};
	QPushButton* button = new QPushButton("Update Age");
	QPushButton* button2 = new QPushButton("Go back");
	Mainlayout->addRow("New Age: ", age);
	Mainlayout->addWidget(button);
	Mainlayout->addWidget(button2);
	connect(button, &QPushButton::clicked, [=]() {
		string ageString = age->text().toStdString();
		//input validation
		try {
			DogValidator::validateAge(ageString);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}
		int ageint = stoi(ageString);
		this->service.updateAgeService(d, ageint);

		//popup that says the dog was updated
		QMessageBox msgBox;
		msgBox.setText("Dog updated!");
		msgBox.exec();
		this->adminMode();
		});
	connect(button2, &QPushButton::clicked, this, &GUI::updateAge);
	window->setLayout(Mainlayout);
	window->show();
}

void GUI::printDogsUser()
{
	int currentDogIndex = 0;

	window->close();
	window = new QWidget{};

	QLabel* label = new QLabel("Dogs: ");
	label->setAlignment(Qt::AlignCenter);
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->addWidget(label);

	Dog* dogs = this->service.getElement();
	int dogCount = this->service.getSizeService();

	if (dogCount == 0)
	{
		QMessageBox msgBox;
		msgBox.setText("No dogs available!");
		msgBox.exec();
		this->userMode();
		return;
	}

	QLabel* dogLabel = new QLabel(QString::fromStdString(dogs[currentDogIndex].Representation()));
	mainLayout->addWidget(dogLabel);

	QPushButton* buttonAdopt = new QPushButton("Adopt");
	QPushButton* buttonNext = new QPushButton("Next");
	QPushButton* buttonExit = new QPushButton("Exit");
	mainLayout->addWidget(buttonAdopt);
	mainLayout->addWidget(buttonNext);
	mainLayout->addWidget(buttonExit);

	connect(buttonAdopt, &QPushButton::clicked, [=]() mutable {
		this->service.addAdoptionListService(&dogs[currentDogIndex]);
		this->service.removeDogService(&dogs[currentDogIndex]);
		ofstream file2("Dogs.txt");
		Dog* dogs2 = this->service.getElement();
		for (int i = 0; i < this->service.getSizeService(); i++)
		{
			Dog d = dogs2[i];
			file2 << d.getBreed() << "," << d.getName() << "," << d.getAge() << "," << d.getPhotograph() << "\n";
		}
		file2.close();
		QMessageBox msgBox;
		msgBox.setText("Dog adopted!");
		msgBox.exec();
		if (this->service.getSizeService() == 0)
		{
			QMessageBox msgBox;
			msgBox.setText("No dogs available!");
			msgBox.exec();
			this->userMode();
			return;
		}
		currentDogIndex = (currentDogIndex + 1) % dogCount;
		dogLabel->setText(QString::fromStdString(dogs[currentDogIndex].Representation()));
		});

	connect(buttonNext, &QPushButton::clicked, [=]() mutable {
		currentDogIndex = (currentDogIndex + 1) % dogCount;
		dogLabel->setText(QString::fromStdString(dogs[currentDogIndex].Representation()));
		});

	connect(buttonExit, &QPushButton::clicked, this, &GUI::userMode);

	window->setLayout(mainLayout);
	window->show();
}

void GUI::printDogsByBreed()
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Dogs: ");
	label->setAlignment(Qt::AlignCenter);
	QFormLayout* Mainlayout = new QFormLayout();
	Mainlayout->addWidget(label);
	QLineEdit* breed = new QLineEdit{};
	QLineEdit* age = new QLineEdit{};
	QPushButton* button = new QPushButton("Search");
	QPushButton* button2 = new QPushButton("Go back");
	Mainlayout->addRow("Breed: ", breed);
	Mainlayout->addRow("Age: ", age);
	Mainlayout->addWidget(button);
	Mainlayout->addWidget(button2);

	// Create a layout for displaying search results
	QVBoxLayout* resultsLayout = new QVBoxLayout();
	Mainlayout->addRow(resultsLayout);

	connect(button, &QPushButton::clicked, [=]() {
		// Clear previous search results
		QLayoutItem* item;
		while ((item = resultsLayout->takeAt(0)) != nullptr) {
			delete item->widget();
			delete item;
		}

		string breedString = breed->text().toStdString();
		string ageString = age->text().toStdString();

		// Input validation
		if (breedString.empty()) {
			// Print all dogs
			Dog* beginIterator = this->service.getElement();
			Dog* endIterator = beginIterator + this->service.getSizeService();
			for (Dog* ptr = beginIterator; ptr != endIterator; ++ptr)
			{
				Dog& d = *ptr;
				QLabel* dog = new QLabel(QString::fromStdString(d.Representation()));
				resultsLayout->addWidget(dog);
			}
			return;
		}

		try {
			DogValidator::validateBreed(breedString);
			DogValidator::validateAge(ageString);
		}
		catch (exception& e) {
			QMessageBox msgBox;
			msgBox.setText(e.what());
			msgBox.exec();
			return;
		}

		int ageInt = stoi(ageString);
		Dog* beginIterator = this->service.getElement();
		Dog* endIterator = beginIterator + this->service.getSizeService();
		for (Dog* ptr = beginIterator; ptr != endIterator; ++ptr)
		{
			Dog& d = *ptr;
			if (d.getBreed() == breedString && d.getAge() < ageInt)
			{
				QLabel* dog = new QLabel(QString::fromStdString(d.Representation()));
				resultsLayout->addWidget(dog);
			}
		}
		});

	connect(button2, &QPushButton::clicked, this, &GUI::userMode);
	window->setLayout(Mainlayout);
	window->show();
}

void GUI::printAdoptionList()
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Adoption List: ");
	label->setAlignment(Qt::AlignCenter);
	QVBoxLayout* Mainlayout = new QVBoxLayout();
	QPushButton* button = new QPushButton("Go back");
	Mainlayout->addWidget(label);
	Mainlayout->addWidget(button);

	Dog* beginIterator = this->service.getElementAdoption();
	Dog* endIterator = beginIterator + this->service.getSizeServiceAdoption();
	for (Dog* ptr = beginIterator; ptr != endIterator; ++ptr)
	{
		Dog& d = *ptr;
		QLabel* dog = new QLabel(QString::fromStdString(d.Representation()));
		Mainlayout->addWidget(dog);
	}

	connect(button, &QPushButton::clicked, this, &GUI::userMode);

	window->setLayout(Mainlayout);
	window->show();
}

void GUI::printAdoptionListSystem()
{
	window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Adoption List in the system: ");
	label->setAlignment(Qt::AlignCenter);
	QVBoxLayout* Mainlayout = new QVBoxLayout();
	string optionfile = this->service.getOptionFile();
	QPushButton* button = new QPushButton("Go back");

	Mainlayout->addWidget(label);
	Mainlayout->addWidget(button);

	if (optionfile == "html") {
		string filename = "file:///C:/Users/Mihai/Desktop/OOP/a9/AdoptedDogs.html";
		string command = "\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" " + filename;
		system(command.c_str());
	}
	if (optionfile == "csv") {
		string filename = "AdoptedDogs.csv";
		string command = "notepad.exe " + filename;
		system(command.c_str());
	}
	connect(button, &QPushButton::clicked, this, &GUI::userMode);

	window->setLayout(Mainlayout);
	window->show();
}

void GUI::undo()
{
	try {
		this->service.undo();
		QMessageBox::information(this, "Undo", "Undo was successful!");
	}
	catch (exception& e) {
		QMessageBox::information(this, "Undo", e.what());
	}
}

void GUI::redo()
{
	try {
		this->service.redo();
		QMessageBox::information(this, "Redo", "Redo was successful!");
	}
	catch (exception& e) {
		QMessageBox::information(this, "Redo", e.what());
	}
}

void GUI::adoptionListTable()
{
   window->close();
	window = new QWidget{};
	QLabel* label = new QLabel("Adoption List: ");
	label->setAlignment(Qt::AlignCenter);
	QVBoxLayout* Mainlayout = new QVBoxLayout();
	QPushButton* button = new QPushButton("Go back");
	Mainlayout->addWidget(label);
	Mainlayout->addWidget(button);

	QTableWidget* table = new QTableWidget(this->service.getSizeServiceAdoption(), 4);
	table->setHorizontalHeaderLabels(QStringList() << "Breed" << "Name" << "Age" << "Photo");
	Dog* beginIterator = this->service.getElementAdoption();
	Dog* endIterator = beginIterator + this->service.getSizeServiceAdoption();
	int row = 0;
	for (Dog* ptr = beginIterator; ptr != endIterator; ++ptr)
	{
		Dog& d = *ptr;
		table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(d.getBreed())));
		table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(d.getName())));
		table->setItem(row, 2, new QTableWidgetItem(QString::number(d.getAge())));
		table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(d.getPhotograph())));
		row++;
	}
	Mainlayout->addWidget(table);
	connect(button, &QPushButton::clicked, this, &GUI::userMode);
	window->setLayout(Mainlayout);
	window->show();
}
