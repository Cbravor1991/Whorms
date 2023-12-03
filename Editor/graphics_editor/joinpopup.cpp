#include "joinpopup.h"
#include "ui_joinpopup.h"
#include <QFontDatabase>
#include <iostream>
#include <iostream>
#include <filesystem>

JoinPopUp::JoinPopUp(QWidget *parent) : QDialog(parent),
                                                                                ui(new Ui::JoinPopUp)
                                                                             
{   namespace fs = std::filesystem;
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":GROBOLD.ttf");

    if (id != -1)
    {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty())
        {
            QString fontFamily = fontFamilies.at(0);
            QFont font(fontFamily, 12); 
            std::string directorio = "../mapas"; 

   for (const auto& entrada : fs::directory_iterator(directorio)) {
        // Verificar si la extensión es .yaml
        if (entrada.path().extension() == ".yaml") {
            mapas.push_back(entrada.path().filename().string());
        }
    }
    for (const auto& dato: mapas) {
        ui->games->addItem(QString::fromStdString(dato));
    }
            ui->games->setFont(font);
            ui->labelConfirm->setFont(font);
            ui->createButton->setFont(font);
     
        }
    }
}

JoinPopUp::~JoinPopUp()
{
    delete ui;
}

void JoinPopUp::on_createButton_clicked()
{

  this->close();

}


