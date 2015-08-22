#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);

    connect(ui->nickname, SIGNAL(returnPressed()), this, SLOT(connectClicked()));
    connect(ui->adress, SIGNAL(returnPressed()), this, SLOT(connectClicked()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectClicked()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(quitClicked()));
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::connectClicked()
{
    emit sendAdress(ui->adress->text(), ui->nickname->text());

    close();
}

void ConnectDialog::quitClicked()
{
    emit quit();

    close();
}


