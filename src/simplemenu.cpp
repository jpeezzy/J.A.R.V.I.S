#include "simplemenu.h"
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QWidget>
#include <QGridLayout>
#include <QFont>
SimpleMenu::SimpleMenu(QWidget *parent)
	: QMainWindow(parent)
{
	/*this connect sends the text to backend (will do Later) */
	//jarvis.talk("does this even work?");
	std::cout <<"does it try to talk?>" << std::endl;
	jarvisThread = std::thread(&commands::intro, &jarvis);

	//jarvis.detatch();
	QAction *quit = new QAction("&Quit", this); //Qaction
	
	//text is QLabel pointer that prints a string to screen
	text = new QLabel("Hello World!", this);
	text->setAlignment(Qt::AlignCenter);
	text->setWordWrap(true);

	//makes text font bigger 
	QFont font = text->font();
	font.setPointSize(60);
	font.setBold(true);
	text->setFont(font);

	//Sets up a style sheet similar to css for dynamic parameters (color of background)
	QFile qFile("stylesheet.css");
	qFile.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(qFile.readAll());
	qApp->setStyleSheet(StyleSheet);
//documentation on style sheets here http://doc.qt.io/qt-4.8/stylesheet-reference.html

	//this shows the text box for inputting commands; 
	textBox = new QLineEdit;
	textBox->setPlaceholderText("input commands here");
	textBox->setMaxLength(30);
//This sets the layout where text is showed on top of the input text box;  
	QGridLayout *layout = new QGridLayout; 
	layout->addWidget(text);
	layout->addWidget(textBox,1,0);
	QWidget *window = new QWidget();
	window->setLayout(layout);	
	this->setCentralWidget(window);
	
	//this adds file button on top of application;
	QMenu *file;
	file = menuBar() -> addMenu("&File"); //Qmenuobject
	file->addAction(quit);//adds the option "quit under file menu" 

	connect(quit, &QAction::triggered, qApp, QApplication::quit);//when quit is slelected, app closes

	//this connects text box with the enter key, hopefully sending the message to the main program.
	//we do this by using connect, and using a functor(object that can be used () like a function
	
	//this connect sends the text from the text box into a std::string that can be send to the backend
	connect(textBox, &QLineEdit::returnPressed, text, [this]{text->setText(textBox->text());});
	connect(textBox, &QLineEdit::returnPressed, textBox, [this]{commandToString(textBox->text());});

	connect(textBox, &QLineEdit::returnPressed, textBox, &QLineEdit::clear);
	connect(textBox, &QLineEdit::returnPressed, textBox, [this]{backEnd();});

}

std::string SimpleMenu::getText()
{
	return textCommand; 
}

void SimpleMenu::commandToString(QString qText)
{
	//textCommand = qText.toStdString();
	textCommand = qText.toUtf8().constData();
	//std::cout << "WORD THAT IS PRINTED IS " << textCommand << std::endl;
	/*This also sends textcommand to the backend  */
	//jarvisThread= std::thread(&SimpleMenu::backEnd, this);
}

void SimpleMenu::backEnd()
{
	jarvis.storeQuestion(textCommand);
}

