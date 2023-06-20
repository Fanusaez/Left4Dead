#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>

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
{
    ui->setupUi(this);
    int id = QFontDatabase::addApplicationFont(":/assets/AmazMegaGrungeOne.ttf");
   
    if (id != -1) {
        std::cout<<"Hola"<<std::endl;
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty()) {
            QString fontFamily = fontFamilies.at(0); // Obtén el nombre de la familia de fuentes

            QFont font(fontFamily, 24); // Crea una instancia de QFont con el nombre de la familia y el tamaño deseado
            ui->createButton->setFont(font);
            ui->joinButton->setFont(font);
            ui->pushButton->setFont(font);
            ui->exitButton->setFont(font);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

