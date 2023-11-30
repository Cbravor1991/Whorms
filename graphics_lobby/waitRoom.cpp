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
            //ui->labelName->setFont(font);
         
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

void waitRoom::on_createButton_clicked()
{

 
    bool partida_creada = true;

    if (partida_creada)
    {
        /*obtener el codigo de la partida creada asi el otro jugador se puede unir
        int8_t = loby->obtener_codigo_partida_cread;
        */
  
        lobby->enviar_escenario(0);
  
        ui->start->setEnabled(true);
        ui->start->setStyleSheet("color: rgb(255, 255, 255);");

      
    }
    else
    {
        QString text = QString("Error al crear partida");
        ui->labelConfirm->setText(text);
    }
}

void waitRoom::on_accept_clicked()
{
    this->close();
}
