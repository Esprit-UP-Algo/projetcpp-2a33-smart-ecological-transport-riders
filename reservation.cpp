#include "reservation.h"
#include "client.h"
#include<QSqlQuery>
#include<QtDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QObject>
#include <QSqlQueryModel>
reservation:: reservation()
 {

 CIN=0;
 NOM="";
 PRENOM="";
 MATRICULE="";
 DATEREN="";
 MAIL="";
 NB_PERMIS="";
 MONTANT_TOTAL="";
 }


reservation:: reservation(int CIN,QString NOM,QString PRENOM ,QString MATRICULE ,QString DATEREN,QString MAIL,QString NB_PERMIS,QString MONTANT_TOTAL)
 {
    this->CIN=CIN;
     this->NOM=NOM ;
     this->PRENOM=PRENOM;
     this->MATRICULE =MATRICULE;
     this->DATEREN=DATEREN;
         this->MAIL=MAIL;
      this->NB_PERMIS=NB_PERMIS;

  this->MONTANT_TOTAL=MONTANT_TOTAL;
 }
 //getters
 int reservation::getCIN(){return  CIN;}
 QString reservation::getNOM(){return NOM;}
 QString reservation::getPRENOM(){return PRENOM;}
 QString reservation ::getMATRICULE(){return MATRICULE;}
 QString reservation ::getDATEREN(){return DATEREN;}
 QString reservation ::getMAIL(){return MAIL;}
 QString reservation ::getNB_PERMIS(){return NB_PERMIS;}
 QString reservation ::getMONTANT_TOTAL(){return MONTANT_TOTAL;}
 //setters
 void reservation::setCIN(int CIN)
 {this->CIN=CIN;}

 void reservation::setNOM(QString NOM)
 {this->NOM=NOM;}

 void reservation::setPRENOM(QString PRENOM)
 {this->PRENOM=PRENOM;}

 void reservation::setMATRICULE(QString MATRICULE)
 {this->MATRICULE=MATRICULE;}

 void reservation::setDATEREN(QString DATEREN)
 {this->DATEREN=DATEREN;}
 void reservation::setMAIL(QString MAIL)
 {this->MAIL=MAIL;}
 void reservation::setNB_PERMIS(QString NB_PERMIS)
 {this->NB_PERMIS=NB_PERMIS;}
 void reservation::setMONTANT_TOTAL(QString MONTANT_TOTAL)
 {this->MONTANT_TOTAL=MONTANT_TOTAL;}

 bool reservation::ajouter() {
   QSqlQuery query;

   // Check if CIN already exists
   QString checkQuery = "SELECT * FROM RESERVER WHERE CIN = :CIN";
   query.prepare(checkQuery);
   query.bindValue(":CIN", CIN);
   query.exec();

   if (query.next()) {
     // CIN already exists, abort insertion
     qDebug() << "Error: CIN already exists.";
     return false;
   }

   // CIN doesn't exist, proceed with insertion
   QString insertQuery = "INSERT INTO RESERVER (CIN, NOM, PRENOM, MATRICULE, MAIL, DATEREN, NB_PERMIS, MONTANT_TOTAL)"
                         "VALUES (:CIN, :NOM, :PRENOM, :MATRICULE, :DATEREN, :MAIL, :NB_PERMIS, :MONTANT_TOTAL)";
   query.prepare(insertQuery);
   query.bindValue(":CIN", CIN);
   query.bindValue(":NOM", NOM);
   query.bindValue(":PRENOM", PRENOM);
   query.bindValue(":MATRICULE", MATRICULE);
   query.bindValue(":DATEREN", DATEREN);
   query.bindValue(":MAIL", MAIL);
   query.bindValue(":NB_PERMIS", NB_PERMIS);
   query.bindValue(":MONTANT_TOTAL", MONTANT_TOTAL);

   return query.exec();
 }
 QSqlQueryModel* reservation::afficher()
 {
     QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM RESERVER");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("MATRICULE"));
 model->setHeaderData(4, Qt::Horizontal,QObject::tr("MAIL"));
 model->setHeaderData(5, Qt::Horizontal,QObject::tr("DATEREN"));
 model->setHeaderData(6, Qt::Horizontal,QObject::tr("NB_PERMIS"));
 model->setHeaderData(7, Qt::Horizontal,QObject::tr("MONTANT_TOTAL"));
     return  model ;
 }
 QSqlQueryModel* reservation::afficher1()
 {
     QSqlQueryModel* model=new QSqlQueryModel();
     model->setQuery("SELECT  CIN ,MAIL FROM RESERVER");

          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));

 model->setHeaderData(1, Qt::Horizontal,QObject::tr("MAIL"));

     return  model ;
 }
 QSqlQueryModel* reservation::afficher2()
 {
     QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("SELECT DATEREN, MONTANT_TOTAL FROM RESERVER GROUP BY DATEREN, MONTANT_TOTAL HAVING COUNT(*) = 5");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("DATEREN"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("MONTANT_TOTAL"));
     return model;
 }
 bool reservation::supprimer(int CIN)     //
 {
    QSqlQuery query;
    //QString CIN=QString::number(CIN);// conversion

   query.prepare("Delete from RESERVER where CIN = :CIN ");
    query.bindValue(":CIN",CIN);
    return query.exec();
 }
 bool reservation::modifier(int CIN, QString NOM, QString PRENOM, QString MATRICULE, QString DATEREN, QString MAIL, QString NB_PERMIS, QString MONTANT_TOTAL)
 {
     QSqlQuery query;
     query.prepare("UPDATE RESERVER SET CIN=:CIN, NOM=:NOM, PRENOM=:PRENOM, MATRICULE=:MATRICULE, NB_PERMIS=:NB_PERMIS, MONTANT_TOTAL=:MONTANT_TOTAL, DATEREN=:DATEREN, MAIL=:MAIL WHERE CIN=:CIN;");
     query.bindValue(":CIN", CIN);
     query.bindValue(":NOM", NOM);
     query.bindValue(":PRENOM", PRENOM);
     query.bindValue(":MATRICULE", MATRICULE);
     query.bindValue(":DATEREN", DATEREN);
     query.bindValue(":MAIL", MAIL); // Add this line to bind the MAIL value
 query.bindValue(":NB_PERMIS", NB_PERMIS);
 query.bindValue(":MONTANT_TOTAL", MONTANT_TOTAL);
     return query.exec();
 }




 QSqlQueryModel* reservation::rechercherCIN(int CIN)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     QSqlQuery query;
     query.prepare("select * from RESERVER where CIN like :CIN");
     query.bindValue(":CIN",CIN);
     query.exec();
     model->setQuery(query);

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("MATRICULE"));
 model->setHeaderData(4, Qt::Horizontal,QObject::tr("DATEREN"));
 model->setHeaderData(5, Qt::Horizontal,QObject::tr("MAIL"));
 model->setHeaderData(6, Qt::Horizontal,QObject::tr("NB_PERMIS"));
 model->setHeaderData(7, Qt::Horizontal,QObject::tr("MONTANT_TOTAL"));
     return model;
 }

 QSqlQueryModel* reservation::rechercher(QString R)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     QSqlQuery query;
     //QString ID=QString::number(CIN);//conversion
     //query.prepare("select * from RESERVER where CIN like '"+ID+"' ||'%'");//like :CIN
     query.prepare("SELECT* FROM RESERVER WHERE CIN like '"+R+"' ||'%' OR NOM like '"+R+"' ||'%' OR PRENOM like '"+R+"' ||'%' OR MATRICULE like '"+R+"' ||'%' OR DATEREN like '"+R+"' ||'%' OR MAIL like '"+R+"' ||'%'   ");
     query.bindValue(":CIN",R);
     query.exec();
     model->setQuery(query);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("MATRICULE"));
 model->setHeaderData(4, Qt::Horizontal,QObject::tr("DATEREN"));
 model->setHeaderData(5, Qt::Horizontal,QObject::tr("MAIL"));
 model->setHeaderData(6, Qt::Horizontal,QObject::tr("NB_PERMIS"));
 model->setHeaderData(7, Qt::Horizontal,QObject::tr("MONTANT_TOTAL"));
     return model;

 }
 QSqlQueryModel* reservation::trier()
 {
     QSqlQuery * q = new  QSqlQuery ();
            QSqlQueryModel * model = new  QSqlQueryModel ();
            q->prepare("SELECT * FROM RESERVER order by CIN"); //ASC pour ascendant, DESC pour descendant
            q->exec();
            model->setQuery(*q);
            return model;
 }
