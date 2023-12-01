#include "joinpopup.h"
#include "ui_joinpopup.h"
#include <QFontDatabase>
#include <iostream>

JoinPopUp::JoinPopUp(Lobby *lobby, QPushButton *startButton, QWidget *parent) : QDialog(parent),
                                                                                ui(new Ui::JoinPopUp),
                                                                                lobby(lobby),

                                                                                startButton(startButton)
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
            ui->labelName->hide();
            ui->labelConfirm->setFont(font);
            ui->createButton->setFont(font);
            ui->games->setFont(font);
            std::vector<std::string> cargas;
            cargas.push_back("1");
            cargas.push_back("2");
            cargas.push_back("3");
            for (const auto& dato : cargas) {
                  ui->games->addItem(QString::fromStdString(dato));
    }
 


     
        }
    }
}

JoinPopUp::~JoinPopUp()
{
    delete ui;
}

void JoinPopUp::on_createButton_clicked()
{

    //std::string nombre_partida = ui->labelName->text().toStdString();
    int game = ui->games->currentText().toInt();
    std::cout <<"el juego es:" <<game<<'\n';
    /*creamos la partida a traves del lobby
   bool partida_creada = lony->crear_partida(nombrePartida, cantidad_jugadores)
     */
    bool partida_creada = true;

    if (partida_creada)
    { hide();


       // QString text = QString("Partida %1 creada. El codigo es: %2").arg(nombre_partida.c_str()).arg(0);

        lobby->enviar_partida(game);
        int cantidad;
         
        while (!lobby->en_juego)
        {    
            if (lobby->modo_partida())
            {   hide();
                lobby->jugar();
                 std::cout << "La cantidad de jugadores es: " << cantidad << '\n';
            }
            else
            {   
                cantidad = lobby->cantidad_jugadores();
                std::cout << "La cantidad de jugadores es: " << cantidad << '\n';
            }
        }
       // std::cout << "EL nombre de la partida es: " << nombre_partida << '\n';
    }
    else
    {
        QString text = QString("Error al crear partida");
        ui->labelConfirm->setText(text);
    }
}

void JoinPopUp::on_accept_clicked()
{
    this->close();
}
