#include "mainwindow.h"

#include <QApplication>

#include "../client/lobby.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lobby lobby(argv[1], argv[2]);
    MainWindow w(&lobby);
    w.show();
    return a.exec();
}
