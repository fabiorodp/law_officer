#include "login.h"
#include "ui_login.h"

// Libraries necessary to connect to the dataserver:
#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>

// Other libraries:
#include<QDebug>
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_loginButton_clicked()
{
    // Declare db variable, in private, at mainwindow.h as: 'QSqlDatabase db;', then:
    db = QSqlDatabase::addDatabase("QMYSQL");

    // Connecting to the database:
    QString ipadress = ui -> ipadress -> text();
    QString port = ui -> port -> text();
    QString user = ui -> userInput -> text();
    QString pass = ui -> passwordInput -> text();

    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("FRPAdv");
    db.setUserName(user);
    db.setPassword(pass);

    // Checking if it connects successfully:
    if (db.open())
    {
        qDebug() << "Database Connected.";
        QMessageBox::information(this, "Login successful", "Login successful.");
        hide();
    }
    else
    {
        qDebug() << "Failed to connect to the database.";
        QMessageBox::information(this, "Login failed.", "Username or password invalid.");
    }
}
