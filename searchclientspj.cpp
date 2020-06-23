#include "searchclientspj.h"
#include "ui_searchclientspj.h"

searchclientspj::searchclientspj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchclientspj)
{
    ui->setupUi(this);
}

searchclientspj::~searchclientspj()
{
    delete ui;
}
