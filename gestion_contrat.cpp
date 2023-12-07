#include "gestion_contrat.h"
#include "ui_gestion_contrat.h"
#include "contrat.h"
#include <vector>
#include <string>
#include <QBuffer>
#include <cstdlib>
#include <ctime>
#include <QSqlError>
#include<QDebug>
#include<QImage>
#include <QPixmap>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include<QTextDocument>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QPrintDialog>
#include <QGraphicsView>
#include <QTabWidget>
#include<QDateEdit>
#include <QSqlQuery>
#include "contrat_ar.h"

gestion_contrat::gestion_contrat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_contrat)
{
    contrat f;
    ui->setupUi(this);
ui->affiche_tab->setModel(f.afficher());
}

gestion_contrat::~gestion_contrat()
{
    delete ui;
}
void gestion_contrat::on_ajouter_clicked(){
    QString CONTRATID_string = ui->CONTRATID->text();
      bool ok;
      int CONTRATID = CONTRATID_string.toInt(&ok);

      if (!ok) {

          QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer ID.");
          return;
      }
      QString DATEDEBUT = ui->DATEDEBUT->text();

      QString DATEFIN = ui->DATEFIN->text();

      QString MONTANT = ui->MONTANT->text();


      contrat tr(CONTRATID,DATEDEBUT,DATEFIN,MONTANT);
      bool test = tr.ajouter();

      QMessageBox msgBox;
      if (test) {
          msgBox.setText("ajout avec succes");
          msgBox.exec();
          ui->CONTRATID->clear();
          ui->DATEDEBUT->clear();
          ui->DATEFIN->clear();
          ui->MONTANT->clear();


      } else {
          msgBox.setText("echec");
          msgBox.exec();
      }

      ui->affiche_tab->setModel(tr.afficher());
      QSqlQuery qry;
      QDateTime dateTime=QDateTime::currentDateTime();


      QString date=dateTime.toString();

      qry.prepare("insert into HISTORIQUE (ACTIVITE,DATEE) values ('ajout contrat',:dateTime)");
      qry.bindValue(":dateTime",dateTime);

      qry.exec();



};
void gestion_contrat::on_supprimer_clicked() {
    contrat f;
    int CONTRATID= ui->CONTRATID->text().toInt();
    bool test = f.supprimer(CONTRATID);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Suppression effectuée.\n"
                                             "Click Ok to exit."), QMessageBox::Ok);
        QSqlQuery qry;
        QDateTime dateTime=QDateTime::currentDateTime();

        QString date=dateTime.toString();

        qry.prepare("insert into HISTORIQUE (ACTIVITE,DATEE) values ('supression contrat',:dateTime)");
        qry.bindValue(":dateTime",dateTime);

        qry.exec();



    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                              QObject::tr("Échec de la suppression.\n"
                                          "Le fournisseur n'existe pas dans la base de données."),
                              QMessageBox::Cancel);
    }
    ui->affiche_tab->setModel(f.afficher());


}


void gestion_contrat::on_modifier_clicked()
{

        int CONTRATID=ui->CONTRATID->text().toInt();
           QString DATEDEBUT = ui->DATEDEBUT->text();
           QString DATEFIN = ui->DATEFIN->text();
           QString MONTANT = ui->MONTANT->text();






              contrat f(CONTRATID,DATEDEBUT,DATEFIN,MONTANT);

                 bool test=f.modifier(CONTRATID,DATEDEBUT,DATEFIN,MONTANT);

                 if(test)

               {ui->affiche_tab->setModel(f.afficher());

               QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                                 QObject::tr("invite modifiée.\n"

                                             "Click ok to exit."), QMessageBox::Ok);



               }

                 else

                     QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                                 QObject::tr("echec d'ajout !.\n"

                                             "Click Cancel to exit."), QMessageBox::Cancel);


}


void gestion_contrat::on_afficher_clicked()
{
    contrat f;
    ui->affiche_tab->setModel(f.afficher());
}


void gestion_contrat::on_affiche_tab_activated(const QModelIndex &index)
{
    QString val=ui->affiche_tab->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from GESTIONCONTRAT where CONTRATID='"+val+"'");
    if(qry.exec())

    {
     while(qry.next())
     {ui->CONTRATID->setText(qry.value(0).toString());
         QString startDateString = qry.value(1).toString();
         QString endDateString = qry.value(2).toString();
         QDate startDate = QDate::fromString(startDateString, "yyyy-MM-dd");  // Adjust the format based on your database
         QDate endDate = QDate::fromString(endDateString, "yyyy-MM-dd");      // Adjust the format based on your database
         // Setting the QDate objects as text in the UI
         ui->DATEDEBUT->setDate(startDate);
         ui->DATEFIN->setDate(endDate);
      ui->MONTANT->setText(qry.value(3).toString());


     }
    }
    else
    {
     QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}


void gestion_contrat::on_tri_clicked()
{
    contrat f;
    ui->affiche_tab->setModel(f.trier());
}

void gestion_contrat::on_pdf_clicked()
{
    contrat f;
    f.telechargerPDF();

    QMessageBox::information(nullptr,QObject::tr("OK"),
               QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);
}

void gestion_contrat::on_chercher_textChanged(const QString &arg1)
{
    contrat f;
    int CONTRATID= ui->chercher->text().toInt();

  f.recherche(ui->affiche_tab,CONTRATID);
    if (ui->chercher->text().isEmpty())
    {
        ui->affiche_tab->setModel(f.afficher());
    }
}

void gestion_contrat::on_stat_clicked()
{
    statistic = new class Statistic(this);
    statistic->setWindowTitle("smart garden | Statistiques");
    statistic->show();
}

void gestion_contrat::on_historique_clicked()
{
    contrat p;
    ui->tableViewHistorique->setModel(p.afficherHistorique());
}

void gestion_contrat::on_tableViewHistorique_activated(const QModelIndex &index)
{
    QString val = ui->tableViewHistorique->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT montant FROM GESTIONCONTRAT WHERE CONTRATID='" + val + "'");

    if (qry.exec()) {
        if (qry.next()) {
            // Retrieve the montant value from the query result
            double montantValue = qry.value(0).toDouble(); // Assuming montant is a numeric field

            // Compare the montant value with 5000
            if (montantValue > 5000) {
                // Do something if montant is over 5000
                qDebug() << "Montant is over 5000!";
            } else {
                // Do something if montant is 5000 or less
                qDebug() << "Montant is 5000 or less.";
            }
        } else {
            // Handle the case where the query returned no results for the given CONTRATID
            qDebug() << "No data found for CONTRATID: " << val;
        }
    } else {
        // Handle the case where the query execution failed
        qDebug() << "Query execution failed:" << qry.lastError().text();
    }
}

void gestion_contrat::on_contrat_a_clicked()
{

    ca = new class contrat_ar(this);
    ca->setWindowTitle("smart garden | Statistiques");
    ca->show();
}
