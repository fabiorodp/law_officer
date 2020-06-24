#include "registerclientpj.h"
#include "ui_registerclientpj.h"
#include "searchclientspj.h"

// Libraries necessary to connect to the dataserver:
#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>

// Other libraries:
#include<QDebug>
#include <QMessageBox>

registerclientpj::registerclientpj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerclientpj)
{
    ui->setupUi(this);

    setWindowTitle("Registro de Cliente - Pessoa Jurídica");

    fields_pj << ui->pj_bairro << ui->pj_cargo << ui->pj_celular << ui->pj_cep << ui->pj_cidade
              << ui->pj_complemento << ui->pj_cpf << ui->pj_endereco << ui->pj_estado << ui->pj_ie
              << ui->pj_irpj << ui->pj_nire << ui->pj_nome_do_adm << ui->pj_nr << ui->pj_pais
              << ui->pj_razao_social << ui->pj_nascimento << ui->pj_telefone;
}

registerclientpj::~registerclientpj()
{
    delete ui;
}

void registerclientpj::setFoundCNPJ(QString str)
{
    ui->pj_cnpj->setText(str);
}

void registerclientpj::on_pesquisar_client_clicked()
{
    searchclientspj * searchclientspj_ = new searchclientspj(this);
    searchclientspj_ -> exec();
    close();
}

void registerclientpj::on_deleteAllButton_clicked()
{
    for (QLineEdit *i : fields_pj)
    {
        i->selectAll();
        i->del();
    }

    ui -> pj_cnpj -> selectAll();
    ui -> pj_cnpj -> del();
}

void registerclientpj::on_salvar_clicked()
{
    // Open database:
    QSqlQuery query(db);

    if (ui->pj_razao_social->text() == "" || ui->pj_ie->text() == "" || ui->pj_cnpj->text() == "../-" || ui->pj_nome_do_adm->text() == ""
            || ui->pj_nascimento->text() == "--" || ui->pj_cpf->text() == "..-" || ui->pj_cargo->text() == "" || ui->pj_endereco->text() == ""
            || ui->pj_nr->text() == "" || ui->pj_bairro->text() == "" || ui->pj_cidade->text() == "" || ui->pj_estado->text() == ""
            || ui->pj_cep->text() == "" || ui->pj_pais->text() == "" || ui->pj_celular->text() == "")
    {
        QMessageBox::critical(this, "Campo obrigatório não preenchido", "Verifique qual campo obrigatório marcado com * não foi preenchido.");

    }
    else
    {
        sqlCommand = "SELECT * FROM `clients_PJ` WHERE `pj_cnpj` LIKE '" +ui->pj_cnpj->text()+ "'";

        if (!query.exec(sqlCommand))
        {
            qDebug() << query.lastError();
            QMessageBox::information(this, "Erro", "Não foi possível conectar ao banco de dados.");
        }
        else
        {
            if (query.size() == 1)
            {
                for (QLineEdit *i : fields_pj)
                {
                    sqlCommand = "UPDATE `clients_PJ` SET `" +i->objectName()+
                            "` = '" +i->text()+ "' WHERE `clients_PJ`.`pj_cnpj` = '" +ui->pj_cnpj->text()+ "'";

                    query.exec(sqlCommand);

                    qDebug() << query.lastError();
                }

                QMessageBox::information(this, "Cadastro / Atualização bem sucedida", "O Cliente com CNPJ nr. "
                                         +ui->pj_cnpj->text()+ " foi cadastrado/atualizado.");
                close();
            }

            else    //doesn't exist a register with input cnpj:
            {
                sqlCommand = "INSERT INTO `clients_PJ` (`pj_razao_social`, `pj_ie`, `pj_cnpj`, `pj_nire`, `pj_irpj`, "
                             "`pj_nome_do_adm`, `pj_nascimento`, `pj_cpf`, `pj_cargo`, `pj_endereco`, `pj_nr`, `pj_complemento`, "
                        "`pj_bairro`, `pj_cidade`, `pj_estado`, `pj_cep`, `pj_pais`, `pj_telefone`, `pj_celular`) VALUES ('"
                        +ui->pj_razao_social->text()+ "', '" +ui->pj_ie->text()+ "', '" +ui->pj_cnpj->text()+
                        "', '" +ui->pj_nire->text()+ "', '" +ui->pj_irpj->text()+ "', '" +ui->pj_nome_do_adm->text()+
                        "', '" +ui->pj_nascimento->text()+ "', '" +ui->pj_cpf->text()+ "', '" +ui->pj_cargo->text()+ "', '" +ui->pj_endereco->text()+
                        "', '" +ui->pj_nr->text()+ "', '" +ui->pj_complemento->text()+ "', '" +ui->pj_bairro->text()+ "', '" +ui->pj_cidade->text()+
                        "', '" +ui->pj_estado->text()+ "', '" +ui->pj_cep->text()+ "', '" +ui->pj_pais->text()+ "', '" +ui->pj_telefone->text()+
                        "', '" +ui->pj_celular->text()+ "')";

                query.exec(sqlCommand);

                qDebug() << query.lastError();

            QMessageBox::information(this, "Cadastro / Atualização bem sucedida", "O Cliente com CNPJ nr. "
                                     +ui->pj_cnpj->text()+ " foi cadastrado/atualizado.");
            close();
            }
        }
    }
}

void registerclientpj::on_pj_cnpj_returnPressed()
{
    // Conectando ao banco de dados:
    QSqlQuery query(db);

    // Comando SQL:
    sqlCommand = "SELECT * FROM clients_PJ";

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
            if (query.value("pj_cnpj").toString() == ui->pj_cnpj->text())
            {
                for (QLineEdit *i : fields_pj)
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
            QMessageBox::information(this, "Cliente não encontrado", "Não foi possível encontrar o CNPJ fornecido.");
        }
    }
}
