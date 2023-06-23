#ifndef CREATEPOPUP_H
#define CREATEPOPUP_H

#include "playerpick.h"
#include "../client/lobby.h"
#include <QDialog>

namespace Ui {
class createPopUp;
}

class createPopUp : public QDialog
{
    Q_OBJECT

public:
    //explicit createPopUp(QWidget *parent = nullptr);
    createPopUp(Lobby* lobby, QWidget *parent = nullptr);
    ~createPopUp();

private slots:
    void on_createButton_clicked();

private:
    Ui::createPopUp *ui;

    Lobby* lobby;

    PlayerPick* player_pick;
};

#endif // CREATEPOPUP_H
