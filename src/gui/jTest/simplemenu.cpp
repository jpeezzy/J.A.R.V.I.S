#include "simplemenu.h"
#include <QMenu>
#include <QMenuBar>
#include <QPixmap>
#include <QFile>
#include <QWidget>
#include <QGridLayout>
#include <QFont>
SimpleMenu::SimpleMenu(QWidget *parent)
	: QMainWindow(parent) 
{
	QAction *quit = new QAction("&Quit", this); //Qaction
	
	//text is QLabel pointer that prints a string to screen
	text = new QLabel("Hello World!", this);
	text->setAlignment(Qt::AlignCenter);

	//makes text font bigger 
	QFont font = text->font();
	font.setPointSize(72);
	font.setBold(true);
	text->setFont(font);
	//gets the string and places it in the center;
	this->setCentralWidget(text);

	//widget->show();
	//Sets up a style sheet similar to css for dynamic parameters (color of background)
	QFile qFile("stylesheet.css");
	qFile.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(qFile.readAll());
	
	qApp->setStyleSheet(StyleSheet);
//documentation on style sheets here http://doc.qt.io/qt-4.8/stylesheet-reference.html

	QMenu *file;
	file = menuBar() -> addMenu("&File"); //Qmenuobject
	file->addAction(quit);//adds the option "quit under file menu" 

	connect(quit, &QAction::triggered, qApp, QApplication::quit);//when quit is slelected, app closes

}
