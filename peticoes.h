#ifndef PETICOES_H
#define PETICOES_H

#include <QDialog>

namespace Ui {
class peticoes;
}

class peticoes : public QDialog
{
    Q_OBJECT

public:
    explicit peticoes(QWidget *parent = 0);
    ~peticoes();

private:
    Ui::peticoes *ui;
};

#endif // PETICOES_H
