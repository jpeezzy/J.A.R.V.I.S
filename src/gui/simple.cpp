#include <QApplication>
#include <QWidget> 
#include <QIcon> 
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QWidget window;

	window.resize(250,150);
	window.setWindowTitle("Simple example");
	window.setToolTip("this is a tool tip"); //a tooltip is a hint about an item in app
	window.setWindowIcon(QIcon("test.png"));
	window.show();
	return app.exec();
}
