#include "clientnotespj.h"
#include "ui_clientnotespj.h"

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

clientnotespj::clientnotespj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientnotespj)
{
    ui->setupUi(this);
}

clientnotespj::~clientnotespj()
{
    delete ui;
}

void clientnotespj::on_encontrar_clientepj_button_clicked()
{
    if (ui->lineedit_notespj_nome -> text() == "")
    {
        QMessageBox::critical(this, "Campo obrigatório não preenchido", "O campo razão social não pode estar em branco.");
    }
    else
    {
    // Conectando ao banco de dados:
    QSqlQuery query(db);

    QString notesName = ui -> lineedit_notespj_nome -> text();

    // Comando SQL:
    sqlCommand = "SELECT `pj_cnpj`, `pj_razao_social`, `pj_ie`, `pj_nire`, `pj_irpj`, `pj_nome_do_adm`, `pj_nascimento`, "
            "`pj_cpf`, `pj_cargo`, `pj_endereco`, `pj_nr`, `pj_complemento`, `pj_bairro`, `pj_cidade`, `pj_estado`, `pj_cep`, "
            "`pj_pais`, `pj_telefone`, `pj_celular` FROM `clients_PJ` WHERE `pj_razao_social` LIKE '%" +notesName+ "%'";

    query.exec(sqlCommand);

    QSqlQueryModel *model = new QSqlQueryModel;
    model -> setQuery(query);

    ui -> tableview_notespj_clients -> setModel(model);
    ui -> tableview_notespj_clients -> resizeColumnsToContents();

    qDebug() << query.lastError();
    }
}

void clientnotespj::on_tableview_notespj_clients_doubleClicked(const QModelIndex &index)
{
    QVariant searching_value = ui -> tableview_notespj_clients -> model() -> data(index);
    found_value = searching_value.toString();

    if (found_value[2]=="." && found_value[6]=="." && found_value[10]=="/" && found_value[15]=="-")
    {
        // Conectando ao banco de dados:
        QSqlQuery query(db);

        // Comando SQL:
        sqlCommand = "SELECT date, anotacoes FROM `anotacoes_PJ` WHERE `cnpj` LIKE '" +found_value+ "'";

        query.exec(sqlCommand);
        qDebug() << query.lastError();

        QSqlQueryModel *model = new QSqlQueryModel;
        model -> setQuery(query);

        ui -> tableView_notespj_ultimas_anotacoes -> setModel(model);
        ui -> tableView_notespj_ultimas_anotacoes -> resizeColumnsToContents();
        ui -> label_input_cnpj -> setText(found_value);
    }
}

void clientnotespj::on_pushButton_notespj_salvar_clicked()
{
    // Open database:
    QSqlQuery query(db);

    if (ui->textEdit_notespj->toPlainText() == "")
    {
        QMessageBox::critical(this, "Campo não preenchido", "Não é possível salvar anotações em branco.");

    }
    else
    {
        sqlCommand = "INSERT INTO `anotacoes_PJ` (`date`, `cnpj`, `anotacoes`) VALUES (NOW(), '" +found_value+ "', '"
                +ui->textEdit_notespj->toPlainText()+ "')";

        query.prepare(sqlCommand);

        if (!query.exec())
        {
            qDebug() << query.lastError();
            QMessageBox::information(this, "Erro", "Não foi possível conectar ao banco de dados.");
        }
        else
        {
            QMessageBox::information(this, "Anotação bem sucedida", "Sua anotação foi registrada no CNPJ no. " +found_value+ ".");
            close();
        }
    }
}

void clientnotespj::on_tableView_notespj_ultimas_anotacoes_doubleClicked(const QModelIndex &index)
{
    QVariant searching_del = ui -> tableView_notespj_ultimas_anotacoes -> model() -> data(index);
    QString del = searching_del.toString();

    if (del[4]=="-" && del[7]=="-" && del[10]=="T" && del[13]==":")
    {
        int ret = QMessageBox::critical(this, "Confirmação", "Tem certeza que deseja deletar a anotação de " +del+ "?",
                                        QMessageBox::Ok | QMessageBox:: Cancel);
        if (ret == QMessageBox::Ok)
        {
            // Open database:
            QSqlQuery query(db);

            sqlCommand = "DELETE FROM `anotacoes_PJ` WHERE `anotacoes_PJ`.`date` = \'" +del+ "\'";
            query.prepare(sqlCommand);

            if (!query.exec())
            {
                qDebug() << query.lastError();
                QMessageBox::information(this, "Erro", "Não foi possível conectar ao banco de dados.");
            }
            else
            {
                QMessageBox::information(this, "Removido", "Sua anotação de " +del+ " foi removida com sucesso.");
                close();
            }
        }
    }
}
