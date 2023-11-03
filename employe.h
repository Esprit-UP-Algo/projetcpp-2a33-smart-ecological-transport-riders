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

    employe(int,QString,QString,int,int,QString,QString,int);
 int getmatricule();
 QString getnom();
 QString getprenom();
 int getnumero_de_cin();
 int getdate_de_naissance();
 QString getadresse_email();
 QString getsexe();
 int getnumero_de_telephone();

 void setmatricule(int);
 void setnom(QString);
 void setprenom(QString);
 void setnumero_de_cin(int);
 void setdate_de_naissance(int);
 void setadresse_email(QString);
 void setsexe(QString);
 void setnumero_de_telephone(int);
 bool ajouter();
 QSqlQueryModel* afficher();
 bool supprimer(int);
 bool modifier();
private:
 int matricule;
QString nom;
   QString prenom;
   int numero_de_cin;
   int date_de_naissance;
    QString sexe;
   QString adresse_email;
   int numero_de_telephone;


};

#endif // EMPLOYE_H
