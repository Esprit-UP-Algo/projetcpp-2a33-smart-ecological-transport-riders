#ifndef VOITURES_H
#define VOITURES_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QPdfWriter>
#include <QPainter>
#include <QImage>
#include "arduino.h"
class voitures
{
private:
    QString marque;
    QString modele;
    int afb;
    QString plaque_dimmat;
    int kilometrage;
    QString etat;
    int tarifsloca;

public:
    voitures();
    voitures(QString,QString,int,QString,int,QString,int);

    QString getmarque(){return marque;}
    QString getmodele(){return modele;}
    int getafb(){return afb;}
    QString getplaque_dimmat(){return plaque_dimmat;}
    int getkilometrage(){return kilometrage;}
    QString getetat(){return etat;}
    int gettarifsloca(){return tarifsloca;}

    void setmarque(QString marque){this-> marque=marque;}
    void setmodele(QString modele){this-> modele=modele;}
    void setafb(int afb){this-> afb=afb;}
    void setplaque_dimmat(QString plaque_dimmat){this->plaque_dimmat=plaque_dimmat;}
    void setkilometrage(int kilometrage){this->kilometrage=kilometrage;}
    void setetat(QString etat){this->etat=etat;}
    void settarifsloca(int tarifsloca){this->tarifsloca=tarifsloca;}

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,int,QString,int,QString,int);
    QSqlQueryModel* tri_annee();
    QSqlQueryModel* tri_tarifs();
    QSqlQueryModel* recherche(QString,QString);
    int ardu(QString &a);
    QImage generateQRCode();

};


#endif // VOITURES_H
