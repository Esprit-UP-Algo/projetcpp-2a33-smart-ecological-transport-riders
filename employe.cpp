#include "employe.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include<QString>
#include<QDate>
#include<QSqlError>
employe::employe()
{
     matricule=0;numero_de_cin=0;date_de_naissance=QDate::fromString( "dd/MM/yyyy");numero_de_telephone=0;date=QDate::fromString( "dd/MM/yyyy");
       nom="";prenom="";adresse_email="";sexe="";pass=0;
}
employe::employe(int matricule,QString nom,QString prenom,int numero_de_cin,QDate date_de_naissance,QString adresse_email,QString sexe,int numero_de_telephone,int pass,QDate date){
    this->matricule=matricule;
    this ->nom=nom;
    this ->prenom=prenom;
    this ->numero_de_cin=numero_de_cin;
    this ->date_de_naissance=date_de_naissance;
    this ->adresse_email=adresse_email;
    this ->sexe=sexe;
    this ->numero_de_telephone=numero_de_telephone;
    this->pass=pass;
    this ->date=date;
}
int employe::getmatricule(){return matricule; }
QString employe::getnom(){return nom; }
QString employe::getprenom(){return prenom; }
int employe::getnumero_de_cin(){return numero_de_cin; }
QDate employe::getdate_de_naissance(){return date_de_naissance; }
QString employe::getadresse_email(){return adresse_email; }
QString employe::getsexe(){return sexe; }
int employe::getnumero_de_telephone(){return numero_de_telephone; }
int employe::getpass(){return pass;}
QDate employe::getdate(){return date; }

void employe::setmatricule(int matricule){this ->matricule=matricule;}
void employe::setnom(QString nom){this ->nom=nom;}
void employe::setprenom(QString prenom){this ->prenom=prenom;}
void employe::setnumero_de_cin(int numero_de_cin){ this ->numero_de_cin=numero_de_cin;}
void employe::setdate_de_naissance(QDate date_de_naissance) {this ->date_de_naissance=date_de_naissance;}
void employe::setadresse_email(QString adresse_email){ this ->adresse_email=adresse_email;}
void employe::setsexe(QString sexe){this ->sexe=sexe;}
void employe::setnumero_de_telephone(int numero_de_telephone){this ->numero_de_telephone=numero_de_telephone;}
void employe::setpass(int pass){this->pass=pass;}
void employe::setdate(QDate date) {this ->date=date;}

bool employe::ajouter(){



    QSqlQuery query;
    QString matricule_string= QString::number(matricule);
    query.prepare("INSERT INTO EMPLOYE(MATRICULE,NOM,PRENOM,NUMERO_DE_CIN,DATE_DE_NAISSANCE,ADRESSE_EMAIL,SEXE,NUMERO_DE_TELEPHONE,PASS,DATEEM)"
                  "VALUES (:MATRICULE,:NOM ,:PRENOM,:NUMERO_DE_CIN,:DATE_DE_NAISSANCE,:ADRESSE_EMAIL,:SEXE,:NUMERO_DE_TELEPHONE,:PASS,:DATE)");
   query.bindValue(":MATRICULE",matricule);

     query.bindValue(":NOM", nom);
      query.bindValue(":PRENOM", prenom);
       query.bindValue(":NUMERO_DE_CIN",numero_de_cin);
        query.bindValue(":DATE_DE_NAISSANCE",date_de_naissance);
          query.bindValue(":ADRESSE_EMAIL",adresse_email);
          query.bindValue(":SEXE",sexe);
            query.bindValue(":NUMERO_DE_TELEPHONE",numero_de_telephone);
query.bindValue(":PASS",pass);
query.bindValue(":DATE",date);
                  return query.exec();


}

QSqlQueryModel* employe::afficher(){
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("SELECT* FROM EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("numero_de_cin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_de_naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse_email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("numero_de_telephone"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("pass"));
model->setHeaderData(9, Qt::Horizontal, QObject::tr("date"));

    return model;

}
QSqlQueryModel* employe::afficher1(){
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("SELECT* FROM EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));

    return model;

}
bool employe::supprimer(int matricule)
{

    QSqlQuery query;
    QString matricule_string= QString::number(matricule);
    query.prepare("delete from employe where matricule=:matricule");
    query.bindValue(":matricule",matricule);
    return query.exec();
}



bool employe::modifier(){

      QSqlQuery query;
          QString matricule_string=QString::number(matricule);
          QString numero_de_cin_string=QString::number(numero_de_cin);
          QString numero_de_telephone_string=QString::number(numero_de_telephone);

          QString pass_string=QString::number(pass);

            query.prepare ("UPDATE EMPLOYE SET  NOM=:nom, PRENOM=:prenom, NUMERO_DE_CIN=:numero_de_cin, DATE_DE_NAISSANCE=:date_de_naissance ,ADRESSE_EMAIL=:adresse_email,SEXE=:sexe,NUMERO_DE_TELEPHONE=:numero_de_telephone,PASS=:pass,DATEEM=:date  where MATRICULE=:matricule ");

            query.bindValue(":matricule",matricule_string);

              query.bindValue(":nom", nom);
               query.bindValue(":prenom", prenom);
                query.bindValue(":numero_de_cin",numero_de_cin_string);
                 query.bindValue(":date_de_naissance",date_de_naissance);

                   query.bindValue(":adresse_email",adresse_email);
                      query.bindValue(":sexe",sexe);
                     query.bindValue(":numero_de_telephone",numero_de_telephone_string);
   query.bindValue(":pass",pass);
   query.bindValue(":date",date);


              return query.exec();

  }



QSqlQueryModel* employe::rechercher(QString test, bool searchByNom, bool searchByMatricule)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Construct the query based on the selected criteria
    QString queryString = "SELECT * FROM EMPLOYE WHERE ";
    if (searchByNom) {
        queryString += "NOM LIKE :test ";
    }
    if (searchByMatricule) {
        if (searchByNom) {
            queryString += "OR ";
        }
        queryString += "MATRICULE LIKE :test ";
    }

    query.prepare(queryString);
    query.bindValue(":test", "%" + test + "%");

    if (query.exec()) {
        model->setQuery(query);
        // Set headers and other properties if needed
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
    }

    return model;
}
