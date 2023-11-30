/********************************************************************************
** Form generated from reading UI file 'waitRoom.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITROOM_H
#define UI_WAITROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_waitRoom
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelConfirm;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *start;

    void setupUi(QDialog *waitRoom)
    {
        if (waitRoom->objectName().isEmpty())
            waitRoom->setObjectName(QString::fromUtf8("waitRoom"));
        waitRoom->resize(450, 180);
        waitRoom->setStyleSheet(QString::fromUtf8("background-image: url(:lobby_background.jpg);"));
        verticalLayout = new QVBoxLayout(waitRoom);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelConfirm = new QLabel(waitRoom);
        labelConfirm->setObjectName(QString::fromUtf8("labelConfirm"));
        labelConfirm->setEnabled(false);
        labelConfirm->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(labelConfirm);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        start = new QPushButton(waitRoom);
        start->setObjectName(QString::fromUtf8("start"));
        start->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(start->sizePolicy().hasHeightForWidth());
        start->setSizePolicy(sizePolicy);
        start->setMinimumSize(QSize(0, 0));
        start->setMaximumSize(QSize(200, 30));
        start->setLayoutDirection(Qt::LeftToRight);
        start->setStyleSheet(QString::fromUtf8("color: rgb(157, 157, 157);"));

        horizontalLayout_4->addWidget(start);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(waitRoom);

        QMetaObject::connectSlotsByName(waitRoom);
    } // setupUi

    void retranslateUi(QDialog *waitRoom)
    {
        waitRoom->setWindowTitle(QCoreApplication::translate("waitRoom", "Dialog", nullptr));
        labelConfirm->setText(QString());
        start->setText(QCoreApplication::translate("waitRoom", "START GAME", nullptr));
    } // retranslateUi

};

namespace Ui {
    class waitRoom: public Ui_waitRoom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITROOM_H
