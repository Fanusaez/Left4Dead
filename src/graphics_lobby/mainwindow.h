#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../client/lobby.h"
#include "createpopup.h"
#include "joinpopup.h"
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Lobby* lobby, QWidget *parent = nullptr);
    //MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_createButton_clicked();

    void on_joinButton_clicked();

    void on_startButton_clicked();

    void on_exitButton_clicked();

     void hideTemporaryLabel();

protected:
     void closeEvent(QCloseEvent *event);
     
private:
    Ui::MainWindow *ui;
    Lobby* lobby;
    createPopUp* create_pop_up;
    JoinPopUp* join_pop_up;
    QTimer *timer;
};
#endif // MAINWINDOW_H
