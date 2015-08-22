#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "connectdialog.h"

#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->messageHolder->document()->setMaximumBlockCount(1000);

    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connectedToHost()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readFromServer()));

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(sendToServer()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendToServer()));

    displayConnectDialog();

    ui->lineEdit->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete connectDialog;
    delete socket;
}

void MainWindow::getAdress(QString adress, QString name)
{
    QStringList strList = adress.split(":");
    nickname = name;

    if ( strList.size() < 2 || strList.size() > 2 || nickname.length() == 0 )
    {
        displayConnectDialog();
    }
    else
    {
        show();

        connectToServer(strList[0], strList[1], nickname);
    }
}

void MainWindow::displayConnectDialog()
{
    connectDialog = new ConnectDialog();

    connectDialog->show();

    connect(connectDialog, SIGNAL(sendAdress(QString,QString)), this, SLOT(getAdress(QString,QString)));
    connect(connectDialog, SIGNAL(quit()), this, SLOT(close()));
}

void MainWindow::connectToServer(QString adress, QString port, QString nickname)
{

    ui->messageHolder->append(tr("Attempting to connect [")+adress+tr(":")+port+tr("]..."));

    socket->connectToHost(QHostAddress(adress), port.toUShort(0,10));
}

void MainWindow::connectedToHost()
{
    QString loginText = "/NICK " + nickname;


    socket->write(loginText.toStdString().c_str()); // autologin
    socket->write("/LIST"); // users list
}

void MainWindow::readFromServer()
{
    QString data;

    while (socket->bytesAvailable())
    {
       data += socket->readAll();
    }

    ui->messageHolder->moveCursor(QTextCursor::End);
    ui->messageHolder->textCursor().insertText(processText(data));
    ui->messageHolder->moveCursor(QTextCursor::End);

    while ( ui->messageHolder->document()->lineCount() > 1000 )
    {
        ui->messageHolder->textCursor().movePosition(QTextCursor::Start);
        ui->messageHolder->textCursor().select(QTextCursor::LineUnderCursor);
        ui->messageHolder->textCursor().removeSelectedText();
    }
}

void MainWindow::sendToServer()
{
    QString textToSend = ui->lineEdit->text() + "\n";
    socket->write(textToSend.toStdString().c_str());
    ui->lineEdit->clear();
}

void MainWindow::updateUsersList(QString rawData)
{
}

QString MainWindow::processText(QString text)
{
    bool isServerRespond = true;
    QStringList const serverResponds = { "[SERVER]", "<SERVER>" };
    QStringList const serverCommands = { "LOGGEDIN", "CONNECTED USERS" };

    for ( auto it=serverResponds.cbegin(); it<serverResponds.cend(); ++it )
        for ( unsigned i=0; i<(*it).length(); ++i )
            if ( (*it).at(i) != text[i] )
                isServerRespond = false;

    if ( isServerRespond )
    {
        text = text.remove(0, serverResponds[0].length()); // remove server pretext

        for ( auto it=serverCommands.cbegin(); it<serverCommands.cend(); ++it )
        {
            bool commandPassed = true;

            for ( unsigned i=0; i<(*it).length(); ++i )
                if ( (*it).at(i) != text[i] )
                    commandPassed = false;

            if ( commandPassed )
            {
                // to fill
            }
        }
    }

    return "[" + QTime::currentTime().toString() + "] " + text;
}






















