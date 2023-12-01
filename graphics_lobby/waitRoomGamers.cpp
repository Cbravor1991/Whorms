#include "waitRoomGamers.h"
#include "ui_waitRoomGamers.h"
#include <QFontDatabase>
#include <iostream>

waitRoomGamers::waitRoomGamers(Lobby *lobby, QWidget *parent) : QDialog(parent),
                                                                                    ui(new Ui::waitRoomGamers),
                                                                                    lobby(lobby)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":GROBOLD.ttf");

    if (id != -1)
    {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty())
        {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes

            QFont font(fontFamily, 12); // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            //ui->labelName->setFont(font);
         
            ui->labelNumberPlayer->setFont(font);
            ui->labelMessage->setFont(font);
            
        }
    }

          QString text = QString("2/4");
          ui->labelNumberPlayer->setText(text);

          QString text_message = QString("Esperando a que el anfitrion empieze la partida");
          ui->labelMessage->setText(text);  


}

waitRoomGamers::~waitRoomGamers()
{
    delete ui;
}


  void waitRoomGamers::on_createButton_clicked(){}


