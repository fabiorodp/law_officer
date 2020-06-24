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
#include <QApplication>

searchclientspf::searchclientspf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchclientspf)
{
    ui->setupUi(this);
    setWindowTitle("Pesquisar Cliente - Pessoa Física");
}

searchclientspf::~searchclientspf()
{
    delete ui;
}

void searchclientspf::on_searchButton_clicked()
{   
    if (ui->searchName -> text() == "")
    {
        QMessageBox::critical(this, "Campo obrigatório não preenchido", "O campo nome não pode estar em branco.");
    }
    else
    {
    // Conectando ao banco de dados:
    QSqlQuery query(db);

    QString searchName = ui -> searchName -> text();

    // Comando SQL:
    sqlCommand = "SELECT nome, cpf, nascimento, telefone, celular FROM `clients_PF` WHERE `nome` LIKE '%"
            +searchName+ "%'";

    query.exec(sqlCommand);

    QSqlQueryModel *model = new QSqlQueryModel;
    model -> setQuery(query);

    ui -> searchTable -> setModel(model);
    ui -> searchTable -> resizeColumnsToContents();

    qDebug() << query.lastError();
    }
}

void searchclientspf::on_searchTable_doubleClicked(const QModelIndex &index)
{
    QVariant searchCPF = ui -> searchTable -> model() -> data(index);
    foundCPF = searchCPF.toString();

    //registerclientpf setFoundCPF(foundCPF)

    registerclientpf * registerclientpf_ = new registerclientpf(this);
    registerclientpf_ -> setFoundCPF(foundCPF);
    registerclientpf_ -> exec();
    close();
}
