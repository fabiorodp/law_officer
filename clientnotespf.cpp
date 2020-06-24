#include "clientnotespf.h"
#include "ui_clientnotespf.h"

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

clientnotespf::clientnotespf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientnotespf)
{
    ui->setupUi(this);

    setWindowTitle("Pesquisa e/ou anotações para clientes pessoa física");
}

clientnotespf::~clientnotespf()
{
    delete ui;
}

void clientnotespf::on_encontrar_cliente_button_clicked()
{
    if (ui->lineedit_notes_nome -> text() == "")
    {
        QMessageBox::critical(this, "Campo obrigatório não preenchido", "O campo nome não pode estar em branco.");
    }
    else
    {
    // Conectando ao banco de dados:
    QSqlQuery query(db);

    QString notesName = ui -> lineedit_notes_nome -> text();

    // Comando SQL:
    sqlCommand = "SELECT `cpf`, `nome`, `estado_civil`, `profissao`, `nascimento`, `nome_da_mae`, `rg`, "
            "`inss`, `pispasep`, `endereco`, `nr`, `complemento`, `bairro`, `cidade`, `estado`, `cep`, "
            "`pais`, `telefone`, `celular` FROM `clients_PF` WHERE `nome` LIKE '%" +notesName+ "%'";

    query.exec(sqlCommand);

    QSqlQueryModel *model = new QSqlQueryModel;
    model -> setQuery(query);

    ui -> tableview_notespf_clients -> setModel(model);
    ui -> tableview_notespf_clients -> resizeColumnsToContents();

    qDebug() << query.lastError();
    }
}

void clientnotespf::on_tableview_notespf_clients_doubleClicked(const QModelIndex &index)
{
    QVariant searching_value = ui -> tableview_notespf_clients -> model() -> data(index);
    found_value = searching_value.toString();

    if (found_value[3]=="." && found_value[7]=="." && found_value[11]=="-")
    {
        // Conectando ao banco de dados:
        QSqlQuery query(db);

        // Comando SQL:
        sqlCommand = "SELECT date, anotacoes FROM `anotacoes_PF` WHERE `cpf` LIKE '" +found_value+ "'";

        query.exec(sqlCommand);
        qDebug() << query.lastError();

        QSqlQueryModel *model = new QSqlQueryModel;
        model -> setQuery(query);

        ui -> tableView_notespf_ultimas_anotacoes -> setModel(model);
        ui -> tableView_notespf_ultimas_anotacoes -> resizeColumnsToContents();
        ui -> label_input_cpf -> setText(found_value);
    }
}

void clientnotespf::on_pushButton_notespf_salvar_clicked()
{
    // Open database:
    QSqlQuery query(db);

    if (ui->textEdit_notespf->toPlainText() == "")
    {
        QMessageBox::critical(this, "Campo não preenchido", "Não é possível salvar anotações em branco.");

    }
    else
    {
        sqlCommand = "INSERT INTO `anotacoes_PF` (`date`, `cpf`, `anotacoes`) VALUES (NOW(), '" +found_value+ "', '"
                +ui->textEdit_notespf->toPlainText()+ "')";
        query.prepare(sqlCommand);

        if (!query.exec())
        {
            qDebug() << query.lastError();
            QMessageBox::information(this, "Erro", "Não foi possível conectar ao banco de dados.");
        }
        else
        {
            QMessageBox::information(this, "Anotação bem sucedida", "Sua anotação foi registrada no CPF no. " +found_value+ ".");
            close();
        }
    }
}

void clientnotespf::on_tableView_notespf_ultimas_anotacoes_doubleClicked(const QModelIndex &index)
{
    QVariant searching_del = ui -> tableView_notespf_ultimas_anotacoes -> model() -> data(index);
    QString del = searching_del.toString();

    if (del[4]=="-" && del[7]=="-" && del[10]=="T" && del[13]==":")
    {
        int ret = QMessageBox::critical(this, "Confirmação", "Tem certeza que deseja deletar a anotação de " +del+ "?",
                                        QMessageBox::Ok | QMessageBox:: Cancel);
        if (ret == QMessageBox::Ok)
        {
            // Open database:
            QSqlQuery query(db);

            sqlCommand = "DELETE FROM `anotacoes_PF` WHERE `anotacoes_PF`.`date` = \'" +del+ "\'";
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
