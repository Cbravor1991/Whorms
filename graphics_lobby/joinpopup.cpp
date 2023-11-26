#include "joinpopup.h"
#include "ui_joinpopup.h"
#include <QFontDatabase>

JoinPopUp::JoinPopUp(QPushButton* startButton, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinPopUp),
    startButton(startButton)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":AmazMegaGrungeOne.ttf");

    if (id != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty()) {
            QString fontFamily = fontFamilies.at(0);

            QFont font(fontFamily, 12); 
            ui->gameCode->setFont(font);
            ui->joinButton->setFont(font);
            ui->confirmLabel->setFont(font);
    
        }
    }

    validator = new QIntValidator(this);
    ui->gameCode->setValidator(validator);
}

JoinPopUp::~JoinPopUp()
{
    delete ui;
    delete validator;

}

void JoinPopUp::on_joinButton_clicked()
{
    bool could_join = true;
    if (could_join){
        QString text = QString("Te has unido a una partida");
        ui->confirmLabel->setText(text);
        startButton->setEnabled(true);
        startButton->setStyleSheet("QPushButton {"
                            "border: none;"
                            "background: none;"
                            "color: rgb(255, 255, 255);"
                        "}"
                        "QPushButton:hover {"
                            "color: rgb(176, 10, 10);"
                        "}");
    } else{
        QString text = QString("Error al unirse a una partida");
        ui->confirmLabel->setText(text);

    }
}


