#include "joinpopup.h"
#include "ui_joinpopup.h"
#include <QFontDatabase>

JoinPopUp::JoinPopUp(Lobby* lobby, QPushButton* startButton, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinPopUp),
    lobby(lobby),
    player_pick(nullptr),
    startButton(startButton)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":AmazMegaGrungeOne.ttf");

    if (id != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty()) {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes

            QFont font(fontFamily, 12); // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            ui->gameCode->setFont(font);
            ui->joinButton->setFont(font);
            ui->confirmLabel->setFont(font);
            ui->selectSoldier->setFont(font);
        }
    }

    validator = new QIntValidator(this);
    ui->gameCode->setValidator(validator);
}

JoinPopUp::~JoinPopUp()
{
    delete ui;
    delete validator;
    if (player_pick != nullptr) delete player_pick;
}

void JoinPopUp::on_joinButton_clicked()
{
    lobby->join_scenario(ui->gameCode->text().toInt());
    bool could_join = lobby->get_join();
    if (could_join){
        QString text = QString("Te has unido a una partida");
        ui->confirmLabel->setText(text);
        lobby->start();
        ui->selectSoldier->setEnabled(true);
        ui->selectSoldier->setStyleSheet("color: rgb(255, 255, 255);");
        startButton->setEnabled(true);
        startButton->setStyleSheet("QPushButton {"
                            "border: none;"
                            "background: none;"
                            "color: rgb(255, 255, 255);"
                        "}"
                        "QPushButton:hover {"
                            "color: rgb(176, 10, 10);"
                        "}");
    } else{
        QString text = QString("Error al unirse a una partida");
        ui->confirmLabel->setText(text);
        ui->selectSoldier->setEnabled(false);
    }
}

void JoinPopUp::on_selectSoldier_clicked() {
    this->close();
    player_pick = new PlayerPick(lobby);
    player_pick->show();
}

