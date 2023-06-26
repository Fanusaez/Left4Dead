#include "playerpick.h"
#include "ui_playerpick.h"
#include <QFontDatabase>
#include "../common/soldier_type.h"

PlayerPick::PlayerPick(Lobby* lobby, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerPick),
    lobby(lobby)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":AmazMegaGrungeOne.ttf");

    if (id != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty()) {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes

            QFont font(fontFamily, 12); // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            ui->idfButton->setFont(font);
            ui->p90Button->setFont(font);
            ui->scouttButton->setFont(font);
            ui->soldierLebel->setFont(font);
            ui->pushButton->setFont(font);
        }
    }
    ui->pushButton->setEnabled(false);
    ui->pushButton->setStyleSheet("color: rgb(157, 157, 157);");

}

PlayerPick::~PlayerPick()
{
    delete ui;
}

void PlayerPick::on_idfButton_clicked()
{
    QString name = "IDF";
    QString text = QString("SELECCIONE UN SOLDADO PARA JUGAR: %1").arg(name);
    ui->soldierLebel->setText(text);
    ui->pushButton->setEnabled(true);
    ui->pushButton->setStyleSheet("color: rgb(255, 255, 255);");
}


void PlayerPick::on_scouttButton_clicked()
{
    QString name = "SCOUT";
    QString text = QString("SELECCIONE UN SOLDADO PARA JUGAR: %1").arg(name);
    ui->soldierLebel->setText(text);
    ui->pushButton->setEnabled(true);
    ui->pushButton->setStyleSheet("color: rgb(255, 255, 255);");
}


void PlayerPick::on_p90Button_clicked()
{
    QString name = "P90";
    QString text = QString("SELECCIONE UN SOLDADO PARA JUGAR: %1").arg(name);
    ui->soldierLebel->setText(text);
    ui->pushButton->setEnabled(true);
    ui->pushButton->setStyleSheet("color: rgb(255, 255, 255);");
}


void PlayerPick::on_pushButton_clicked()
{
    QString weapon = ui->soldierLebel->text();
    if (weapon.toStdString() == "SELECCIONE UN SOLDADO PARA JUGAR: IDF")
        lobby->soldier_type(IDF);
    if (weapon.toStdString() == "SELECCIONE UN SOLDADO PARA JUGAR: SCOUT")
        lobby->soldier_type(SCOUT);
    if (weapon.toStdString() == "SELECCIONE UN SOLDADO PARA JUGAR: P90")
        lobby->soldier_type(P90);

    this->close();
}

void PlayerPick::closeEvent(QCloseEvent *e) {
    if (!ui->pushButton->isEnabled())
        lobby->soldier_type(IDF);
    else{
        QString weapon = ui->soldierLebel->text();
        if (weapon.toStdString() == "SELECCIONE UN SOLDADO PARA JUGAR: IDF")
            lobby->soldier_type(IDF);
        if (weapon.toStdString() == "SELECCIONE UN SOLDADO PARA JUGAR: SCOUT")
            lobby->soldier_type(SCOUT);
        if (weapon.toStdString() == "SELECCIONE UN SOLDADO PARA JUGAR: P90")
            lobby->soldier_type(P90);
    }
}
