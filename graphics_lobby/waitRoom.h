#ifndef WAITROOM_H
#define WAITROOM_H

#pragma once
#include <QMainWindow>
#include "../client_src/client_lobby.h"
#include <QDialog>

namespace Ui {
class waitRoom;
}

class waitRoom : public QDialog
{
    Q_OBJECT

public:
    //explicit createPopUp(QWidget *parent = nullptr);
    waitRoom( Lobby* lobby,QWidget *parent = nullptr);
  
    ~waitRoom();

private slots:
    void on_start_clicked();
 
    

private:
    Ui::waitRoom *ui;
    Lobby* lobby;
};

#endif
