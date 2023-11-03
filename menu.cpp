#include "menu.h"
#include "ui_menu.h"
#include "interface1.h"

menu::menu(QWidget *parent) :
    QDialog(parent),

    ui(new Ui::menu)
{
    ui->setupUi(this);


    animation1 = new QPropertyAnimation(ui->pushButton,"geometry");
animation1 ->setDuration(3000);
animation1->setStartValue(ui->pushButton->geometry());
 animation1->setEndValue(QRect( 50, 200, 100, 50));
animation1->start();


animation2 = new QPropertyAnimation(ui->pushButton_2,"geometry");
animation2 ->setDuration(3000);
animation2->setStartValue(ui->pushButton_2->geometry());
animation2->setEndValue(QRect( 150, 200, 100, 50));
animation2->start();


animation3 = new QPropertyAnimation(ui->pushButton_3,"geometry");
animation3 ->setDuration(3000);
animation3->setStartValue(ui->pushButton_3->geometry());
animation3->setEndValue(QRect( 250, 200, 100, 50));
animation3->start();

animation4 = new QPropertyAnimation(ui->pushButton_4,"geometry");
animation4 ->setDuration(3000);
animation4->setStartValue(ui->pushButton_4->geometry());
animation4->setEndValue(QRect( 350, 200, 100, 50));
animation4->start();

animation5 = new QPropertyAnimation(ui->pushButton_5,"geometry");
animation5 ->setDuration(3000);
animation5->setStartValue(ui->pushButton_5->geometry());
animation5->setEndValue(QRect( 450, 200, 100, 50));
animation5->start();
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    this->hide();
          interface1 interface1 ;
          interface1.setModal(true);

          interface1.exec();


}
