#include "joinpopup.h"
#include "ui_joinpopup.h"
#include <QFontDatabase>
#include <iostream>


JoinPopUp::JoinPopUp(Lobby* lobby,QPushButton* startButton,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinPopUp),
      lobby(lobby),
  
    startButton(startButton)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":AmazMegaGrungeOne.ttf");

    if (id != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty()) {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes

            QFont font(fontFamily, 12); // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            ui->labelName->setFont(font);
            ui->labelConfirm->setFont(font);
            ui->createButton->setFont(font);
            ui->accept->setFont(font);
    

       
        }
    }
}

JoinPopUp::~JoinPopUp()
{
    delete ui;

}

void JoinPopUp::on_createButton_clicked()
{
 
    std::string nombre_partida =  ui->labelName->text().toStdString();
    /*creamos la partida a traves del lobby
   bool partida_creada = lony->crear_partida(nombrePartida, cantidad_jugadores)
     */
    bool partida_creada = true;

  
    if (partida_creada){
        /*obtener el codigo de la partida creada asi el otro jugador se puede unir
        int8_t = loby->obtener_codigo_partida_cread;
        */
         hide();
         QString text = QString("Partida %1 creada. El codigo es: %2").arg(nombre_partida.c_str()).arg(0);
        std::cout<<"EL nombre de la partida es: "<< nombre_partida<<'\n';
        lobby->start_game();
      
        
    }
    else{
        QString text = QString("Error al crear partida");
        ui->labelConfirm->setText(text);
    
    }
}

void JoinPopUp::on_accept_clicked() {
    this->close();

}




