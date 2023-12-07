#include "contrat_ar.h"
#include "contrat.h"
#include "ui_contrat_ar.h"
#include "arduino.h"
#include <QDebug>
#include<QMessageBox>
int j=0;
contrat_ar::contrat_ar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::contrat_ar)
{
    ui->setupUi(this);

   int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(on_caa_clicked())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

contrat_ar::~contrat_ar()
{
    delete ui;
}

void contrat_ar::on_pushButton_clicked(){


    data = A.read_from_arduino(); // Assuming data is a QString

}

void contrat_ar::on_caa_clicked()
{
    int CONTRATID=ui->id_ca->text().toInt();

       contrat c;
    data=A.read_from_arduino();
   int d =data.toInt();



    if(c.doesCINExist(CONTRATID) && d==1)
    {
      QMessageBox::information(nullptr, QObject::tr("valide"),
                   QObject::tr("cin et carte correct:accés valide .\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);



      double MONTANT = c.getmontant_b(CONTRATID);
      QString MONTANTString = QString::number(MONTANT);

          QByteArray dataToSend = MONTANTString.toUtf8();

           qDebug() << dataToSend;

           A.write_to_arduino(dataToSend);

  }


}

