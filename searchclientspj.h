#ifndef SEARCHCLIENTSPJ_H
#define SEARCHCLIENTSPJ_H

#include "login.h"

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class searchclientspj;
}

class searchclientspj : public QDialog
{
    Q_OBJECT

public:
    explicit searchclientspj(QWidget *parent = 0);
    ~searchclientspj();

private slots:
    void on_searchButtonPJ_clicked();

    void on_searchTablePJ_doubleClicked(const QModelIndex &index);

private:
    Ui::searchclientspj *ui;
    QSqlDatabase db;
    QString sqlCommand;
    QString foundCNPJ;
    login lg;
};

#endif // SEARCHCLIENTSPJ_H
