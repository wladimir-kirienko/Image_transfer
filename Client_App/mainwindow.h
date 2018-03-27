#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_load_clicked();

    void on_pushButton_send_clicked();

private:
    Ui::MainWindow *ui;
    QByteArray ba;
    Client client;
    QImage myImage;
};

#endif // MAINWINDOW_H
