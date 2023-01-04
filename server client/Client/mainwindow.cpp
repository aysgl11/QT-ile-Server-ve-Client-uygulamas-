#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      socket(this)
{
    ui->setupUi(this);
    socket.connectToHost(QHostAddress("192.168.1.105"), 5000);
    connect(&socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    connect(ui->sendButton, SIGNAL(pressed()), this, SLOT(onSendButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyRead()
{
    QByteArray data = socket.readAll();
    qDebug() << data;



    ui->textEdit->append(QString::fromStdString( data.toStdString()));


}

void MainWindow::onSendButtonPressed()
{
    qDebug() << "onSendButtonPressed";
    QString text = ui->lineEdit->text();

    ui->lineEdit->setText("");

    socket.write(QByteArray::fromStdString(text.toStdString()));


}
