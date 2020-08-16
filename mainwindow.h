#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMetaType>
#include <QTcpSocket>
#include "commands.h"
#include "command_filter_timer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void writeCommand(const Command commandToSend);
    void keyPressEvent(QKeyEvent *event);
    ~MainWindow();


signals:
    void newMessage(QByteArray);

private slots:
    void readSocket();
    void discardSocket();
    void displayMessage(const QByteArray& msg);
    void writeMsg(const QByteArray arr);

    void on_fowardBtn_clicked();

    void on_backardBtn_clicked();

    void on_leftBtn_clicked();

    void on_rightBtn_clicked();

    void on_stopEngine_clicked();

    void on_startEngine_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket* socket;
    bool engineStarted = false;
    CommandFilterTimer timer;

};
#endif // MAINWINDOW_H
