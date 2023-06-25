#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QCloseEvent>

/* MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
} */

MainWindow::MainWindow(Lobby* lobby, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , lobby(lobby)
    , join_pop_up (nullptr)
    , create_pop_up (nullptr)
{
    ui->setupUi(this);
    int id = QFontDatabase::addApplicationFont(":AmazMegaGrungeOne.ttf");
   
    if (id != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty()) {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes

            QFont font(fontFamily, 24); // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            ui->createButton->setFont(font);
            ui->joinButton->setFont(font);
            ui->settingsButton->setFont(font);
            ui->exitButton->setFont(font);
            ui->startButton->setFont(font);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    if (join_pop_up != nullptr) delete join_pop_up;
    if (create_pop_up != nullptr) delete create_pop_up;
}

void MainWindow::on_createButton_clicked() {
    create_pop_up = new createPopUp(lobby);
    create_pop_up->show();
}


void MainWindow::on_joinButton_clicked() {
    join_pop_up = new JoinPopUp(lobby);
    join_pop_up ->show();
}

void MainWindow::on_startButton_clicked() {
    this->close();
    lobby->exit_lobby();
}

void MainWindow::on_exitButton_clicked() {
    QApplication::exit();
}
