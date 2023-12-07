#ifndef contrat_H
#define contrat_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QTableView>

class contrat
{
public:
    contrat();
    contrat(int,QString,QString,QString);
    int getCONTRATID(){return CONTRATID ;}
    QString getDATEDEBUT(){return DATEDEBUT ;}
         QString getDATEFIN(){return DATEFIN ;}
         QString getMONTANT(){return MONTANT ;}


         void setCONTRATID(int);
         void setDATEDEBUT(QString);
         void setDATEFIN(QString);
         void setMONTANT(QString);


         bool ajouter();
         QSqlQueryModel* afficher();
         bool supprimer(int);
         bool modifier(int,QString,QString,QString);

         void recherche(QTableView * affiche_tab, int);

         QSqlQueryModel * trier();
         void telechargerPDF();
          QSqlQueryModel * afficherHistorique();
         //  int getContratIDIfExists(int CONTRATID);
           //bool doesIDExist(QString CONTRATID);
           double getTemperatureForLait(double CONTRATID);
           bool doesCINExist(int CONTRATID);
           double getmontant_b(int CONTRATID);
           double getid(int CONTRATID);


private:
         int CONTRATID ;
         QString DATEFIN,DATEDEBUT,MONTANT;

};

#endif // contrat_H
