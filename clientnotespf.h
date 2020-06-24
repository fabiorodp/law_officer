#ifndef CLIENTNOTESPF_H
#define CLIENTNOTESPF_H

#include <QDialog>
#include <QSqlDatabase>
#include <QVector>
#include <QLineEdit>

namespace Ui {
class clientnotespf;
}

class clientnotespf : public QDialog
{
    Q_OBJECT

public:
    explicit clientnotespf(QWidget *parent = 0);
    ~clientnotespf();

private slots:
    void on_encontrar_cliente_button_clicked();

    void on_tableview_notespf_clients_doubleClicked(const QModelIndex &index);

    void on_pushButton_notespf_salvar_clicked();

    void on_tableView_notespf_ultimas_anotacoes_doubleClicked(const QModelIndex &index);

private:
    Ui::clientnotespf *ui;
    QSqlDatabase db;
    QString sqlCommand;
    QString found_value;
};

#endif // CLIENTNOTESPF_H
