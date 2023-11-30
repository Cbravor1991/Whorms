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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_createPopUp
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPlayers;
    QComboBox *playersNumber;
    QHBoxLayout *horizontalLayout;
    QPushButton *createButton;
    QLabel *labelConfirm;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *ACEPTAR;

    void setupUi(QDialog *createPopUp)
    {
        if (createPopUp->objectName().isEmpty())
            createPopUp->setObjectName(QString::fromUtf8("createPopUp"));
        createPopUp->resize(450, 180);
        createPopUp->setStyleSheet(QString::fromUtf8("background-image: url(:lobby_background.jpg);"));
        verticalLayout = new QVBoxLayout(createPopUp);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
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
        playersNumber->setMaximumSize(QSize(100, 16777215));
        playersNumber->setStyleSheet(QString::fromUtf8("background-image: url(:lobby_background.jpg);"));

        horizontalLayout_2->addWidget(playersNumber);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        createButton = new QPushButton(createPopUp);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        createButton->setMaximumSize(QSize(100, 30));
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
        ACEPTAR = new QPushButton(createPopUp);
        ACEPTAR->setObjectName(QString::fromUtf8("ACEPTAR"));
        ACEPTAR->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ACEPTAR->sizePolicy().hasHeightForWidth());
        ACEPTAR->setSizePolicy(sizePolicy);
        ACEPTAR->setMinimumSize(QSize(0, 0));
        ACEPTAR->setMaximumSize(QSize(200, 30));
        ACEPTAR->setLayoutDirection(Qt::LeftToRight);
        ACEPTAR->setStyleSheet(QString::fromUtf8("color: rgb(157, 157, 157);"));

        horizontalLayout_4->addWidget(ACEPTAR);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(createPopUp);

        QMetaObject::connectSlotsByName(createPopUp);
    } // setupUi

    void retranslateUi(QDialog *createPopUp)
    {
        createPopUp->setWindowTitle(QCoreApplication::translate("createPopUp", "Dialog", nullptr));
        labelPlayers->setText(QCoreApplication::translate("createPopUp", "Seleccione el escenario:", nullptr));
        playersNumber->setItemText(0, QCoreApplication::translate("createPopUp", "Alta mar", nullptr));
        playersNumber->setItemText(1, QCoreApplication::translate("createPopUp", "Monta\303\261as", nullptr));
        playersNumber->setItemText(2, QString());
        playersNumber->setItemText(3, QString());

        createButton->setText(QCoreApplication::translate("createPopUp", "CREAR", nullptr));
        labelConfirm->setText(QString());
        ACEPTAR->setText(QCoreApplication::translate("createPopUp", "ACEPTAR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class createPopUp: public Ui_createPopUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEPOPUP_H
