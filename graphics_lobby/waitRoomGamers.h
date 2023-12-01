#ifndef WAITROOMGAMERS_H
#define WAITROOMGAMERS_H

#pragma once
#include <QMainWindow>
#include "../client_src/client_lobby.h"
#include <QDialog>

namespace Ui {
class waitRoomGamers;
}

class waitRoomGamers : public QDialog
{
    Q_OBJECT

public:
    //explicit createPopUp(QWidget *parent = nullptr);
    waitRoomGamers( Lobby* lobby,QWidget *parent = nullptr);
  
    ~waitRoomGamers();

private slots:
    void on_createButton_clicked();
  
    

private:
    Ui::waitRoomGamers*ui;
    Lobby* lobby;
};

#endif
