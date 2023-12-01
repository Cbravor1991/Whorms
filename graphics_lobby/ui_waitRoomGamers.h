/********************************************************************************
** Form generated from reading UI file 'waitRoomGamers.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITROOMGAMERS_H
#define UI_WAITROOMGAMERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_waitRoomGamers
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelNumberPlayer;
    QLabel *labelMessage;

    void setupUi(QDialog *waitRoomGamers)
    {
        if (waitRoomGamers->objectName().isEmpty())
            waitRoomGamers->setObjectName(QString::fromUtf8("waitRoomGamers"));
        waitRoomGamers->resize(450, 180);
        waitRoomGamers->setStyleSheet(QString::fromUtf8("background-image: url(:lobby_background.jpg);"));
        verticalLayout = new QVBoxLayout(waitRoomGamers);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelNumberPlayer = new QLabel(waitRoomGamers);
        labelNumberPlayer->setObjectName(QString::fromUtf8("labelNumberPlayer"));
        labelNumberPlayer->setEnabled(false);
        labelNumberPlayer->setMaximumSize(QSize(16777215, 80));
        labelNumberPlayer->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(labelNumberPlayer);

        labelMessage = new QLabel(waitRoomGamers);
        labelMessage->setObjectName(QString::fromUtf8("labelMessage"));
        labelMessage->setEnabled(false);

        verticalLayout->addWidget(labelMessage);


        retranslateUi(waitRoomGamers);

        QMetaObject::connectSlotsByName(waitRoomGamers);
    } // setupUi

    void retranslateUi(QDialog *waitRoomGamers)
    {
        waitRoomGamers->setWindowTitle(QCoreApplication::translate("waitRoomGamers", "Dialog", nullptr));
        labelNumberPlayer->setText(QString());
        labelMessage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class waitRoomGamers: public Ui_waitRoomGamers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITROOMGAMERS_H
