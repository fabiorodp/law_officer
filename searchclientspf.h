#ifndef SEARCHCLIENTSPF_H
#define SEARCHCLIENTSPF_H

#include "login.h"

#include <QDialog>
#include <QSqlDatabase>
#include <QVector>
#include <QLineEdit>

namespace Ui {
class searchclientspf;
}

class searchclientspf : public QDialog
{
    Q_OBJECT

public:
    explicit searchclientspf(QWidget *parent = 0);
    ~searchclientspf();

private:
    Ui::searchclientspf *ui;

    QSqlDatabase db;
    QString sqlCommand;
    QString foundCPF;
    login lg;

private slots:
    void on_searchButton_clicked();
    void on_searchTable_doubleClicked(const QModelIndex &index);
};

#endif // SEARCHCLIENTSPF_H
