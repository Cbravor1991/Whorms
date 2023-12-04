#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QCloseEvent>
#include <iostream>

MainWindow::MainWindow(Editor* editor, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      create_pop_up(nullptr),
      join_pop_up(nullptr),
      editor(editor)

{
    ui->setupUi(this);
    int id = QFontDatabase::addApplicationFont(":GROBOLD.ttf");
    if (id != -1)
    {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty())
        {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes

            QFont font(fontFamily, 24); // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            ui->createButton->setFont(font);
            ui->editButton ->setFont(font);
            ui->exitButton->setFont(font);
          
        }
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(hideTemporaryLabel()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    QApplication::exit(1);
}

void MainWindow::on_createButton_clicked()
{
    hide();
    create_pop_up = new createPopUp(editor, nullptr);
    create_pop_up->show();
}

void MainWindow::on_editButton_clicked()
{
    hide();
    join_pop_up = new JoinPopUp(editor, nullptr);
    join_pop_up->show();
}


void MainWindow::on_exitButton_clicked()
{
    QApplication::exit(1);
}

