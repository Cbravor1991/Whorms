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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_createPopUp
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPlayers;
    QComboBox *playersNumber;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *labelName;
    QPushButton *createButton;
    QLabel *labelConfirm;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *createPopUp)
    {
        if (createPopUp->objectName().isEmpty())
            createPopUp->setObjectName(QString::fromUtf8("createPopUp"));
        createPopUp->resize(450, 180);
        createPopUp->setStyleSheet(QString::fromUtf8("background-image: url(:lobby_background.jpg);"));
        verticalLayout = new QVBoxLayout(createPopUp);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelPlayers = new QLabel(createPopUp);
        labelPlayers->setObjectName(QString::fromUtf8("labelPlayers"));
        labelPlayers->setEnabled(true);
        labelPlayers->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(labelPlayers);

        playersNumber = new QComboBox(createPopUp);
        playersNumber->addItem(QString());
        playersNumber->addItem(QString());
        playersNumber->addItem(QString());
        playersNumber->addItem(QString());
        playersNumber->setObjectName(QString::fromUtf8("playersNumber"));
        playersNumber->setEnabled(true);
        playersNumber->setMaximumSize(QSize(80, 16777215));
        playersNumber->setStyleSheet(QString::fromUtf8("background-image: url(:lobby_background.jpg);"));

        horizontalLayout_2->addWidget(playersNumber);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelName = new QLineEdit(createPopUp);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setEnabled(true);
        labelName->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(labelName);

        createButton = new QPushButton(createPopUp);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        createButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(createButton);


        verticalLayout->addLayout(horizontalLayout);

        labelConfirm = new QLabel(createPopUp);
        labelConfirm->setObjectName(QString::fromUtf8("labelConfirm"));
        labelConfirm->setEnabled(false);
        labelConfirm->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(labelConfirm);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(createPopUp);

        QMetaObject::connectSlotsByName(createPopUp);
    } // setupUi

    void retranslateUi(QDialog *createPopUp)
    {
        createPopUp->setWindowTitle(QCoreApplication::translate("createPopUp", "Crear Juego", nullptr));
        labelPlayers->setText(QCoreApplication::translate("createPopUp", "Seleccione la cantidad de jugadores:", nullptr));
        playersNumber->setItemText(0, QCoreApplication::translate("createPopUp", "1", nullptr));
        playersNumber->setItemText(1, QCoreApplication::translate("createPopUp", "2", nullptr));
        playersNumber->setItemText(2, QCoreApplication::translate("createPopUp", "3", nullptr));
        playersNumber->setItemText(3, QCoreApplication::translate("createPopUp", "4", nullptr));

        labelName->setText(QCoreApplication::translate("createPopUp", "Nombre de partida", nullptr));
        createButton->setText(QCoreApplication::translate("createPopUp", "Crear", nullptr));
        labelConfirm->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class createPopUp: public Ui_createPopUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEPOPUP_H
