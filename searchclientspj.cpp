#include "searchclientspj.h"
#include "ui_searchclientspj.h"
#include "registerclientpj.h"

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

searchclientspj::searchclientspj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchclientspj)
{
    ui->setupUi(this);
    setWindowTitle("Registro de Cliente - Pessoa Jurídica");
}

searchclientspj::~searchclientspj()
{
    delete ui;
}


void searchclientspj::on_searchButtonPJ_clicked()
{
    if (ui->search_razao_social -> text() == "")
    {
        QMessageBox::critical(this, "Campo obrigatório não preenchido", "O campo razão social não pode estar em branco.");
    }
    else
    {
    // Conectando ao banco de dados:
    lg.connOpen();
    QSqlQuery query(db);

    QString searchRazaoSocial = ui -> search_razao_social -> text();

    // Comando SQL:
    sqlCommand = "SELECT `pj_razao_social`, `pj_cnpj`, `pj_nome_do_adm`, `pj_nascimento`, `pj_telefone`, `pj_celular`"
            "FROM `clients_PJ` WHERE `pj_razao_social` LIKE '%" +searchRazaoSocial+ "%'";

    query.exec(sqlCommand);

    QSqlQueryModel *model = new QSqlQueryModel;
    model -> setQuery(query);

    ui -> searchTablePJ -> setModel(model);
    ui -> searchTablePJ -> resizeColumnsToContents();

    qDebug() << query.lastError();
    }
    lg.connClose();
}

void searchclientspj::on_searchTablePJ_doubleClicked(const QModelIndex &index)
{
    QVariant searchCNPJ = ui -> searchTablePJ -> model() -> data(index);
    foundCNPJ = searchCNPJ.toString();

    registerclientpj * registerclientpj_ = new registerclientpj(this);
    registerclientpj_ -> setFoundCNPJ(foundCNPJ);
    registerclientpj_ -> exec();
    close();
}
