#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>

class client
{

private:
    QString nom, prenom,adresse ,adresseemail;
    int numcin;
    int numtel;
    int numpermis;
    QDate naissance;
public:
client();
client(QString,QString,int,QDate,QString,QString,int,int);
QString getnom();
QString getprenom();
int getnumpermis();
QDate getnaissance();
QString getadresse();
QString getadresseemail();
int getnumtel();
int getnumcin();
void setnom(QString);
void setprenom(QString);
void setnumpermis(int);
void setnaissance(QDate);
void setadresse(QString);
void setadresseemail(QString);
void setnumtel(int);
void setnumcin(int);



bool ajouter();
QSqlQueryModel * afficher();
bool supprimer(int);
bool modifier();
QSqlQueryModel *rechercher(int);
QSqlQueryModel * afficher(bool sortBydate);


};

#endif // CLIENT_H

