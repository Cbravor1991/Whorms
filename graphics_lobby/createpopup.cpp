#include "createpopup.h"
#include "ui_createpopup.h"
#include <QFontDatabase>
#include <iostream>

createPopUp::createPopUp(Lobby *lobby, QPushButton *startButton, QWidget *parent) : QDialog(parent),
                                                                                    ui(new Ui::createPopUp),
                                                                                    lobby(lobby),
                                                                                    startButton(startButton),
                                                                                    wait_room(nullptr)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":GROBOLD.ttf");

    if (id != -1)
    {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty())
        {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes
            QFont font(fontFamily, 12);              // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            // ui->labelName->setFont(font);
            ui->labelScenarios->setFont(font);
            ui->scenarios->setFont(font);
            ui->createButton->setFont(font);
            ui->labelConfirm->setFont(font);
            ui->accept->setFont(font);
        }
    }
}

createPopUp::~createPopUp()
{
    delete ui;
}

void createPopUp::on_createButton_clicked()
{
    // int8_t game_players = ui->playersNumber->currentText().toInt();
    // std::string nombre_partida = ui->labelName->text().toStdString();
    /*creamos la partida a traves del lobby
   bool partida_creada = lony->crear_partida(nombrePartida, cantidad_jugadores)
     */
    bool partida_creada = true;

    if (partida_creada)
    {
        /*obtener el codigo de la partida creada asi el otro jugador se puede unir
        int8_t = loby->obtener_codigo_partida_cread;
        */

        int codigo_creado = lobby->enviar_escenario(0);

        QString text = QString("El codigo es: %2").arg(codigo_creado);

        // std::cout << "La cantidad de jugadores es: " << static_cast<int>(game_players) << '\n';
        // std::cout << "La cantidad de jugadores es: " << nombre_partida << '\n';

        // lobby->start_game();

        ui->labelConfirm->setText(text);
        ui->accept->setEnabled(true);
        ui->accept->setStyleSheet("color: rgb(255, 255, 255);");

        startButton->setEnabled(true);
        startButton->setStyleSheet("QPushButton {"
                                   "border: none;"
                                   "background: none;"
                                   "color: rgb(255, 255, 255);"
                                   "}"
                                   "QPushButton:hover {"
                                   "color: rgb(176, 10, 10);"
                                   "}");
        // hide();
    }
    else
    {
        QString text = QString("Error al crear partida");
        ui->labelConfirm->setText(text);
    }
}

void createPopUp::on_accept_clicked()
{
    this->close();
    wait_room = new waitRoom(lobby, nullptr);
    wait_room->show();
}
