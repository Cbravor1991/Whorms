#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include "createpopup.h"
#include <QMainWindow>
#include <QTimer>
#include "joinpopup.h"
#include "../client_src/client_editor.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Editor* editor, QWidget *parent = nullptr);
    //MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_createButton_clicked();

    void on_editButton_clicked();



    void on_exitButton_clicked();

     void hideTemporaryLabel();

protected:
     void closeEvent(QCloseEvent *event);
     
private:
    Ui::MainWindow *ui;
    createPopUp* create_pop_up;
    JoinPopUp * join_pop_up;
    QTimer *timer;
    Editor* editor;
  
};
#endif // MAINWINDOW_H
