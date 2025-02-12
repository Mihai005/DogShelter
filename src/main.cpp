#include "a10.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSlider>
#include <QtWidgets/QDial>
#include <QtWidgets/QLayout>
#include "UI.h"
#include "GUI.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	QWidget* main = new QWidget{};
	QVBoxLayout* vL = new QVBoxLayout(main);
	QPushButton* btnCSV = new QPushButton("CSV", main);
	QPushButton* btnHTML = new QPushButton("HTML", main);
	vL->addWidget(btnCSV);
	vL->addWidget(btnHTML);
	main->show();
	main->setWindowTitle("Choose Repository Type");
	main->setFixedHeight(main->sizeHint().height());
	main->setFixedWidth(main->sizeHint().width());
	Repository* repo = nullptr;
	Service* service = nullptr;
	GUI* gui = nullptr;

	QObject::connect(btnCSV, &QPushButton::clicked, [&]() {
		repo = new RepositoryFileCSV("AdoptedDogs.csv");
		service = new Service(repo);
		UI ui = Service(repo);
		ui.defaultshelter();
		gui = new GUI(*service);
		main->close();
		});

	QObject::connect(btnHTML, &QPushButton::clicked, [&]() {
		repo = new RepositoryFileHTML("AdoptedDogs.html");
		service = new Service(repo);
		UI ui = Service(repo);
		ui.defaultshelter();
		gui = new GUI(*service);
		main->close();
		});

	return a.exec();
}

/*
Husky,Rex,1,https://shelter/link1.com
Golden Retriever,Max,2,https://shelter/link2.com
Labrador,Bella,3,https://shelter/link3.com
Pug,Luna,4,https://shelter/link4.com
Beagle,Charlie,5,https://shelter/link5.com
Poodle,Lucy,6,https://shelter/link6.com
Dalmatian,Daisy,7,https://shelter/link7.com
German Shepherd,Rocky,8,https://shelter/link8.com
Chihuahua,Bailey,9,https://shelter/link9.com
Pomeranian,Sadie,10,https://shelter/link10.com
*/
