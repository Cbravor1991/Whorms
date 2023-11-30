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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_JoinPopUp
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *labelName;
    QPushButton *createButton;
    QLabel *labelConfirm;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *accept;

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
        labelName = new QLineEdit(JoinPopUp);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setEnabled(true);
        labelName->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(labelName);

        createButton = new QPushButton(JoinPopUp);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        createButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(createButton);


        verticalLayout->addLayout(horizontalLayout);

        labelConfirm = new QLabel(JoinPopUp);
        labelConfirm->setObjectName(QString::fromUtf8("labelConfirm"));
        labelConfirm->setEnabled(false);
        labelConfirm->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(labelConfirm);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        accept = new QPushButton(JoinPopUp);
        accept->setObjectName(QString::fromUtf8("accept"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(accept->sizePolicy().hasHeightForWidth());
        accept->setSizePolicy(sizePolicy);
        accept->setMinimumSize(QSize(0, 0));
        accept->setMaximumSize(QSize(200, 30));
        accept->setLayoutDirection(Qt::LeftToRight);
        accept->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(accept);


        verticalLayout->addLayout(horizontalLayout_4);



        retranslateUi(JoinPopUp);

        QMetaObject::connectSlotsByName(JoinPopUp);
    } // setupUi

    void retranslateUi(QDialog *JoinPopUp)
    {
        JoinPopUp->setWindowTitle(QCoreApplication::translate("JoinPopUp", "Dialog", nullptr));
        labelName->setText(QCoreApplication::translate("JoinPopUp", "INGRESE NUMERO DE PARTIDA", nullptr));
        createButton->setText(QCoreApplication::translate("JoinPopUp", "UNIRSE", nullptr));
        labelConfirm->setText(QString());
          accept->setText(QCoreApplication::translate("JoinPopUp", "SALIR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JoinPopUp: public Ui_JoinPopUp{};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINPOPUP_H
