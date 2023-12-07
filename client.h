#ifndef CLIENT_H
#define CLIENT_H


using namespace std;

class client
{
    public:
        client();
        client(int CIN,QString NOM,QString PRENOM,QString MATRICULE,QString DATEREN,QString MAIL,QString NB_PERMIS,QString MONTANT_TOTAL);
           // ~Client();

            int getCIN();
            QString getNOM();
            QString getPRENOM();
            QString getMATRICULE();
            QString getDATEREN();
            QString getMAIL();
            QString getNB_PERMIS();
            QString getMONTANT_TOTAL();
            void setCIN(int);
            void setNOM(QString);
            void setPRENOM(QString);
            void setMATRICULE(QString);
            void setDATEREN(QString);
             void setMAIL(QString);
             void setNB_PERMIS(QString);
             void setMONTANT_TOTAL(QString);
            bool ajouter();
            QSqlQueryModel* afficher();
            QSqlQueryModel* afficher1();
            QSqlQueryModel* afficher2();
            bool supprimer(int);
            bool modifier(int,QString,QString,QString,QString,QString,QString,QString);
            QSqlQueryModel* rechercher(QString);
            QSqlQueryModel* rechercherCIN(int);
              QSqlQueryModel* trier();
            void verif() ;
              void browse();

    private:
              int CIN;
        QString MATRICULE;
        QString PRENOM;
        QString NOM;
        QString DATEREN;
        QString MAIL;
           QString NB_PERMIS;
           QString MONTANT_TOTAL;

};

#endif // CLIENT_H
