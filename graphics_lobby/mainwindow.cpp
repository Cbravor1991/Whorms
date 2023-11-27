#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QCloseEvent>
#include <iostream>



MainWindow::MainWindow(Lobby* lobby, QWidget *parent)
    : QMainWindow(parent), 
     ui(new Ui::MainWindow),
     create_pop_up (nullptr),
     join_pop_up (nullptr), 
      loby(lobby)
    
 
{
    ui->setupUi(this);
    int id = QFontDatabase::addApplicationFont(":AmazMegaGrungeOne.ttf");
    if (id != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty()) {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes

            QFont font(fontFamily, 24); // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            ui->createButton->setFont(font);
            ui->joinButton->setFont(font);
            ui->exitButton->setFont(font);
            ui->startButton->setFont(font);
            ui->labelMatch->setFont(font);
        }
    }
    ui->labelMatch->hide();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(hideTemporaryLabel()));
  
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
 
}

void MainWindow::closeEvent(QCloseEvent *e) {
    QApplication::exit(1);
}

void MainWindow::on_createButton_clicked() {
       
     create_pop_up = new createPopUp(loby, ui->startButton, nullptr);
     create_pop_up->show();  
 

}


void MainWindow::on_joinButton_clicked() {
    hide();
    join_pop_up = new JoinPopUp(loby,nullptr, nullptr);
     join_pop_up->show();  
 
 
}

void MainWindow::on_startButton_clicked() {
    hide();
    // loby->start_game();
    
}

void MainWindow::on_exitButton_clicked() {
    QApplication::exit(1);
}

void MainWindow::hideTemporaryLabel()
{
    ui->labelMatch->hide();
    timer->stop();
}
