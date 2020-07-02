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
    setWindowTitle("Conectar ao banco de dados");
}

login::~login()
{
    delete ui;
}

bool login::connOpen()
{
    db.close();
    //db.removeDatabase(QSqlDatabase::defaultConnection);

    // Connecting to the database:
    user = ui -> userInput -> text();
    pass = ui -> passwordInput -> text();

    // Declare db variable, in private, at mainwindow.h as: 'QSqlDatabase db;', then:
    qDebug() << user;
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("");
    db.setPort(3306);
    db.setDatabaseName("");
    db.setUserName("");
    db.setPassword("");

    // Checking if it connects successfully:
    if (db.open())
    {
        qDebug() << "Database Connected.";
        return true;
    }
    else
    {
        qDebug() << "Failed to connect to the database.";
        return false;
    }
}

void login::connClose()
{
    db.close();
    //db.removeDatabase(QSqlDatabase::defaultConnection);
}

void login::on_loginButton_clicked()
{
    user = ui -> userInput -> text();
    pass = ui -> passwordInput -> text();

    //connOpen();
    //QString sqlcommand = "SELECT * FROM users WHERE user_name="+user+" AND user_pass=" +pass+"";
    //QSqlQuery query(db);
    //query.exec(sqlcommand);

    if (user == "Fabio" && pass == "test123")
    {
        connOpen();
        QMessageBox::information(this, "Login successful", "Login successful.");
        close();
    }
    else
    {
        QMessageBox::information(this, "Login failed.", "Username or password invalid.");
    }
}
