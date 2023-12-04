#include "waitRoom.h"
#include "ui_waitRoom.h"
#include <QFontDatabase>
#include <iostream>

waitRoom::waitRoom(Lobby *lobby, QWidget *parent) : QDialog(parent),
                                                                                    ui(new Ui::waitRoom),
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
            ui->labelConfirm->setFont(font);
            ui->start->setFont(font);
       
        }
    }

          QString text = QString("ESPERANDO INICIO DE PARTIDA....");
          ui->labelConfirm->setText(text);


}

waitRoom::~waitRoom()
{
    delete ui;
}

void waitRoom::on_start_clicked()
{
    this->close();
    lobby->enviar_comienzo_juego();
    lobby->jugar();
}



