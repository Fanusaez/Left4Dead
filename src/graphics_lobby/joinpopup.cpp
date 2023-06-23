#include "joinpopup.h"
#include "ui_joinpopup.h"
#include <QFontDatabase>

JoinPopUp::JoinPopUp(Lobby* lobby, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinPopUp),
    lobby(lobby)
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
        }
    }
}

JoinPopUp::~JoinPopUp()
{
    delete ui;
}

void JoinPopUp::on_joinButton_clicked()
{
    lobby->join_scenario(ui->gameCode->text().toInt());
    lobby->start();
    this->close();
    player_pick = new PlayerPick(lobby);
    player_pick->show();
}

