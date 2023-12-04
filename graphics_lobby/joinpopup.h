#ifndef JOINPOPUP_H
#define JOINPOPUP_H

#include <QMainWindow>

#include "../client_src/client_lobby.h"
#include <QDialog>

namespace Ui {
class JoinPopUp;
}

class JoinPopUp : public QDialog
{
    Q_OBJECT

public:
    //explicit createPopUp(QWidget *parent = nullptr);
    JoinPopUp(Lobby* lobby, QWidget *parent = nullptr);
  
    ~JoinPopUp();

private slots:
    void on_joinButton_clicked();
    void on_accept_clicked();

    

private:
    Ui::JoinPopUp *ui;
    Lobby* lobby;
    QPushButton* startButton;
};

#endif // CREATEPOPUP_H

