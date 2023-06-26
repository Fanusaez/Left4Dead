#ifndef PLAYERPICK_H
#define PLAYERPICK_H

#include <QDialog>
#include "../client/lobby.h"

namespace Ui {
class PlayerPick;
}

class PlayerPick : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerPick(Lobby* lobby, QWidget *parent = nullptr);
    ~PlayerPick();

private slots:
    void on_idfButton_clicked();

    void on_scouttButton_clicked();

    void on_p90Button_clicked();

    void on_pushButton_clicked();

protected:
     void closeEvent(QCloseEvent *event);

private:
    Ui::PlayerPick *ui;

    Lobby* lobby;
};

#endif // PLAYERPICK_H
