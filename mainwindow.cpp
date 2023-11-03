#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "menu.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
if (username =="test" && password =="test"){

   QMessageBox::information (this,"login","usernameand password is correct");
this->hide();
      menu menu ;
      menu.setModal(true);

      menu.exec();

}
else {
   QMessageBox::warning (this,"login","usernameand password is not correct");
}
}
