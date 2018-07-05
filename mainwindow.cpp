#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a new QGraphicsScene and show it on the ui
    scene = new BoardScene();
    scene->setBackgroundBrush(QColor(120, 120, 120));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

