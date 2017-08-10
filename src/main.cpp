#include "gui/simplemenu.h"
#include "commands.h"
#include <QFile>

int main(int argc, char* argv[])
{
	QApplication app(argc,argv);

	commands test;
	test.intro();
	SimpleMenu window;
	//window.resize(1000,1000);

	window.setWindowTitle("jarvis?");
	window.setWindowIcon(QIcon("test.png"));
	window.setToolTip("Testing toooltip");
	window.showFullScreen(); //launches application full screen 
	//window.show();
	return app.exec();
}


