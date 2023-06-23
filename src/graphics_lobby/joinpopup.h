#ifndef JOINPOPUP_H
#define JOINPOPUP_H

#include <QDialog>
#include "playerpick.h"
#include "../client/lobby.h"

namespace Ui {
class JoinPopUp;
}

class JoinPopUp : public QDialog
{
    Q_OBJECT

public:
    //explicit JoinPopUp(QWidget *parent = nullptr);
    JoinPopUp(Lobby* lobby, QWidget *parent = nullptr);
    ~JoinPopUp();

private slots:
    void on_joinButton_clicked();

private:
    Ui::JoinPopUp *ui;

    Lobby* lobby;

    PlayerPick* player_pick;
};

#endif // JOINPOPUP_H
