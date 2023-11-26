#include "createpopup.h"
#include "ui_createpopup.h"
#include <QFontDatabase>
#include <iostream>


createPopUp::createPopUp(Lobby* lobby, QPushButton* startButton,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createPopUp),
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
            ui->labelPlayers->setFont(font);
            ui->playersNumber->setFont(font);
            ui->createButton->setFont(font);
       
      
            ui->labelConfirm->setFont(font);
       
        }
    }
}

createPopUp::~createPopUp()
{
    delete ui;

}

void createPopUp::on_createButton_clicked()
{
    int8_t game_players = ui->playersNumber->currentText().toInt();

  
    if (1==1){
        QString text = QString("Partida creada. El codigo es: 0");
        ui->labelConfirm->setText(text);
        std::cout<<"La cantidad de jugadores es: "<< game_players<<'\n';
        hide();
         lobby->start_game();
        
    }
    else{
        QString text = QString("Error al crear partida");
        ui->labelConfirm->setText(text);
    
    }
}

