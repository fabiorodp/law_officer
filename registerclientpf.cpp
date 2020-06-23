#include "registerclientpf.h"
#include "ui_registerclientpf.h"
#include "searchclientspf.h"

// Libraries necessary to connect to the dataserver:
#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>

// Other libraries:
#include<QDebug>
#include <QMessageBox>

registerclientpf::registerclientpf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerclientpf)
{
    ui->setupUi(this);

    fields_pf << ui->inss << ui->pispasep << ui->tratamento << ui->nome << ui->sobrenome
              << ui->estado_civil << ui->profissao << ui->nascimento << ui->nome_da_mae
              << ui->rg << ui->endereco << ui->nr << ui->complemento << ui->bairro
              << ui->cidade << ui->estado << ui->cep << ui->pais << ui->telefone << ui->celular;
}

registerclientpf::~registerclientpf()
{
    delete ui;
}

void registerclientpf::on_pesquisar_client_clicked()
{
    searchclientspf * search_clientspf = new searchclientspf(this);
    search_clientspf -> exec();
}

void registerclientpf::on_deleteAllButton_clicked()
{
    for (QLineEdit *i : fields_pf)
    {
        i->selectAll();
        i->del();
    }

    ui -> cpf -> selectAll();
    ui -> cpf -> del();
}

void registerclientpf::on_salvar_clicked()
{
    // Open database:
    QSqlQuery query(db);

    if (ui->cpf->text() == "..-" || ui->tratamento->text() == "" || ui->nome->text() == "" || ui->sobrenome->text() == ""
            || ui->estado_civil->text() == "" || ui->profissao->text() == "" || ui->nascimento->text() == "--"
            || ui->rg->text() == "" || ui->endereco->text() == "" || ui->nr->text() == "" || ui->bairro->text() == ""
            || ui->cidade->text() == "" || ui->cep->text() == "" || ui->pais->text() == "" || ui->celular->text() == "")
    {
        QMessageBox::critical(this, "Campo obrigatório não preenchido", "Verifique qual campo obrigatório marcado com * não foi preenchido.");

    }
    else
    {
        sqlCommand = "SELECT * FROM `clients_PF` WHERE `cpf` LIKE '" +ui->cpf->text()+ "'";

        if (!query.exec(sqlCommand))
        {
            qDebug() << query.lastError();
            QMessageBox::information(this, "Erro", "Não foi possível conectar ao banco de dados.");
        }
        else
        {
            if (query.size() == 1)
            {
                for (QLineEdit *i : fields_pf)
                {
                    sqlCommand = "UPDATE `clients_PF` SET `" +i->objectName()+
                            "` = '" +i->text()+ "' WHERE `clients_PF`.`cpf` = '" +ui->cpf->text()+ "'";

                    query.exec(sqlCommand);

                    qDebug() << query.lastError();
                }

                QMessageBox::information(this, "Cadastro / Atualização bem sucedida", "O Cliente com CPF nr. "
                                         +ui->cpf->text()+ " foi cadastrado/atualizado.");
                close();
            }

            else    //doesn't exist a register with input cpf:
            {
                sqlCommand = "INSERT INTO `clients_PF` (`tratamento`, `nome`, `sobrenome`, `estado_civil`, `profissao`, "
                             "`nascimento`, `nome_da_mae`, `rg`, `cpf`, `inss`, `pispasep`, `endereco`, `nr`, `complemento`, "
                             "`bairro`, `cidade`, `estado`, `cep`, `pais`, `telefone`, `celular`) VALUES ('"
                        +ui->tratamento->text()+ "', '" +ui->nome->text()+ "', '" +ui->sobrenome->text()+
                        "', '" +ui->estado_civil->text()+ "', '" +ui->profissao->text()+ "', '" +ui->nascimento->text()+
                        "', '" +ui->nome_da_mae->text()+ "', '" +ui->rg->text()+ "', '" +ui->cpf->text()+ "', '" +ui->inss->text()+
                        "', '" +ui->pispasep->text()+ "', '" +ui->endereco->text()+ "', '" +ui->nr->text()+ "', '" +ui->complemento->text()+
                        "', '" +ui->bairro->text()+ "', '" +ui->cidade->text()+ "', '" +ui->estado->text()+ "', '" +ui->cep->text()+
                        "', '" +ui->pais->text()+ "', '" +ui->telefone->text()+ "', '" +ui->celular->text()+ "')";

                query.exec(sqlCommand);

                qDebug() << query.lastError();

            QMessageBox::information(this, "Cadastro / Atualização bem sucedida", "O Cliente com CPF nr. "
                                     +ui->cpf->text()+ " foi cadastrado/atualizado.");
            close();
            }
        }
    }
}

void registerclientpf::on_cpf_returnPressed()
{
    // Conectando ao banco de dados:
    QSqlQuery query(db);

    // Comando SQL:
    sqlCommand = "SELECT * FROM clients_PF";

    if (!query.exec(sqlCommand))
    {
        qDebug() << query.lastError();
        QMessageBox::information(this, "Erro", "Não foi possível conectar ao banco de dados.");
    }
    else
    {
        QString not_found = "True";

        while(query.next())
        {
            if (query.value("cpf").toString() == ui->cpf->text())
            {
                for (QLineEdit *i : fields_pf)
                {
                    // Select and delete text before make a new research:
                    i -> selectAll();
                    i -> del();

                    // Search for client and auto-fill the value fields:
                    QString value = query.value(i->objectName()).toString();
                    i -> insert(value);
                    not_found = "False";
                }
            }
        }

        if (not_found == "True")
        {
            on_deleteAllButton_clicked();
            QMessageBox::information(this, "Cliente não encontrado", "Não foi possível encontrar o CPF fornecido.");
        }
    }
}
