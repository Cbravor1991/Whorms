#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include <QApplication>
#include "./client_editor.h"
#include "../graphics_editor/mainwindow.h"

int main(int argc, char *argv[])
{
    try
    {
         QApplication app(argc, argv);
         Editor editor;
         MainWindow w (&editor);
         w.show();
        app.exec();

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
