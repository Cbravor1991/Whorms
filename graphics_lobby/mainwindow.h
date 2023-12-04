#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include "createpopup.h"
#include <QMainWindow>
#include <QTimer>
#include "../client_src/client_lobby.h"
#include "joinpopup.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Lobby* lobby, QWidget *parent = nullptr);
    //MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_createButton_clicked();

    void on_joinButton_clicked();

    void on_exitButton_clicked();

    

protected:
     void closeEvent(QCloseEvent *event);
     
private:
    Ui::MainWindow *ui;
    createPopUp* create_pop_up;
    JoinPopUp * join_pop_up;
    QTimer *timer;
    Lobby* loby;
};
#endif // MAINWINDOW_H
