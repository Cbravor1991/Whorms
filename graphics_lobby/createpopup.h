#ifndef CREATEPOPUP_H
#define CREATEPOPUP_H

#include <QMainWindow>

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
    createPopUp( Lobby* lobby, QPushButton* startButton, QWidget *parent = nullptr);
  
    ~createPopUp();

private slots:
    void on_createButton_clicked();
    void on_accept_clicked();
    

private:
    Ui::createPopUp *ui;
    Lobby* lobby;
    QPushButton* startButton;
};

#endif // CREATEPOPUP_H
