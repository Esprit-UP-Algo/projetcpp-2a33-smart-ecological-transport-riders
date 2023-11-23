#include "client.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include<QString>
#include<QSqlQueryModel>
#include<QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include "smtp.h"
#include "smtp.cpp"


client::client() {
    nom="";
    prenom="";
    numpermis=0;
    adresse="";
    adresseemail ="";
    numtel=0;
    numcin=0;
}
client::client(QString nom,QString prenom,int numpermis,QDate naissance,QString adresse,QString adresseemail,int numtel,int numcin){

    this->nom=nom;
    this->prenom=prenom;
    this->numpermis=numpermis;
    this->naissance=naissance;
    this->adresse=adresse;
    this->adresseemail=adresseemail;
    this->numtel=numtel;
    this->numcin=numcin;
}
QString client::getnom(){return nom; }
QString client::getprenom(){return prenom; }
int client::getnumpermis(){return numpermis; }
QDate client::getnaissance(){return naissance; }
QString client::getadresse(){return adresse; }
QString client::getadresseemail(){return adresseemail; }
int client::getnumtel(){return numtel; }
int client::getnumcin(){return numcin; }
void client::setnom(QString nom){this ->nom=nom;}
void client::setprenom(QString prenom){this ->prenom=prenom;}
void client::setnumpermis(int numpermis){ this ->numpermis=numpermis;}
void client::setnaissance(QDate naissance) {this ->naissance=naissance;}
void client::setadresse(QString adresse){ this ->adresse=adresse;}
void client::setadresseemail(QString adresseemail){this ->adresseemail=adresseemail;}
void client::setnumtel(int numtel){this ->numtel=numtel;}
void client::setnumcin(int numcin){this ->numcin=numcin;}

bool client::ajouter(){
    QSqlQuery query;
    QString res = QString::number(numcin);
    query.prepare("insert into CLIENTS (NOM,PRENOM, NUMPERMIS, NAISSANCE, ADRESSE, ADRESSEEMAIL, NUMTEL, NUMCIN)"
                  "values (:NOM, :PRENOM, :NUMPERMIS, :NAISSANCE, :ADRESSE, :ADRESSEEMAIL, :NUMTEL, :NUMCIN)");
    query.bindValue(":NOM",nom);
    query.bindValue(":PRENOM",prenom);
    query.bindValue(":NUMPERMIS",numpermis);
    query.bindValue(":NAISSANCE",naissance);
    query.bindValue(":ADRESSE",adresse);
    query.bindValue(":ADRESSEEMAIL",adresseemail);
    query.bindValue(":NUMTEL",numtel);
    query.bindValue(":NUMCIN",numcin);
    return query.exec();
}

QSqlQueryModel * client::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from CLIENTS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("numpermis"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresseemail"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("numtel"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("numcin"));
    return model;
}
bool client::supprimer(int numcin){
    QSqlQuery query;
    QString res=QString::number(numcin);
    query.prepare("Delete FROM CLIENTS where NUMCIN= :NUMCIN");
    query.bindValue(":NUMCIN",numcin);
    return query.exec();
}
bool client::modifier()
{
    QSqlQuery query;
    QString queryString = "UPDATE CLIENTS SET nom = :NOM, prenom = :PRENOM, numpermis = :NUMPERMIS, "
                         "naissance = :NAISSANCE, adresse = :ADRESSE, adresseemail = :ADRESSEEMAIL, "
                         "numtel = :NUMTEL WHERE numcin = :NUMCIN";

    query.prepare(queryString);


    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":NUMPERMIS", numpermis);
    query.bindValue(":NAISSANCE", naissance);
    query.bindValue(":ADRESSE", adresse);
    query.bindValue(":ADRESSEEMAIL", adresseemail);
    query.bindValue(":NUMTEL", numtel);
    query.bindValue(":NUMCIN", numcin);

    if (query.exec())
    {
        // le mis à jour est effectué
        return true;
    }
    else
    {
        // erreur
        return false;
    }
}


QSqlQueryModel * client::rechercher(int nbe) {
    QSqlQueryModel *model = new QSqlQueryModel();
      QSqlQuery query;
      query.prepare("SELECT * FROM CLIENTS WHERE NUMCIN = :NUMCIN");
      query.bindValue(":NUMCIN", nbe); // Ajout de la liaison

      if (query.exec()) {
          model->setQuery(query);
      }

      return model;
}
QSqlQueryModel * client::afficher(bool sortBydate)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (sortBydate) {
        query.prepare("SELECT * FROM CLIENTS ORDER BY NAISSANCE ASC");
    } else {
        query.prepare("SELECT * FROM CLIENTS");
    }

    if (query.exec()) {
        model->setQuery(query);
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUMPERMIS"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NAISSANCE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSEEMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NUMTEL"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("NUMCIN"));

    return model;
}

