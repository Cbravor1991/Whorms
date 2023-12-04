#ifndef CREATEPOPUP_H
#define CREATEPOPUP_H

#include <QMainWindow>
#include "waitRoom.h"
#include "../client_src/client_lobby.h"
#include <QDialog>

namespace Ui {
class createPopUp;
}

class createPopUp : public QDialog
{
    Q_OBJECT

public:
    //explicit createPopUp(QWidget *parent = nullptr);
    createPopUp( Lobby* lobby, QWidget *parent = nullptr);
  
    ~createPopUp();

private slots:
    void on_createButton_clicked();
    void on_accept_clicked();
    

private:
    Ui::createPopUp *ui;
    Lobby* lobby;
    waitRoom* wait_room;
    std::vector<std::string> mapas;
};

#endif // CREATEPOPUP_H
