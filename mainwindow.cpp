#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "registerclientpf.h"
#include "registerclientpj.h"
#include "clientnotespf.h"
#include "clientnotespj.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Página inicial do FRP Lawyer");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSair_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionConectar_triggered()
{
    login * login_ = new login(this);
    login_ -> exec();
}

void MainWindow::on_action_Cadastrar_Pessoa_Fisica_triggered()
{
    registerclientpf * registerclientpf_ = new registerclientpf(this);
    registerclientpf_ -> exec();
}

void MainWindow::on_action_Cadastrar_Pessoa_Juridica_triggered()
{
    registerclientpj * registerclientpj_ = new registerclientpj(this);
    registerclientpj_ -> exec();
}

void MainWindow::on_action_Notes_Pessoa_Fisica_triggered()
{
    clientnotespf * clientnotespf_ = new clientnotespf(this);
    clientnotespf_ -> exec();
}

void MainWindow::on_action_Notes_Pessoa_Juridica_triggered()
{
    clientnotespj * clientnotespj_ = new clientnotespj(this);
    clientnotespj_ -> exec();
}
