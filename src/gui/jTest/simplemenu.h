#pragma once

#include <QMainWindow> 
#include <QApplication> //shows the windows
#include <QLabel>
#include <QGridLayout>
class SimpleMenu : public QMainWindow{

	public:
		SimpleMenu(QWidget *parent = 0);
		
	private:
		QLabel *text; 
};
