#ifndef JOINPOPUP_H
#define JOINPOPUP_H

#include <QMainWindow>


#include <QDialog>

namespace Ui {
class JoinPopUp;
}

class JoinPopUp : public QDialog
{
    Q_OBJECT

public:
    //explicit createPopUp(QWidget *parent = nullptr);
    JoinPopUp(QWidget *parent = nullptr);
     std::vector<std::string> mapas;
  
    ~JoinPopUp();

private slots:
    void on_createButton_clicked();


    

private:
    Ui::JoinPopUp *ui;

};

#endif // CREATEPOPUP_H

