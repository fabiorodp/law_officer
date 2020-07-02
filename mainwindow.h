#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSair_triggered();

    void on_action_Cadastrar_Pessoa_Fisica_triggered();

    void on_action_Cadastrar_Pessoa_Juridica_triggered();

    void on_action_Notes_Pessoa_Fisica_triggered();

    void on_action_Notes_Pessoa_Juridica_triggered();

private:
    Ui::MainWindow *ui;

public:
    QString permissao;
    void setPermissao(QString permissao);
};

#endif // MAINWINDOW_H
