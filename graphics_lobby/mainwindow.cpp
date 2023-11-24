#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QCloseEvent>
#include <iostream>


/* MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
} */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
 
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
    if(ui->startButton->isEnabled()){
        ui->labelMatch->show();
        timer->start(2000);
    } else {
      std::cout <<"Presionaste boton de crear partida"<<'\n';
    }
}


void MainWindow::on_joinButton_clicked() {
    if(ui->startButton->isEnabled()){
        ui->labelMatch->show();
        timer->start(2000);
    } else {
       std::cout <<"Presionaste boton de join"<<'\n';
    }   
}

void MainWindow::on_startButton_clicked() {
    QApplication::exit();
    std::cout <<"Presionaste boton de salida"<<'\n';
}

void MainWindow::on_exitButton_clicked() {
    QApplication::exit(1);
}

void MainWindow::hideTemporaryLabel()
{
    ui->labelMatch->hide();
    timer->stop();
}
