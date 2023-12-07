#include "contrat.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <string>
#include <QPdfWriter>
#include <QPainter>
//constrecteur pardefaut
contrat::contrat()
{
     CONTRATID=0;
     DATEDEBUT="";
     DATEFIN="";
     MONTANT="";

}
//constrecteur parametre
contrat::contrat(int CONTRATID,QString DATEDEBUT,QString DATEFIN,QString MONTANT)
{
     this->CONTRATID=CONTRATID;
     this->DATEDEBUT=DATEDEBUT;
       this->DATEFIN=DATEFIN;
     this->MONTANT=MONTANT;


}

void contrat::setCONTRATID(int CONTRATID){this->CONTRATID=CONTRATID;}
void contrat::setDATEDEBUT(QString DATEDEBUT){this->DATEDEBUT=DATEDEBUT;}
void contrat::setDATEFIN(QString DATEFIN){this->DATEFIN=DATEFIN;}
void contrat::setMONTANT( QString MONTANT){this->MONTANT=MONTANT;}


bool contrat::ajouter()
{
    QSqlQuery query;
    QString CONTRATID_string=QString::number(CONTRATID);


         query.prepare("INSERT INTO GESTIONCONTRAT (CONTRATID,DATEDEBUT,DATEFIN,MONTANT) "
                       "VALUES (:CONTRATID,:DATEDEBUT,:DATEFIN,:MONTANT)");
         query.bindValue(":CONTRATID",CONTRATID_string);
         query.bindValue(":DATEDEBUT",DATEDEBUT);
         query.bindValue(":DATEFIN",DATEFIN);
         query.bindValue(":MONTANT",MONTANT);



         return query.exec();

}


QSqlQueryModel* contrat::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT* FROM GESTIONCONTRAT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CONTRATID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATEDEBUT"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATEFIN"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("MONTANT"));






    return model;
};
bool contrat::supprimer(int CONTRATID){
    QSqlQuery query;
    QString res = QString::number(CONTRATID);
    query.prepare("DELETE FROM GESTIONCONTRAT WHERE CONTRATID=:CONTRATID");
    query.bindValue(":CONTRATID", res);
    if (!query.exec()) {
        return false;  // Failed to execute the query
    }
    if (query.numRowsAffected() == 0) {
        return false;  // No rows were affected
    }
    return true;
}


bool contrat::modifier(int CONTRATID,QString DATEDEBUT,QString DATEFIN,QString MONTANT)
{
    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM GESTIONCONTRAT WHERE CONTRATID = :CONTRATID");
         query.bindValue(":CONTRATID", CONTRATID);
         query.exec();
         query.next();
         int count = query.value(0).toInt();
         if (count == 0) {
             return false;
         }

         QString CONTRATID_string = QString::number(CONTRATID);
         query.prepare("UPDATE GESTIONCONTRAT SET DATEDEBUT = COALESCE(:DATEDEBUT, DATEDEBUT), DATEFIN = COALESCE(:DATEFIN, DATEFIN),MONTANT = COALESCE(:MONTANT, MONTANT) WHERE CONTRATID = :CONTRATID");
         query.bindValue(":CONTRATID", CONTRATID_string);
         query.bindValue(":DATEDEBUT", DATEDEBUT.isEmpty() ? QVariant(QVariant::String) : DATEDEBUT);
         query.bindValue(":DATEFIN", DATEFIN.isEmpty() ? QVariant(QVariant::String) : DATEFIN);
         query.bindValue(":MONTANT", MONTANT.isEmpty() ? QVariant(QVariant::String) : MONTANT);



         return query.exec();
}
void contrat::recherche(QTableView * affiche_tab ,int CONTRATID)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString CONTRATID_string=QString::number(CONTRATID);

   QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from GESTIONCONTRAT where CONTRATID like '%"+CONTRATID_string+"%'  ;");


    query->exec();
    model->setQuery(*query);
    affiche_tab->setModel(model);
    affiche_tab->show();




}

QSqlQueryModel* contrat::trier()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from GESTIONCONTRAT ORDER BY CONTRATID");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CONTRATID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATEDEBUT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATEFIN"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MONTANT"));
    return model;
}
void  contrat::telechargerPDF(){

                     QPdfWriter pdf("C:\\Users\\21655\\Documents\\projet\\import.pdf");
                     QPainter painter(&pdf);
                    int i = 4000;
                         painter.setPen(Qt::blue);
                         painter.setFont(QFont("Arial", 30));
                         painter.drawText(1100,1200,"gestion contrat");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial",14));
                         painter.drawRect(100,100,7300,2600);
                         painter.drawRect(0,3000,9600,500);
                         painter.setFont(QFont("Arial",8));
                         painter.drawText(300,3300,"CONTRATID");
                         painter.drawText(1300,3300,"DATEDEBUT");
                         painter.drawText(2200,3300,"DATEFIN");
                         painter.drawText(3200,3300,"MONTANT");


//partie design
     //   importation des donnees de la base vers qt

                         QSqlQuery query;

                         query.prepare("select * from GESTIONCONTRAT");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(300,i,query.value(0).toString());
                             painter.drawText(1300,i,query.value(1).toString());
                             painter.drawText(2300,i,query.value(2).toString());
                             painter.drawText(3300,i,query.value(3).toString());



                            i = i + 500;
                         }}
QSqlQueryModel * contrat::afficherHistorique()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from HISTORIQUE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Activité"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date"));

    return model;
}/*
int contrat::getContratIDIfExists(int CONTRATID) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM GESTIONCONTRAT WHERE CONTRATID = :CONTRATID");
    query.bindValue(":CONTRATID", CONTRATID);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            // If count is greater than 0, the ID exists; return the CONTRATID
            return CONTRATID;
        }
    }

    // Handle the case where the query execution fails or the ID doesn't exist
    // You might throw an exception, return a specific value, or handle it based on your needs
    return -1; // Placeholder value; you can choose a meaningful default or special value
}*/
double contrat::getTemperatureForLait(double CONTRATID) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM GESTIONCONTRAT WHERE CONTRATID = :CONTRATID");
    query.bindValue(":CONTRATID", CONTRATID);

    if (query.exec() && query.next()) {
        double CONTRATID = query.value("CONTRATID").toDouble();
        return CONTRATID;
    }

    // Return an appropriate value when no data is found
    // You might want to throw an exception, log an error, or return a specific default value
    return -1.0; // Adjust the default value as needed
}

bool  contrat::doesCINExist(int CONTRATID) {


        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM GESTIONCONTRAT WHERE CONTRATID = :CONTRATID");
        query.bindValue(":CONTRATID", CONTRATID);

        if (query.exec() && query.next()) {
            return query.value(0).toInt() > 0; // If count is greater than 0, the ID exists
        }

        // Handle the case where the query execution fails or doesn't return a result
        return false;

}
double contrat::getmontant_b(int CONTRATID) {
    QSqlQuery query;
    query.prepare("SELECT MONTANT FROM GESTIONCONTRAT WHERE CONTRATID = :CONTRATID");
    query.bindValue(":CONTRATID", CONTRATID);

    if (query.exec() && query.next()) {
        double MONTANT = query.value("MONTANT").toDouble();
        return MONTANT;
    }

    // Return an appropriate value when no data is found
    // You might want to throw an exception, log an error, or return a specific default value
    return -1.0; // Adjust the default value as needed
}
