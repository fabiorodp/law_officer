#ifndef SEARCHCLIENTSPJ_H
#define SEARCHCLIENTSPJ_H

#include <QDialog>

namespace Ui {
class searchclientspj;
}

class searchclientspj : public QDialog
{
    Q_OBJECT

public:
    explicit searchclientspj(QWidget *parent = 0);
    ~searchclientspj();

private:
    Ui::searchclientspj *ui;
};

#endif // SEARCHCLIENTSPJ_H
