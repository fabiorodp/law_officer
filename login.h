#ifndef LOGIN_H
#define LOGIN_H
#include "mainwindow.h"

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_loginButton_clicked();

private:
    Ui::login *ui;
    QString ipadress;
    QString port;
    QString dbName;
    QString user;
    QString pass;
    MainWindow mw;

public:
    QSqlDatabase db;
    void connClose();
    bool connOpen();
};

#endif // LOGIN_H
