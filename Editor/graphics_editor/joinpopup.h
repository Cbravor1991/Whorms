#ifndef JOINPOPUP_H
#define JOINPOPUP_H

#include <QMainWindow>
#include "../client_src/client_editor.h"
#include <QDialog>

namespace Ui {
class JoinPopUp;
}

class JoinPopUp : public QDialog
{
    Q_OBJECT

public:
    //explicit createPopUp(QWidget *parent = nullptr);
    JoinPopUp(Editor* editor, QWidget *parent = nullptr);
     std::vector<std::string> mapas;
  
    ~JoinPopUp();

private slots:
    void on_createButton_clicked();


    

private:
    Ui::JoinPopUp *ui;
    Editor* editor;
};

#endif // CREATEPOPUP_H

