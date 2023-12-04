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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_JoinPopUp
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *games;
    QPushButton *joinButton;
    QLabel *labelConfirm;

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
        games = new QComboBox(JoinPopUp);
        games->setObjectName(QString::fromUtf8("games"));

        horizontalLayout->addWidget(games);

        joinButton = new QPushButton(JoinPopUp);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));
        joinButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(joinButton);


        verticalLayout->addLayout(horizontalLayout);

        labelConfirm = new QLabel(JoinPopUp);
        labelConfirm->setObjectName(QString::fromUtf8("labelConfirm"));
        labelConfirm->setEnabled(false);
        labelConfirm->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(labelConfirm);


        retranslateUi(JoinPopUp);

        QMetaObject::connectSlotsByName(JoinPopUp);
    } // setupUi

    void retranslateUi(QDialog *JoinPopUp)
    {
        JoinPopUp->setWindowTitle(QCoreApplication::translate("JoinPopUp", "Dialog", nullptr));
        joinButton->setText(QCoreApplication::translate("JoinPopUp", "UNIRSE", nullptr));
        labelConfirm->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class JoinPopUp: public Ui_JoinPopUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINPOPUP_H
