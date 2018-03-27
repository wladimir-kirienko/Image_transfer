#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server.setLabel(ui->label);
    server.setStatusBar(ui->statusBar);

    ui->statusBar->showMessage("Ожидание получения изображения...");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Сохранить файл..."), "Безымянный.png", tr("Изображения (*.png)"));

    if (fileName.isEmpty())
        return;

    QPixmap NewPixMap = server.getPixMap();

    if (NewPixMap.isNull())
        return;

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    NewPixMap.save(&file, "PNG");

    ui->statusBar->showMessage("Изображение сохранено");
}
