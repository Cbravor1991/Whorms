/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *createButton;
    QPushButton *editButton;
    QPushButton *exitButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1280, 720);
        MainWindow->setStyleSheet(QString::fromUtf8("background-image: url(:lobby_background.jpg);"));
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        createButton = new QPushButton(centralwidget);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        createButton->setEnabled(true);
        createButton->setGeometry(QRect(80, 590, 250, 41));
        createButton->setMaximumSize(QSize(250, 50));
        QFont font;
        font.setPointSize(14);
        createButton->setFont(font);
        createButton->setMouseTracking(true);
        createButton->setLayoutDirection(Qt::LeftToRight);
        createButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background: none;\n"
"	color : rgb(255,255,255);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	color: rgb(176, 10, 10)\n"
"}"));
        createButton->setIconSize(QSize(32, 32));
        editButton = new QPushButton(centralwidget);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        editButton->setEnabled(true);
        editButton->setGeometry(QRect(500, 590, 250, 41));
        editButton->setMaximumSize(QSize(250, 50));
        editButton->setFont(font);
        editButton->setMouseTracking(true);
        editButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background: none;\n"
"	color : rgb(255,255,255);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	color: rgb(176, 10, 10)\n"
"}"));
        editButton->setIconSize(QSize(32, 32));
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setEnabled(true);
        exitButton->setGeometry(QRect(960, 590, 200, 41));
        exitButton->setMaximumSize(QSize(200, 50));
        exitButton->setFont(font);
        exitButton->setMouseTracking(true);
        exitButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background: none;\n"
"	color : rgb(255,255,255);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	color: rgb(176, 10, 10)\n"
"}"));
        exitButton->setIconSize(QSize(32, 32));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        createButton->setText(QCoreApplication::translate("MainWindow", "CREAR MAPA", nullptr));
        editButton->setText(QCoreApplication::translate("MainWindow", "EDITAR MAPA", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "SALIR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
