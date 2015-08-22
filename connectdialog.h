#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QWidget>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();

signals:
    void sendAdress(QString adress, QString nickname);
    void quit();

private slots:
    void connectClicked();
    void quitClicked();

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
