#include "peticoes.h"
#include "ui_peticoes.h"

peticoes::peticoes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::peticoes)
{
    ui->setupUi(this);
}

peticoes::~peticoes()
{
    delete ui;
}
