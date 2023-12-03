#ifndef CREATEPOPUP_H
#define CREATEPOPUP_H

#include <QMainWindow>
#include "../client_src/client_editor.h"
#include <QDialog>

namespace Ui {
class createPopUp;
}

class createPopUp : public QDialog
{
    Q_OBJECT

public:
    //explicit createPopUp(QWidget *parent = nullptr);
    createPopUp(Editor* editor,QWidget *parent = nullptr);
  
    ~createPopUp();

private slots:
    void on_nightButton_clicked();
    void on_snowButton_clicked();
    void on_snowButton_2_clicked();
    
    

private:
    Ui::createPopUp *ui;
    Editor* editor;
};

#endif // CREATEPOPUP_H
