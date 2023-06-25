#include "createpopup.h"
#include "ui_createpopup.h"
#include <QFontDatabase>
#include "../common/game_mode.h"

createPopUp::createPopUp(Lobby* lobby, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createPopUp),
    lobby(lobby),
    player_pick(nullptr)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":AmazMegaGrungeOne.ttf");

    if (id != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty()) {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes

            QFont font(fontFamily, 12); // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            ui->labelName->setFont(font);
            ui->labelPlayers->setFont(font);
            ui->playersNumber->setFont(font);
            ui->createButton->setFont(font);
            ui->gameMode->setFont(font);
            ui->labelMode->setFont(font);
            ui->labelConfirm->setFont(font);
            ui->selectSoldier->setFont(font);
        }
    }
}

createPopUp::~createPopUp()
{
    delete ui;
    if (player_pick != nullptr) delete player_pick;
}

void createPopUp::on_createButton_clicked()
{
    int8_t game_players = ui->playersNumber->currentText().toInt();
    QString game_mode = ui->gameMode->currentText();
    if (game_mode.toStdString() == "Survival")
        lobby->create_scenario(ui->labelName->text().toStdString(), SURVIVAL, game_players);
    else 
        lobby->create_scenario(ui->labelName->text().toStdString(), CLEAR_THE_ZONE, game_players);
    int32_t game_code = lobby->get_create();
    if (game_code != -1){
        QString text = QString("Partida creada. El codigo es: %1").arg(game_code);
        ui->labelConfirm->setText(text);
        lobby->start();
        ui->selectSoldier->setEnabled(true);
        ui->selectSoldier->setStyleSheet("color: rgb(255, 255, 255);");
    }
    else{
        QString text = QString("Error al crear partida");
        ui->labelConfirm->setText(text);
        ui->selectSoldier->setEnabled(false);
    }
}

void createPopUp::on_selectSoldier_clicked() {
    this->close();
    player_pick = new PlayerPick(lobby);
    player_pick->show();
}