#pragma once
#include "commands.h" //gives the backend information 
#include <iostream>
#include <QMainWindow> 
#include <QApplication> //shows the windows
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QtMultimedia> //play music
#include <QtMultimediaWidgets>
class SimpleMenu : public QMainWindow{

	public:
		SimpleMenu(QWidget *parent = 0);
		std::string getText();
		void commandToString(QString qText);
	private:
		QLabel *text;
		QLineEdit *textBox;
		QMediaPlayer *player;
		QMediaPlaylist *playlist;
		QVideoWidget *videoWidget;
		std::string textCommand;
		commands jarvis;
		std::thread jarvisThread;
		void backEnd();//sends phrase to the backend;
};
