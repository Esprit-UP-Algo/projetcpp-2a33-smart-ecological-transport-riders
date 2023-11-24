#include "voitures.h"
#include "QSqlQuery"
#include "QtDebug"
#include "QObject"
voitures::voitures()
{
    marque="";
    modele="";
    afb=0;
    plaque_dimmat="";
    kilometrage=0;
    etat="";
    tarifsloca=0;

}
voitures::voitures(QString marque,QString modele,int afb,QString plaque_dimmat,int kilometrage,QString etat, int tarifsloca)
{
    this->marque=marque;
    this->modele=modele;
    this->afb=afb;
    this->plaque_dimmat=plaque_dimmat;
    this->kilometrage=kilometrage;
    this->etat=etat;
    this->tarifsloca=tarifsloca;

}
bool voitures::ajouter()
{

    QSqlQuery query;
    QString afb_string=QString::number(afb);
    QString kilometrage_string=QString::number(kilometrage);

    QString tarifsloca_string=QString::number(tarifsloca);
     query.prepare("INSERT INTO VOITURES VALUES ( :marque,:modele, :afb, :plaque_dimmat, :kilometrage, :etat, :tarifsloca)");
     query.bindValue(":marque",marque);
     query.bindValue(":modele",modele);
     query.bindValue(":afb",afb_string);
     query.bindValue(":plaque_dimmat",plaque_dimmat);
     query.bindValue(":kilometrage",kilometrage_string);
     query.bindValue(":etat",etat);
     query.bindValue(":tarifsloca",tarifsloca_string);

    return query.exec();
}
QSqlQueryModel* voitures::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM VOITURES");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("MARQUE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("MODELE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("AFB"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PLAQUE_DIMMAT"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("KILOMETRAGE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("TARIFSLOCA"));

    return model;
}

bool voitures::supprimer(QString plaque_dimmat)
{
    QSqlQuery query;
    query.prepare("DELETE FROM VOITURES WHERE plaque_dimmat= :plaque_dimmat");
    query.bindValue(":plaque_dimmat",plaque_dimmat);
    return query.exec();
}
bool voitures::modifier(QString marque,QString modele,int afb,QString plaque_dimmat,int kilometrage,QString etat,int tarifsloca)
{
    QSqlQuery query;
    query.prepare("UPDATE VOITURES SET marque= :marque,modele= :modele,afb= :afb,plaque_dimmat= :plaque_dimmat,kilometrage= :kilometrage,etat= :etat,tarifsloca= :tarifsloca WHERE afb= :afb");
    QString afb_string=QString::number(afb);
    QString kilometrage_string=QString::number(kilometrage);
    QString tarifsloca_string=QString::number(tarifsloca);
     query.bindValue(":marque",marque);
     query.bindValue(":modele",modele);
     query.bindValue(":afb",afb_string);
     query.bindValue(":plaque_dimmat",plaque_dimmat);
     query.bindValue(":kilometrage",kilometrage_string);
     query.bindValue(":etat",etat);
     query.bindValue(":tarifsloca",tarifsloca_string);

    return query.exec();
}

QSqlQueryModel* voitures::tri_annee()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("SELECT * FROM VOITURES ORDER BY afb asc ");

    return model;
}
QSqlQueryModel* voitures::tri_tarifs()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("SELECT * FROM VOITURES ORDER BY tarifsloca asc ");

    return model;
}
QSqlQueryModel* voitures::recherche(QString dispo,QString indispo)
    {
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM VOITURES WHERE etat LIKE '%" + dispo + "%'");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("MARQUE"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("MODELE"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("AFB"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("PLAQUE_DIMMAT"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("KILOMETRAGE"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("ETAT"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("TARIFSLOCA"));
        model->setQuery("SELECT * FROM VOITURES WHERE etat LIKE '%" + indispo + "%'");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("MARQUE"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("MODELE"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("AFB"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("PLAQUE_DIMMAT"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("KILOMETRAGE"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("ETAT"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("TARIFSLOCA"));
        return model;
    }
