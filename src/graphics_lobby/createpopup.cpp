#include "createpopup.h"
#include "ui_createpopup.h"
#include <QFontDatabase>
#include "../common/game_mode.h"

createPopUp::createPopUp(Lobby* lobby, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createPopUp),
    lobby(lobby)
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
        }
    }
}

createPopUp::~createPopUp()
{
    delete ui;
}

void createPopUp::on_createButton_clicked()
{
    int8_t game_players = ui->playersNumber->currentText().toInt();
    QString game_mode = ui->gameMode->currentText();
    if (game_mode.toStdString() == "Survival")
        lobby->create_scenario(ui->labelName->text().toStdString(), SURVIVAL, game_players);
    else 
        lobby->create_scenario(ui->labelName->text().toStdString(), CLEAR_THE_ZONE, game_players);
    lobby->start();
    this->close();
    player_pick = new PlayerPick(lobby);
    player_pick->show();
}

