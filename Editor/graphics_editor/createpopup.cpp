#include "createpopup.h"
#include "ui_createpopup.h"
#include <QFontDatabase>
#include <iostream>

createPopUp::createPopUp(Editor* editor,QWidget *parent) : QDialog(parent),
                                                                                    ui(new Ui::createPopUp),
                                                                                    editor(editor)
                                                                                 

{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":GROBOLD.ttf");

    if (id != -1)
    {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty())
        {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes

            QFont font(fontFamily, 12); // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            ui->label->setFont(font);
            ui->label_3->setParent(ui->groupBox);
            ui->label_2->setParent(ui->groupBox);
            ui->label_4->setParent(ui->groupBox);
            ui->label_5->setFont(font);
            ui->labelName->setFont(font);
            ui->nightButton->setFont(font);
            ui->snowButton->setFont(font);
            ui->snowButton_2->setFont(font);
           
        }
    }
}

createPopUp::~createPopUp()
{
    delete ui;
}

void createPopUp::on_nightButton_clicked()
{
    hide();
    
    editor->crear_mapa("noche", ui->labelName->text().toStdString());


    
}

void createPopUp::on_snowButton_clicked()
{
    hide();
    editor->crear_mapa("snow", ui->labelName->text().toStdString());
}

void createPopUp::on_snowButton_2_clicked()
{
    hide();
    editor->crear_mapa("dia", ui->labelName->text().toStdString());
}