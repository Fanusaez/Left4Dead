#ifndef JOINPOPUP_H
#define JOINPOPUP_H

#include <QDialog>
#include "playerpick.h"
#include "../client/lobby.h"
#include <QIntValidator>

namespace Ui {
class JoinPopUp;
}

class JoinPopUp : public QDialog
{
    Q_OBJECT

public:
    //explicit JoinPopUp(QWidget *parent = nullptr);
    JoinPopUp(Lobby* lobby, QPushButton* startButton, QWidget *parent = nullptr);
    ~JoinPopUp();

private slots:
    void on_joinButton_clicked();

    void on_selectSoldier_clicked();
private:
    Ui::JoinPopUp *ui;

    Lobby* lobby;

    PlayerPick* player_pick;

    QPushButton* startButton;

    QIntValidator* validator;
    
};

#endif // JOINPOPUP_H
