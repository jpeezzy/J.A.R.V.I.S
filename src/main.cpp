#include "simplemenu.h"
#include "commands.h"
#include <QFile>

int main(int argc, char* argv[])
{
	QApplication app(argc,argv);
	//commands test;
	SimpleMenu window;
//	window.resize(1000,1000);

	window.setWindowTitle("jarvis?");
	window.setWindowIcon(QIcon("gui/test.png"));
	window.setToolTip("Testing toooltip");
	window.showFullScreen(); //launches application full screen 
	//window.show();
	//std::thread t1(&commands::intro, commands());
	return app.exec();
}


