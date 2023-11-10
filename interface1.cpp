#include "interface1.h"
#include "ui_interface1.h"
#include "employe.h"
#include <QString>
#include <QIntValidator>
#include <QMessageBox>
#include <QDate>



interface1::interface1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interface1)
{
    ui->setupUi(this);
    ui->le_matricule->setValidator(new QIntValidator(0,999999,this));
    ui->tab_employe->setModel(E.afficher());
    model = new QSqlQueryModel();
       model->setQuery("SELECT * FROM employe");
       ui->tab_employe->setModel(model);

       ui->comboBoxTri->addItem("Par defaut");
       ui->comboBoxTri->addItem("Croissant");
       ui->comboBoxTri->addItem("Decroissant");

       connect(ui->comboBoxTri, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &interface1::on_comboBoxTri_currentIndexChanged);


}

interface1::~interface1()
{
    delete ui;

}

void interface1::on_pushButton_clicked()
{
    int matricule = ui->le_matricule->text().toInt();
    QString nom = ui->le_nom->text();
    QString prenom = ui->le_prenom->text();
    int numero_de_cin = ui->le_numero_de_cin->text().toInt();
   int date_de_naissance = ui->le_date_de_naissance->text().toInt();
    QString sexe = ui->le_sexe->text();
     QString adresse_email = ui->le_adresse_email->text();
     int numero_de_telephone = ui->le_numero_de_telephone->text().toInt();


     employe  E (matricule ,nom ,prenom ,numero_de_cin ,date_de_naissance,sexe ,adresse_email ,numero_de_telephone);
bool test=E.ajouter();

if (test)
{

    QMessageBox::information (nullptr,QObject::tr("ok"),
                              QObject::tr ("ajout effectué\n"
                                           "click cancel to exit."), QMessageBox::Cancel);
    ui->tab_employe->setModel(E.afficher());


}
else
    QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("ajout non effectué.\n"
                                      "click cancel to exit."),QMessageBox::Cancel);
}



void interface1::on_pb_supprimer_clicked()
{
    int matricule=ui->lespp->text().toInt();
    bool test=E.supprimer(matricule);
    if (test)
    {QMessageBox::information(nullptr,QObject::tr("ok"),
                             QObject::tr("suppression  effectuée.\n"
                                         "click cancel to exit."),QMessageBox::Cancel);
        ui->tab_employe->setModel(E.afficher());

    }
    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("suppression non effectuée.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
}


void interface1::on_pushButton_2_clicked()
{
    int matricule = ui->le_matricule_2->text().toInt();
    QString nom = ui->le_nom_2->text();
    QString prenom = ui->le_prenom_2->text();
    int numero_de_cin = ui->le_numero_de_cin_2->text().toInt();
   int date_de_naissance = ui->le_date_de_naissance_2->text().toInt();
    QString sexe = ui->le_sexe_2->text();
     QString adresse_email = ui->le_adresse_email_2->text();
     int numero_de_telephone = ui->le_numero_de_telephone_2->text().toInt();
employe  E (matricule ,nom ,prenom ,numero_de_cin ,date_de_naissance,sexe ,adresse_email ,numero_de_telephone);
    bool test=E.modifier() ;
   if (test)
   {
       QMessageBox::information(nullptr, QObject::tr("ok"),
                                QObject::tr("modifier effectué\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tab_employe->setModel(E.afficher());
   }
   else
       QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                QObject::tr("modifier non effectué\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
}



void interface1::on_lineEdit_rechercher_textChanged(const QString &arg1)
{
    employe E;
                      QString NUMERO_DE_CIN=ui->lineEdit_rechercher->text();
                     ui->tab_employe->setModel(E.rechercher(NUMERO_DE_CIN));
                    ui->tab_employe->clearSelection();

              if (arg1.isEmpty() && ui->lineEdit_rechercher->hasFocus() && !ui->lineEdit_rechercher->hasSelectedText()) {
                  ui->lineEdit_rechercher->setToolTip("Entrez l'NUMERO_DE_CIN à rechercher");
              }
}

void interface1::on_comboBoxTri_currentIndexChanged(int index)
{
    if (index == 0) // Reset
        {
           model->setQuery("SELECT * FROM employe");
        }
        else if (index == 1) // Croissant
        {
            model->setQuery("SELECT * FROM employe ORDER BY MATRICULE ASC");
        }
        else if (index == 2) // Décroissant
           {
               model->setQuery("SELECT * FROM employe ORDER BY MATRICULE DESC");
           }
}


