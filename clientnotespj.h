#ifndef CLIENTNOTESPJ_H
#define CLIENTNOTESPJ_H

#include "login.h"

#include <QDialog>
#include <QSqlDatabase>
#include <QVector>
#include <QLineEdit>

namespace Ui {
class clientnotespj;
}

class clientnotespj : public QDialog
{
    Q_OBJECT

public:
    explicit clientnotespj(QWidget *parent = 0);
    ~clientnotespj();

private slots:
    void on_encontrar_clientepj_button_clicked();

    void on_tableview_notespj_clients_doubleClicked(const QModelIndex &index);

    void on_pushButton_notespj_salvar_clicked();

    void on_tableView_notespj_ultimas_anotacoes_doubleClicked(const QModelIndex &index);

private:
    Ui::clientnotespj *ui;

    QSqlDatabase db;
    QString sqlCommand;
    QString found_value;
    login lg;
};

#endif // CLIENTNOTESPJ_H
