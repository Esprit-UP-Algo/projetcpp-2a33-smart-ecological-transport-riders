#include "employe.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include<QString>
#include<QDate>
#include<QSqlError>
employe::employe()
{
     matricule=0;numero_de_cin=0;date_de_naissance=0;numero_de_telephone=0;
       nom="";prenom="";adresse_email="";sexe="";
}
employe::employe(int matricule,QString nom,QString prenom,int numero_de_cin,int date_de_naissance,QString sexe,QString adresse_email,int numero_de_telephone){
    this->matricule=matricule;
    this ->nom=nom;
    this ->prenom=prenom;
    this ->numero_de_cin=numero_de_cin;
    this ->date_de_naissance=date_de_naissance;
    this ->adresse_email=adresse_email;
    this ->sexe=sexe;
    this ->numero_de_telephone=numero_de_telephone;
}
int employe::getmatricule(){return matricule; }
QString employe::getnom(){return nom; }
QString employe::getprenom(){return prenom; }
int employe::getnumero_de_cin(){return numero_de_cin; }
int employe::getdate_de_naissance(){return date_de_naissance; }
QString employe::getadresse_email(){return adresse_email; }
QString employe::getsexe(){return sexe; }
int employe::getnumero_de_telephone(){return numero_de_telephone; }

void employe::setmatricule(int matricule){this ->matricule=matricule;}
void employe::setnom(QString nom){this ->nom=nom;}
void employe::setprenom(QString prenom){this ->prenom=prenom;}
void employe::setnumero_de_cin(int numero_de_cin){ this ->numero_de_cin=numero_de_cin;}
void employe::setdate_de_naissance(int date_de_naissance) {this ->date_de_naissance=date_de_naissance;}
void employe::setadresse_email(QString adresse_email){ this ->adresse_email=adresse_email;}
void employe::setsexe(QString sexe){this ->sexe=sexe;}
void employe::setnumero_de_telephone(int numero_de_telephone){this ->numero_de_telephone=numero_de_telephone;}
bool employe::ajouter(){



    QSqlQuery query;
    QString matricule_string= QString::number(matricule);
    query.prepare("INSERT INTO EMPLOYE(MATRICULE,NOM,PRENOM,NUMERO_DE_CIN,DATE_DE_NAISSANCE,SEXE,ADRESSE_EMAIL,NUMERO_DE_TELEPHONE)"
                  "VALUES (:MATRICULE,:NOM ,:PRENOM,:NUMERO_DE_CIN,:DATE_DE_NAISSANCE,:SEXE,:ADRESSE_EMAIL,:NUMERO_DE_TELEPHONE)");
   query.bindValue(":MATRICULE",matricule);

     query.bindValue(":NOM", nom);
      query.bindValue(":PRENOM", prenom);
       query.bindValue(":NUMERO_DE_CIN",numero_de_cin);
        query.bindValue(":DATE_DE_NAISSANCE",date_de_naissance);
query.bindValue(":SEXE",sexe);
          query.bindValue(":ADRESSE_EMAIL",adresse_email);
            query.bindValue(":NUMERO_DE_TELEPHONE",numero_de_telephone);

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
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("adresse_email"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("numero_de_telephone"));

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
          QString date_de_naissance_string=QString::number(date_de_naissance);

            query.prepare ("UPDATE EMPLOYE SET  NOM=:nom, PRENOM=:prenom, NUMERO_DE_CIN=:numero_de_cin, DATE_DE_NAISSANCE=:date_de_naissance,SEXE=:sexe ,ADRESSE_EMAIL=:adresse_email,NUMERO_DE_TELEPHONE=:numero_de_telephone  where MATRICULE=:matricule ");

            query.bindValue(":matricule",matricule_string);

              query.bindValue(":nom", nom);
               query.bindValue(":prenom", prenom);
                query.bindValue(":numero_de_cin",numero_de_cin_string);
                 query.bindValue(":date_de_naissance",date_de_naissance_string);
         query.bindValue(":sexe",sexe);
                   query.bindValue(":adresse_email",adresse_email);
                     query.bindValue(":numero_de_telephone",numero_de_telephone_string);



              return query.exec();

  }



QSqlQueryModel* employe::rechercher(QString test)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE NUMERO_DE_CIN LIKE :test");
    query.bindValue(":test", "%" + test + "%");
    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("numero_de_cin"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_de_naissance"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("adresse_email"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("numero_de_telephone"));
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
    }
    return model;
}
