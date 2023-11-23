#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "voitures.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>
#include <QRegExp>
#include <QPainter>
#include <QPdfWriter>
#include <QTextStream>
#include <QtCharts>
#include <QChartView>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , Ui(new Ui::MainWindow)
{
    Ui->setupUi(this);
    Ui->affichertab->setModel(etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete Ui;
}
void MainWindow::on_pushButton_clicked()
{
    QString marque=Ui->le_marque->text();
    QString modele=Ui->le_modele->text();
    int afb=Ui->le_afb->text().toInt();
    QString plaque_dimmat=Ui->le_plaque_dimmat->text();
    int kilometrage=Ui->le_kilometrage->text().toInt();
    QString etat=Ui->le_etat->text();
    int tarifsloca=Ui->le_tarifs->text().toInt();




    voitures v (marque,modele,afb,plaque_dimmat,kilometrage,etat,tarifsloca);
    bool test=v.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ajouter"),
                    QObject::tr("ajouter successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("ajouter"),
                    QObject::tr("ajouter failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
      Ui->affichertab->setModel(etmp.afficher());
}

void MainWindow::on_pushButton_3_clicked()
{
    {
        voitures v;
        QString plaque_dimmat=Ui->lineEdit_8->text();
        bool test=etmp.supprimer(plaque_dimmat);
                 if(test)
                 {
                   QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                                 QObject::tr(" supprimé.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

                 }
                 else
                 {QMessageBox::critical(nullptr, QObject::tr("supprimer"),
                                 QObject::tr("Erreur !.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
                 Ui->affichertab->setModel(etmp.afficher());
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    QString marque=Ui->le_marque_2->text();
    QString modele=Ui->le_modele_2->text();
    int afb=Ui->le_afb_2->text().toInt();
    QString plaque_dimmat=Ui->le_plaque_dimmat_2->text();
    int kilometrage=Ui->le_kilometrage_2->text().toInt();
    QString etat=Ui->le_etat_2->text();
    int tarifsloca=Ui->le_tarifs_2->text().toInt();




    voitures v (marque,modele,afb,plaque_dimmat,kilometrage,etat,tarifsloca);
    bool test=v.modifier(marque,modele,afb,plaque_dimmat,kilometrage,etat,tarifsloca);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("modifier"),
                    QObject::tr("modifier successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("modifier"),
                    QObject::tr("modifier failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
      Ui->affichertab->setModel(etmp.afficher());
}


void MainWindow::on_pushButton_2_clicked()
{
    voitures v;
    Ui->affichertab_1->setModel(v.tri_annee());
}

void MainWindow::on_pushButton_5_clicked()
{
    voitures v;
    Ui->affichertab_1->setModel(v.tri_tarifs());
}
















void MainWindow::on_pdf_clicked()
{

    QPdfWriter pdf("C:/projet_pdf/pdf");
    int i = 4000;
    QPainter painter(&pdf);
    QString strStream;

    QTextStream out(&strStream);
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000,1400,"Liste Des Voitures");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 7));
    painter.setPen(Qt::darkCyan);
    painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3000,9400,500);
    painter.setPen(Qt::black);
    painter.drawText(300,3300," marque");
    painter.drawText(1300,3300,"modele");
    painter.drawText(2300,3300,"afb");
    painter.drawText(3300,3300,"plaque_dimmat");
    painter.drawText(4300,3300,"kilometrage");
    painter.drawText(5300,3300,"etat");
    painter.drawText(6300,3300,"tarifsloca");
    painter.setPen(Qt::darkCyan);
    painter.drawRect(100,3000,9400,9000);
    painter.setPen(Qt::black);
    QSqlQuery query;
    query.prepare("select * from VOITURES");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1300,i,query.value(1).toString());
        painter.drawText(2300,i,query.value(2).toString());
        painter.drawText(3300,i,query.value(3).toString());
        painter.drawText(4300,i,query.value(4).toString());
        painter.drawText(5300,i,query.value(5).toString());
        painter.drawText(6300,i,query.value(6).toString());
        i +=350;
    }
        QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
        QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_6_clicked()
{
    voitures v;
        Ui->tabchercher->setModel(v.recherche(Ui->cherche->text(),Ui->cherche->text()));

}




void MainWindow::on_pushButton_7_clicked()
{
    {
        QSqlQueryModel*model=new QSqlQueryModel();
            model->setQuery("SELECT etat FROM VOITURES ");

        int countdispo = 0;
        int countindispo = 0;

        for (int i = 0; i < model->rowCount(); i++) {
            QString status_a = model->record(i).value("etat").toString();

            if (status_a == "dispo") {
                countdispo++;
            } else if (status_a == "indispo") {
                countindispo++;
            }
    }
        int total = countdispo + countindispo ;

           QPieSeries *series = new QPieSeries();
           series->append("dispo", countdispo);
           series->append("indispo", countindispo);

           if (countdispo != 0) {
               QPieSlice *slice = series->slices().at(0);
               slice->setLabel("dispo" + QString("%1%").arg(100*slice->percentage(),3,'f',1));
               slice->setLabelVisible();
               slice->setPen(QPen(Qt::cyan));
           }

           if (countindispo != 0) {
               QPieSlice *slice1 = series->slices().at(1);
               slice1->setLabel("indispo" + QString("%1%").arg(100*slice1->percentage(),3,'f',1));
               slice1->setLabelVisible();
               slice1->setBrush(QColor(Qt::red));
           }

           QChart *chart = new QChart();
           chart->addSeries(series);
           chart->setTitle("Total " + QString::number(total));

           QChartView *chartView = new QChartView(chart);
           chartView->setRenderHint(QPainter::Antialiasing);
           chartView->resize(1000, 500);

           chart->legend()->hide();
           chartView->show();

           }
}

void MainWindow::on_pushButton_8_clicked()
{

}
