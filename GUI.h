#pragma once

#include "service.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QScrollArea>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QSlider>
#include <QDial>
#include <QLayout>
#include <QStackedWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>
#include <QKeyEvent>
#include <QShortcut>
#include <QKeySequence>
#include <QFileDialog>
#include <qshortcut.h>
#include <string>
#include "Exceptions.h"
#include <fstream>

class GUI : public QWidget
{
	Q_OBJECT
private:
	Service& service;
	QListWidget* adoptionList;
	QWidget* window = nullptr;
	QHBoxLayout* mainLayout = nullptr;
public:
	void adminMode();
	void userMode();
	void printDogsAdmin();
	void chooseMode();
	void chooseModeGoBack();
	void addDog();
	void removeDog();
	void updateDog();
	void updateBreed();
	void updateName();
	void updateAge();
	void updateBreedGUI(Dog* d);
	void updateNameGUI(Dog* d);
	void updateAgeGUI(Dog* d);
	void printDogsUser();
	void printDogsByBreed();
	void printAdoptionList();
	void printAdoptionListSystem();

	void undo();
	void redo();
	void adoptionListTable();
public:
	GUI(Service& service);
	~GUI() { delete adoptionList; }
};

class AdoptionListTableViewModel : public QAbstractTableModel
{
private:
	Service& service;
	vector<Dog> adoptedDogs;
public:
	AdoptionListTableViewModel(Service& service, QObject* parent = nullptr) : service{ service }, QAbstractTableModel{ parent }
	{
		Dog* beginIterator = this->service.getElementAdoption();
		Dog* endIterator = beginIterator + this->service.getSizeServiceAdoption();
	   for (Dog* it = beginIterator; it != endIterator; it++)
	   {
		   adoptedDogs.push_back(*it);
	   }
	}
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override
	{
		return this->adoptedDogs.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override
	{
		return 4;
	}
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		int row = index.row();
		int column = index.column();
		Dog d = this->adoptedDogs[row];
		if (role == Qt::DisplayRole)
		{
			switch (column)
			{
			case 0:
				return QString::fromStdString(d.getName());
			case 1:
				return QString::fromStdString(d.getBreed());
			case 2:
				return QString::fromStdString(to_string(d.getAge()));
			case 3:
				return QString::fromStdString(d.getPhotograph());
			default:
				break;
			}
		}
		return QVariant{};
	}
};