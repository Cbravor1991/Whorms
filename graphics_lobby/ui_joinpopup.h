/********************************************************************************
** Form generated from reading UI file 'joinpopup.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINPOPUP_H
#define UI_JOINPOPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_JoinPopUp
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *gameCode;
    QPushButton *joinButton;
    QLabel *confirmLabel;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;


    void setupUi(QDialog *JoinPopUp)
    {
        if (JoinPopUp->objectName().isEmpty())
            JoinPopUp->setObjectName(QString::fromUtf8("JoinPopUp"));
        JoinPopUp->resize(450, 180);
        JoinPopUp->setStyleSheet(QString::fromUtf8("background-image: url(:lobby_background.jpg);"));
        verticalLayout = new QVBoxLayout(JoinPopUp);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gameCode = new QLineEdit(JoinPopUp);
        gameCode->setObjectName(QString::fromUtf8("gameCode"));
        gameCode->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(gameCode);

        joinButton = new QPushButton(JoinPopUp);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));
        joinButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(joinButton);


        verticalLayout->addLayout(horizontalLayout);

        confirmLabel = new QLabel(JoinPopUp);
        confirmLabel->setObjectName(QString::fromUtf8("confirmLabel"));
        confirmLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(confirmLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

      



        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(JoinPopUp);

        QMetaObject::connectSlotsByName(JoinPopUp);
    } // setupUi

    void retranslateUi(QDialog *JoinPopUp)
    {
        JoinPopUp->setWindowTitle(QCoreApplication::translate("JoinPopUp", "Dialog", nullptr));
        gameCode->setText(QCoreApplication::translate("JoinPopUp", "XXXXXX", nullptr));
        joinButton->setText(QCoreApplication::translate("JoinPopUp", "Unirse", nullptr));
        confirmLabel->setText(QString());
      
    } // retranslateUi

};

namespace Ui {
    class JoinPopUp: public Ui_JoinPopUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINPOPUP_H
