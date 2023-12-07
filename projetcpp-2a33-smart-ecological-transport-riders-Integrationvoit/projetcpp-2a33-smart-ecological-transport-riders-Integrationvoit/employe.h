#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class employe
{
public:
    employe();

    employe(int,QString,QString,int,QDate,QString,QString,int,int,QDate);
 int getmatricule();
 QString getnom();
 QString getprenom();
 int getnumero_de_cin();
 QDate getdate_de_naissance();
 QString getadresse_email();
 QString getsexe();
 int getnumero_de_telephone();
int getpass();
QDate getdate();
 void setmatricule(int);
 void setnom(QString);
 void setprenom(QString);
 void setnumero_de_cin(int);
 void setdate_de_naissance(QDate);
 void setadresse_email(QString);
 void setsexe(QString);
 void setnumero_de_telephone(int);
 void setpass(int);
 void setdate(QDate);

 bool ajouter();
 QSqlQueryModel* afficher();
 QSqlQueryModel* afficher1();

 bool supprimer(int);
 bool modifier();
 QSqlQueryModel* rechercher(QString test, bool searchByNom, bool searchByMatricule);
 QString getNomByMatricule(int matricule);


private:
 int matricule;
QString nom;
   QString prenom;
   int numero_de_cin;
   QDate date_de_naissance;
    QString sexe;
   QString adresse_email;
   int numero_de_telephone;
   QString test;
int pass;
QDate date;

};

#endif // EMPLOYE_H
