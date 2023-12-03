/********************************************************************************
** Form generated from reading UI file 'createpopup.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEPOPUP_H
#define UI_CREATEPOPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_createPopUp
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QLabel *label;
    QLineEdit *labelName;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QLabel *label_2;
    QPushButton *nightButton;
    QPushButton *snowButton;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *snowButton_2;

    void setupUi(QDialog *createPopUp)
    {
        if (createPopUp->objectName().isEmpty())
            createPopUp->setObjectName(QString::fromUtf8("createPopUp"));
        createPopUp->resize(1000, 250);
        createPopUp->setStyleSheet(QString::fromUtf8("background-image: url(:negro_fondo.jpg);"));
        verticalLayout = new QVBoxLayout(createPopUp);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(createPopUp);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(7770, 50));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(290, 30, 400, 21));
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        labelName = new QLineEdit(groupBox_2);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setEnabled(true);
        labelName->setGeometry(QRect(350, 0, 344, 25));
        labelName->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, 0, 341, 21));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(groupBox_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(createPopUp);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 20, 291, 211));
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(:noche.jpg);"));
        nightButton = new QPushButton(groupBox);
        nightButton->setObjectName(QString::fromUtf8("nightButton"));
        nightButton->setGeometry(QRect(90, 0, 89, 25));
        snowButton = new QPushButton(groupBox);
        snowButton->setObjectName(QString::fromUtf8("snowButton"));
        snowButton->setGeometry(QRect(440, 0, 89, 25));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(330, 20, 291, 211));
        label_3->setStyleSheet(QString::fromUtf8("background-image: url(:snow.jpg);"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(680, 30, 291, 211));
        label_4->setStyleSheet(QString::fromUtf8("background-image: url(:dia.jpg);"));
        snowButton_2 = new QPushButton(groupBox);
        snowButton_2->setObjectName(QString::fromUtf8("snowButton_2"));
        snowButton_2->setGeometry(QRect(790, 0, 89, 25));
        snowButton_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        snowButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        nightButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));


        horizontalLayout->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(createPopUp);

        QMetaObject::connectSlotsByName(createPopUp);
    } // setupUi

    void retranslateUi(QDialog *createPopUp)
    {
        createPopUp->setWindowTitle(QCoreApplication::translate("createPopUp", "Dialog", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("createPopUp", "GroupBox", nullptr));
        label->setText(QCoreApplication::translate("createPopUp", "SELECCIONAR FONDO PARA COMENZAR EDICI\303\223N", nullptr));
        labelName->setText(QCoreApplication::translate("createPopUp", "Nombre del mapa", nullptr));
        label_5->setText(QCoreApplication::translate("createPopUp", "INGRESAR NOMBRE MAPA", nullptr));
        groupBox->setTitle(QCoreApplication::translate("createPopUp", "GroupBox", nullptr));
        label_2->setText(QString());
        nightButton->setText(QCoreApplication::translate("createPopUp", "NOCHE", nullptr));
        snowButton->setText(QCoreApplication::translate("createPopUp", "NIEVE", nullptr));
        label_3->setText(QString());
        label_4->setText(QString());
        snowButton_2->setText(QCoreApplication::translate("createPopUp", "DIA", nullptr));
    } // retranslateUi

};

namespace Ui {
    class createPopUp: public Ui_createPopUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEPOPUP_H
