#include <QApplication>
#include <QTime>
#include <QtGui>
#include "mywindow.hpp"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	/*----Ajout d'un logo----*/
	app.setWindowIcon(QIcon("./Icones/logo.png"));

	MyWindow window;
	window.show();
	
	return app.exec();	
}

