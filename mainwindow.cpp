#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <QHostAddress>
#include <QMessageBox>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      socket{new QTcpSocket{this}}
{
    ui->setupUi(this);
    ui->controlsFrame->hide();

    connect(this, SIGNAL(newMessage(QByteArray)),this, SLOT(displayMessage(QByteArray)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discardSocket()));

    socket->connectToHost("192.168.1.13",6789);
    if(socket->waitForConnected())
        qDebug() << "connected";
    else{
       qDebug() << "not connected";
        exit(EXIT_FAILURE);
    }
}

void MainWindow::writeCommand(const Command commandToSend)
{
    if(!timer.canSendCommand()){
        return;
    }

    timer.reset();

    constexpr int msgSize = 1;
    const QByteArray msg{msgSize, static_cast<std::underlying_type<Command>::type>(commandToSend)};
    this->writeMsg(msg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readSocket(){
    QByteArray block = socket->readAll();
    emit newMessage(block);
}

void MainWindow::discardSocket(){

}

void MainWindow::displayMessage(const QByteArray& msg)
{
qDebug() << "Received " << msg<<"\n";
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(!engineStarted){
        return;
    }

    if(event->key() == Qt::Key_W)
    {
        on_fowardBtn_clicked();
    }

    if(event->key() == Qt::Key_S)
    {
        on_backardBtn_clicked();
    }

    if(event->key() == Qt::Key_A)
    {
        on_leftBtn_clicked();
    }

    if(event->key() == Qt::Key_D)
    {
        on_rightBtn_clicked();
    }
}

void MainWindow::writeMsg(const QByteArray arr)
{
    socket->write(arr);
}

void MainWindow::on_fowardBtn_clicked()
{
    writeCommand(Command::MOVE_FORWARD);
}

void MainWindow::on_backardBtn_clicked()
{
    writeCommand(Command::MOVE_BACKWARD);
}

void MainWindow::on_leftBtn_clicked()
{
    writeCommand(Command::MOVE_LEFT);
}

void MainWindow::on_rightBtn_clicked()
{
    writeCommand(Command::MOVE_RIGHT);
}

void MainWindow::on_stopEngine_clicked()
{
    ui->controlsFrame->hide();
    ui->startEngine->show();
    engineStarted = false;
    writeCommand(Command::STOP);
}

void MainWindow::on_startEngine_clicked()
{
    ui->controlsFrame->show();
    ui->startEngine->hide();
    engineStarted = true;
    writeCommand(Command::START);
}
