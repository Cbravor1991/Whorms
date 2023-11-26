#include <fstream>
#include <string>
#include <iostream>
#include <exception>
// #include "client.h"
#//include "./game.h"
#include <QApplication>
#include "./client_lobby.h"
#include "../graphics_lobby/mainwindow.h"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Uso: " << argv[0] << " <ip/hostname server> <puerto/servicename>\n";
            return 1;
        }
        const std::string hostname = std::string(argv[1]);
        const std::string servname = std::string(argv[2]);

        /*PARA PROBAR LA APP DE QT DESCOMENTAR ESTAS LINEAS*/
        QApplication app(argc, argv);
        Lobby lobby(hostname, servname);
        MainWindow w(&lobby);
         w.show();
        app.exec();

        /*PARA PROBAR LA APP DE QT COMENTAR ESTAS DOS LINEAS*/
        Game juego(hostname, servname);
        juego.run();

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
