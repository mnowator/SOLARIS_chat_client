#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "connectdialog.h"

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
    void getAdress(QString adress, QString nickname);
    void connectedToHost();
    void readFromServer();
    void sendToServer();

private:
    Ui::MainWindow *ui;

    ConnectDialog* connectDialog;
    QTcpSocket* socket;
    QString nickname;
    QStringList userList;

    void displayConnectDialog();
    void connectToServer(QString ip, QString port, QString nickname);
    void updateUsersList(QString rawData);
    QString processText(QString text);
};

#endif // MAINWINDOW_H
