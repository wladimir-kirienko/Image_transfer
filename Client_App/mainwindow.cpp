#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Изображение еще не загружено...");

    /* Создаем строку для регулярного выражения */
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    /* Создаем регулярное выражение с применением строки, как
     * повторяющегося элемента
     */
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    /* Создаем Валидатор регулярного выражения с применением
     * созданного регулярного выражения
     */
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    /* Устанавливаем Валидатор на QLineEdit */
    ui->lineEdit->setValidator(ipValidator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
      tr("Открыть файл..."), "", tr("Изображения (*.png)"));

    if (fileName.isEmpty())
        return;

    if (myImage.load(fileName)){
        QPixmap img(fileName);
        ui->label->setPixmap(img);
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        myImage.save(&buffer, "PNG"); // writes image into ba in PNG format
        ui->statusBar->showMessage("Изображение загружено");
    }
    else{
       ui->label->setText("Ошибка загрузки изображения");
       ui->statusBar->showMessage("Ошибка загрузки изображения");
    }
}

void MainWindow::on_pushButton_send_clicked()
{
    if (!myImage.isNull()){
        client.SetImageData(&ba);
        //client.start("127.0.0.1", 8888);
        client.start(ui->lineEdit->text(), 8888);
        ui->statusBar->showMessage("Изображение передано");
    }
}
