#include <QApplication>
#include <QWidget> 
#include <QIcon>
#include <QPushButton>

class MyButton : public QWidget{
	public:
		MyButton(QWidget *parent = 0);
};

//class that creates push button
MyButton::MyButton(QWidget *parent)
	: QWidget(parent) {
	
	QPushButton *quitBtn = new QPushButton("Quit", this);
	quitBtn->setGeometry(50,40,75,30);

	MyButton::connect(quitBtn, &QPushButton::clicked, qApp, &QApplication::quit);
}


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	MyButton window;
	window.resize(250,150);
	window.setWindowTitle("QPushButton");
	//window.setToolTip("this is a tool tip"); //a tooltip is a hint about an item in app
	//window.setWindowIcon(QIcon("test.png"));
	window.show();
	return app.exec();
}
