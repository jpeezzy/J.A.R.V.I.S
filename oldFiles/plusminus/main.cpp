#include "plusminus.h"
#include <QIcon>
int main(int argc, char *argv[]) {
	    
	  QApplication app(argc, argv);  
	      
	    PlusMinus window;

	window.resize(300, 190);
	window.setWindowTitle("Plus minus");
			window.setWindowIcon(QIcon("test.png"));
			  window.show();

			    return app.exec();
}
