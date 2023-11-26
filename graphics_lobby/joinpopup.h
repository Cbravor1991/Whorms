#ifndef JOINPOPUP_H
#define JOINPOPUP_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class JoinPopUp;
}

class JoinPopUp : public QDialog
{
    Q_OBJECT

public:
    //explicit JoinPopUp(QWidget *parent = nullptr);
    JoinPopUp(QPushButton* startButton, QWidget *parent = nullptr);
    ~JoinPopUp();

private slots:
    void on_joinButton_clicked();

  
private:
    Ui::JoinPopUp *ui;



    QPushButton* startButton;

    QIntValidator* validator;
    
};

#endif // JOINPOPUP_H
