#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Import Qt modules
#include <QMainWindow>

// Import custom modules
#include "boardscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    BoardScene *scene;
    QGraphicsScene *scene2;

};

#endif // MAINWINDOW_H
