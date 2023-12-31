#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QCloseEvent>
#include <iostream>

MainWindow::MainWindow(Lobby *lobby, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      create_pop_up(nullptr),
      join_pop_up(nullptr),
      loby(lobby)

{
    ui->setupUi(this);
       // Ocultar el botón de cierre (x)
   
    int id = QFontDatabase::addApplicationFont(":GROBOLD.ttf");
    if (id != -1)
    {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty())
        {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes

            QFont font(fontFamily, 24); // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            ui->createButton->setFont(font);
            ui->joinButton->setFont(font);
            ui->exitButton->setFont(font);
        }
    }
    //ui->labelMatch->hide();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(hideTemporaryLabel()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::closeEvent(QCloseEvent *e)
{   loby->enviar_desconexion();
    QApplication::exit(1);

}

void MainWindow::on_createButton_clicked()
{
    hide();
    create_pop_up = new createPopUp(loby, nullptr);
    create_pop_up->show();
}

void MainWindow::on_joinButton_clicked()
{
    hide();
    join_pop_up = new JoinPopUp(loby, nullptr);
    join_pop_up->show();
}



void MainWindow::on_exitButton_clicked()
{    loby->enviar_desconexion();
    QApplication::exit(1);
}


