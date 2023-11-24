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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *createButton;
    QPushButton *joinButton;
    QPushButton *exitButton;
    QPushButton *startButton;
    QLabel *labelMatch;

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
        createButton->setGeometry(QRect(70, 350, 200, 41));
        createButton->setMaximumSize(QSize(200, 50));
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
        joinButton = new QPushButton(centralwidget);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));
        joinButton->setEnabled(true);
        joinButton->setGeometry(QRect(70, 470, 200, 41));
        joinButton->setMaximumSize(QSize(200, 50));
        joinButton->setFont(font);
        joinButton->setMouseTracking(true);
        joinButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background: none;\n"
"	color : rgb(255,255,255);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	color: rgb(176, 10, 10)\n"
"}"));
        joinButton->setIconSize(QSize(32, 32));
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setEnabled(true);
        exitButton->setGeometry(QRect(70, 590, 200, 41));
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
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setEnabled(false);
        startButton->setGeometry(QRect(450, 650, 361, 61));
        startButton->setMaximumSize(QSize(500, 100));
        QFont font1;
        font1.setPointSize(28);
        startButton->setFont(font1);
        startButton->setMouseTracking(true);
        startButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background: none;\n"
"	color: rgb(157, 157, 157);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	color: rgb(176, 10, 10)\n"
"}"));
        labelMatch = new QLabel(centralwidget);
        labelMatch->setObjectName(QString::fromUtf8("labelMatch"));
        labelMatch->setEnabled(true);
        labelMatch->setGeometry(QRect(450, 360, 600, 50));
        labelMatch->setStyleSheet(QString::fromUtf8("border: none;\n"
"background: none;\n"
"color : rgb(255,255,255);"));
        labelMatch->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        createButton->setText(QCoreApplication::translate("MainWindow", "CREATE GAME", nullptr));
        joinButton->setText(QCoreApplication::translate("MainWindow", "JOIN GAME", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "EXIT", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        labelMatch->setText(QCoreApplication::translate("MainWindow", "YA SE ENCUENTRA EN UNA PARTIDA", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
