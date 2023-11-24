
#include "mainwindow.h"

#include <QApplication>

//#include "../client/lobby.h"

int main(int argc, char *argv[])
{
	//Lobby lobby(argv[1], argv[2]);
	QApplication app(argc, argv);
	MainWindow w;
    w.show();
	app.exec();
    return 0;
}