#include "searchclientspf.h"
#include "ui_searchclientspf.h"
#include "registerclientpf.h"

// Libraries necessary to connect to the dataserver:
#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include <QSqlQueryModel>

#include <QVariant>
#include <QMap>

// Other libraries:
#include<QDebug>
#include <QMessageBox>

searchclientspf::searchclientspf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchclientspf)
{
    ui->setupUi(this);
}

searchclientspf::~searchclientspf()
{
    delete ui;
}

void searchclientspf::on_searchButton_clicked()
{
    // Conectando ao banco de dados:
    QSqlQuery query(db);

    QString searchName = ui -> searchName -> text();
    QString searchSurname = ui -> searchSurname -> text();

    // Comando SQL:
    sqlCommand = "SELECT nome, sobrenome, cpf, nascimento, telefone, celular FROM `clients_PF` WHERE `nome` LIKE '%"
            +searchName+ "%' OR `sobrenome` LIKE '%" +searchSurname+ "%'";
    query.exec(sqlCommand);

    QSqlQueryModel *model = new QSqlQueryModel;
    model -> setQuery(query);
    ui -> searchTable -> setModel(model);

    qDebug() << query.lastError();
}

void searchclientspf::on_searchTable_doubleClicked(const QModelIndex &index)
{
    QVariant searchCPF = ui -> searchTable -> model() -> data(index);

    /*
    if (searchCPF == QVariant(QString, "336.062.718-08"))
    {
        foundCPF = searchCPF;
        registerClientDialog * register_client = new registerClientDialog(this);
        register_client -> exec();
    }*/

    qDebug() << searchCPF.toString();
}
