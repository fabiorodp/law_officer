#ifndef REGISTERCLIENTPF_H
#define REGISTERCLIENTPF_H

#include <QDialog>
#include <QSqlDatabase>
#include <QVector>
#include <QLineEdit>

namespace Ui {
class registerclientpf;
}

class registerclientpf : public QDialog
{
    Q_OBJECT

public:
    explicit registerclientpf(QWidget *parent = 0);
    ~registerclientpf();

private slots:
    void on_pesquisar_client_clicked();

    void on_deleteAllButton_clicked();

    void on_salvar_clicked();

    void on_cpf_returnPressed();

private:
    Ui::registerclientpf *ui;
    QSqlDatabase db;
    QString sqlCommand;
    QVector<QLineEdit *> fields_pf;
};

#endif // REGISTERCLIENTPF_H
