#ifndef REGISTERCLIENTPJ_H
#define REGISTERCLIENTPJ_H

#include "login.h"

#include <QDialog>
#include <QSqlDatabase>
#include <QVector>
#include <QLineEdit>

namespace Ui {
class registerclientpj;
}

class registerclientpj : public QDialog
{
    Q_OBJECT

public:
    explicit registerclientpj(QWidget *parent = 0);
    ~registerclientpj();

private slots:
    void on_pesquisar_client_clicked();

    void on_deleteAllButton_clicked();

    void on_salvar_clicked();

    void on_pj_cnpj_returnPressed();

private:
    Ui::registerclientpj *ui;
    QSqlDatabase db;
    QString sqlCommand;
    QVector<QLineEdit *> fields_pj;
    login lg;

public:
    void setFoundCNPJ(QString str);
};

#endif // REGISTERCLIENTPJ_H
