#include "createpopup.h"
#include "ui_createpopup.h"
#include <QFontDatabase>
#include <iostream>
#include <filesystem>

createPopUp::createPopUp(Lobby *lobby, QWidget *parent) : QDialog(parent),
                                                          ui(new Ui::createPopUp),
                                                          lobby(lobby),
                                                          wait_room(nullptr)
{
    namespace fs = std::filesystem;
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":GROBOLD.ttf");

    if (id != -1)
    {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty())
        {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes
            QFont font(fontFamily, 12);

            std::string directorio = "../mapas";

            for (const auto &entrada : fs::directory_iterator(directorio))
            {
                // Verificar si la extensión es .yaml
                if (entrada.path().extension() == ".yaml")
                {
                    // Obtener el nombre del archivo sin la extensión
                    std::string nombreSinExtension = entrada.path().stem().string();

                    // Agregar el nombre del archivo sin la extensión al vector mapas
                    mapas.push_back(nombreSinExtension);
                }
            }
            for (const auto &dato : mapas)
            {
                ui->scenarios->addItem(QString::fromStdString(dato));
            }

            ui->labelMap->setFont(font);
            ui->scenarios->setFont(font);
            ui->createButton->setFont(font);
            ui->labelConfirm->setFont(font);
            ui->accept->setFont(font);
        }
    }
}

createPopUp::~createPopUp()
{
    delete ui;
}

void createPopUp::on_createButton_clicked()
{

    bool partida_creada = true;

    if (partida_creada)
    {
        std::string nombre_mapa = ui->scenarios->currentText().toStdString();

        int codigo_creado = lobby->enviar_escenario(0, nombre_mapa);

        QString text = QString("El codigo es: %2").arg(codigo_creado);

        ui->labelConfirm->setText(text);
        ui->accept->setEnabled(true);
        ui->accept->setStyleSheet("color: rgb(255, 255, 255);");
    }
    else
    {
        QString text = QString("Error al crear partida");
        ui->labelConfirm->setText(text);
    }
}

void createPopUp::on_accept_clicked()
{
    hide();
    wait_room = new waitRoom(lobby, nullptr);
    wait_room->show();
}

void createPopUp::closeEvent(QCloseEvent *e)
{
    lobby->enviar_desconexion();
    QApplication::exit(1);
}