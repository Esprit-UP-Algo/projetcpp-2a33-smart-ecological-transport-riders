#include "syle.h"
#include "interface1.h"
#include "ui_interface1.h"
#include <QMainWindow>
#include "mainwindow.h"
#include "client.h"
#include "smtp.h"
#include<QSslSocket>
#include<QSqlRecord>
#include "employe.h"
#include <QString>
#include <QIntValidator>
#include <QMessageBox>
#include <QDate>
#include <QCheckBox>
#include <QLineEdit>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include"connexion.h"
#include <QTextDocument>
#include <QFileDialog>
#include <QFileInfo>
#include <excel.h>
#include <QRegExp>
#include <QPainter>
#include <QtCharts>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>// Add this line for QPieSeries
//#include <QPrinter>
#include"voitures.h"
#include<QtCharts/QChart>
#include<QtCharts/QChartView>
#include<QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include<QPieSeries>
#include <QTabWidget>
#include <QtNetwork>

#include "arduino.h"
#include <QTimer>
#include <QMessageBox>

//integration contrat
#include "contrat.h"
#include <vector>
#include <string>
#include <QBuffer>
#include <cstdlib>
#include <ctime>
#include <QSqlError>
#include<QDebug>
#include<QImage>
#include <QPixmap>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include<QTextDocument>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QPrintDialog>
#include <QGraphicsView>
#include <QTabWidget>
#include<QDateEdit>
#include <QSqlQuery>
int i=0;
int j=0;
interface1::interface1(QWidget *parent):
     QMainWindow(parent),
     ui(new Ui::interface1)
{
    ui->setupUi(this);
     applyStyles(ui);
     serial = new QSerialPort(this);
    int ret=myArduino.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< myArduino.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<myArduino.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
        //integration contrat
        QObject::connect(myArduino.getserial(),SIGNAL(readyRead()),this,SLOT(on_tri_2_clicked())); // permet de lancer
        //le slot update_label suite à la reception du signal readyRead (reception des données).
        QObject::connect(myArduino.getserial(),SIGNAL(readyRead()),this,SLOT(on_tri_3_clicked())); // permet de lancer
        //le slot update_label suite à la reception du signal readyRead (reception des données).

   //  QObject::connect(myArduino.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
     timer = new QTimer(this);
     connect(timer, &QTimer::timeout, this, &interface1::loop);
     timer->start(5000);  // Démarrer le temporisa

    ui->le_matricule->setValidator(new QIntValidator(0,999999,this));
    ui->tab_employe->setModel(E.afficher());
    ui->stackedWidget->setCurrentIndex(3);
    model = new QSqlQueryModel();
       model->setQuery("SELECT * FROM employe");
       ui->tab_employe->setModel(model);

       ui->comboBox->setModel(E.afficher1());

       ui->comboBoxTri->addItem("Par defaut");
       ui->comboBoxTri->addItem("Croissant");
       ui->comboBoxTri->addItem("Decroissant");

       connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &interface1::on_comboBox_currentIndexChanged);
      // connect(ui->checkBox, &QCheckBox::stateChanged, this, &interface1::on_lineEdit_rechercher_textChanged);0
       connect(ui->checkBox, &QCheckBox::stateChanged, this, [=](int state){
           on_lineEdit_rechercher_textChanged(QString::number(state));       });

          connect(ui->pushButton_4, &QPushButton::clicked, this, &interface1::on_pushButton_4_clicked);

connect(ui->pushButton_9, &QPushButton::clicked, this, &interface1::on_pushButton_9_clicked);
connect(ui->pushButton_qu, &QPushButton::clicked, this, &interface1::on_pushButton_qu_clicked);



QPieSeries *series = new QPieSeries();

    QSqlQuery query("SELECT DATE_DE_NAISSANCE FROM EMPLOYE");

    // Define age ranges
    int ageRanges[] = {18, 30, 50, 70};
    int numRanges = sizeof(ageRanges) / sizeof(ageRanges[0]);

    // Initialize counts for each age range
    QVector<int> ageRangeCounts(numRanges, 0);

    while (query.next()) {
        QDateTime date_de_naissance = query.value(0).toDateTime();

        // Calculate age
        int age = QDate::currentDate().year() - date_de_naissance.date().year();

        // Categorize into age ranges
        for (int i = 0; i < numRanges; ++i) {
            if (age >= ageRanges[i] && age < ageRanges[i + 1]) {
                ageRangeCounts[i]++;
                break;
            }
        }
    }

    // Add data to the pie series
    for (int i = 0; i < numRanges; ++i) {
        QString label;
        if (i == numRanges - 1) {
            // Last range, no upper limit
            label = QString("%1+").arg(ageRanges[i]);
        } else {
            label = QString("%1-%2").arg(ageRanges[i]).arg(ageRanges[i + 1] - 1);
        }
        series->append(label, ageRangeCounts[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    // Set the theme of the chart
    chart->setTheme(QChart::ChartThemeLight);  // You can choose a different theme

    chart->setTitle("statistique des ages des employes");

    QChartView *chartview = new QChartView(chart);
    chartview->setParent(ui->horizontalFrame);
//oussema
ui->rechercher->setValidator(new QIntValidator(0,999999999,this));
ui->lineEdit_NUMPERMIS->setValidator(new QIntValidator(0,999999999,this));
ui->lineEdit_NUMTEL->setValidator(new QIntValidator(0,999999999,this));
ui->lineEdit_NUMCIN->setValidator(new QIntValidator(0,999999999,this));
ui->lineEdit_2->setValidator(new QIntValidator(0,999999999,this));
ui->lineEdit_numpermis->setValidator(new QIntValidator(0,999999999,this));
ui->lineEdit_numtel->setValidator(new QIntValidator(0,999999999,this));
ui->cinToModifyLineEdit->setValidator(new QIntValidator(0,999999999,this));
ui->tableView->setModel(etmp.afficher());
qputenv("OPENSSL_CONF", "/z/extlib/_openssl_/ssl/openssl.cnf");
//sarah
ui->affichertab->setModel(etm.afficher());
//integration contrat
contrat f;
ui->affiche_tab->setModel(f.afficher());





}

interface1::~interface1()
{
    delete ui;

}

void interface1::on_pushButton_clicked(){
QPixmap PixFalseIcon(":/images/False_icon.png");
QPixmap PixTrueIcon(":/images/True_icon.png");
if (ui->le_matricule->text().contains(QRegExp("[^0-9]") ) || ui->le_matricule->text().isEmpty())
{
    ui->label_matriculeControl->setPixmap(PixFalseIcon);
}

else
{
    ui->label_matriculeControl->setPixmap(PixTrueIcon);
}
 if (ui->le_nom->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->le_nom->text().isEmpty())
    {
        ui->label_nomControl->setPixmap(PixFalseIcon);
        ui->label_nomControl->setToolTip(tr("Le nom de l'eleve doit comport� seulement des lettres alphab�tique !"));
    }
    else
    {
        ui->label_nomControl->setPixmap(PixTrueIcon);
    }

 if (ui->le_prenom->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->le_prenom->text().isEmpty())
    {
        ui->label_prenomControl->setPixmap(PixFalseIcon);
        ui->label_prenomControl->setToolTip(tr("Le nom de l'eleve doit comport� seulement des lettres alphab�tique !"));
    }
    else
    {
        ui->label_prenomControl->setPixmap(PixTrueIcon);
    }
 if (ui->le_numero_de_cin->text().contains(QRegExp("[^0-9]") ) || ui->le_numero_de_cin->text().isEmpty())
 {
     ui->label_cinControl->setPixmap(PixFalseIcon);
 }

 else
 {
     ui->label_cinControl->setPixmap(PixTrueIcon);
 }

 if (ui->le_sexe->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->le_sexe->text().isEmpty())
    {
        ui->label_sexeControl->setPixmap(PixFalseIcon);
        ui->label_sexeControl->setToolTip(tr("Le nom de l'eleve doit comport� seulement des lettres alphab�tique !"));
    }
    else
    {
        ui->label_sexeControl->setPixmap(PixTrueIcon);
    }
 if (ui->le_adresse_email->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->le_adresse_email->text().isEmpty())
    {
        ui->label_adresse_emailControl->setPixmap(PixFalseIcon);
        ui->label_adresse_emailControl->setToolTip(tr("Le nom de l'eleve doit comport� seulement des lettres alphab�tique !"));
    }
    else
    {
        ui->label_adresse_emailControl->setPixmap(PixTrueIcon);
    }
 if (ui->le_numero_de_telephone->text().contains(QRegExp("[^0-9]") ) || ui->le_numero_de_telephone->text().isEmpty())
 {
     ui->label_telephoneControl->setPixmap(PixFalseIcon);
 }

 else
 {
     ui->label_telephoneControl->setPixmap(PixTrueIcon);
 }
 if (ui->lineEditpass->text().contains(QRegExp("[^0-9]") ) || ui->lineEditpass->text().isEmpty())
 {
     ui->label_21->setPixmap(PixFalseIcon);
 }

 else
 {
     ui->label_21->setPixmap(PixTrueIcon);
 }
    int matricule = ui->le_matricule->text().toInt();
    QString nom = ui->le_nom->text();
    QString prenom = ui->le_prenom->text();
    int numero_de_cin = ui->le_numero_de_cin->text().toInt();

   QDate date_de_naissance= ui->le_date_de_naissance->date();

     QString adresse_email = ui->le_adresse_email->text();
     QString sexe = ui->le_sexe->text();
     int numero_de_telephone = ui->le_numero_de_telephone->text().toInt();
int pass = ui->lineEditpass->text().toInt();
QDate date= ui->date->date();

     employe  E (matricule ,nom ,prenom ,numero_de_cin ,date_de_naissance ,adresse_email,sexe ,numero_de_telephone, pass,date);
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
{QPixmap PixFalseIcon(":/images/False_icon.png");
    QPixmap PixTrueIcon(":/images/True_icon.png");

    if (ui->lespp->text().contains(QRegExp("[^0-9]") ) || ui->lespp->text().isEmpty())
    {
        ui->label_suppControl->setPixmap(PixFalseIcon);

    }
    else
    {
        ui->label_suppControl->setPixmap(PixTrueIcon);
    }

    int matricule=ui->lespp->text().toInt();
    bool matriculeExists = false;

       // Implement your logic to check if matricule exists (replace the following with your actual logic)
       // For example, you might iterate through your data or use a database query
       // matriculeExists = ...;

    if (!matriculeExists)
       {
           QMessageBox::warning(nullptr, QObject::tr("Matricule Not Found"),
                                QObject::tr("Matricule does not exist.\n"
                                            "Please enter a valid matricule."), QMessageBox::Ok);
            // Exit the function if matricule does not exist
       }
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
{ QPixmap PixFalseIcon(":/images/False_icon.png");
    QPixmap PixTrueIcon(":/images/True_icon.png");
    if (ui->le_matricule_2->text().contains(QRegExp("[^0-9]") ) || ui->le_matricule_2->text().isEmpty())
    {
        ui->label_matriculeControl2->setPixmap(PixFalseIcon);
    }

    else
    {
        ui->label_matriculeControl2->setPixmap(PixTrueIcon);
    }
     if (ui->le_nom_2->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->le_nom_2->text().isEmpty())
        {
            ui->label_nomControl2->setPixmap(PixFalseIcon);
            ui->label_nomControl2->setToolTip(tr("Le nom de l'eleve doit comport� seulement des lettres alphab�tique !"));
        }
        else
        {
            ui->label_nomControl2->setPixmap(PixTrueIcon);
        }

     if (ui->le_prenom_2->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->le_prenom_2->text().isEmpty())
        {
            ui->label_prenomControl2->setPixmap(PixFalseIcon);
            ui->label_prenomControl2->setToolTip(tr("Le nom de l'eleve doit comport� seulement des lettres alphab�tique !"));
        }
        else
        {
            ui->label_prenomControl2->setPixmap(PixTrueIcon);
        }
     if (ui->le_numero_de_cin_2->text().contains(QRegExp("[^0-9]") ) || ui->le_numero_de_cin_2->text().isEmpty())
     {
         ui->label_cinControl2->setPixmap(PixFalseIcon);
     }

     else
     {
         ui->label_cinControl2->setPixmap(PixTrueIcon);
     }
     if (ui->le_date_de_naissance_2->text().contains(QRegExp("[^0-9-]") ) || ui->le_date_de_naissance_2->text().isEmpty())
        {
            ui->label_dateControl2->setPixmap(PixFalseIcon);
        }
        else
        {
            ui->label_dateControl2->setPixmap(PixTrueIcon);
        }
     if (ui->le_sexe_2->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->le_sexe_2->text().isEmpty())
        {
            ui->label_sexeControl2->setPixmap(PixFalseIcon);
            ui->label_sexeControl2->setToolTip(tr("Le nom de l'eleve doit comport� seulement des lettres alphab�tique !"));
        }
        else
        {
            ui->label_sexeControl2->setPixmap(PixTrueIcon);
        }
     if (ui->le_adresse_email_2->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->le_adresse_email_2->text().isEmpty())
        {
            ui->label_adresse_emailControl2->setPixmap(PixFalseIcon);
            ui->label_adresse_emailControl2->setToolTip(tr("Le nom de l'eleve doit comport� seulement des lettres alphab�tique !"));
        }
        else
        {
            ui->label_adresse_emailControl2->setPixmap(PixTrueIcon);
        }
     if (ui->le_numero_de_telephone_2->text().contains(QRegExp("[^0-9]") ) || ui->le_numero_de_telephone_2->text().isEmpty())
     {
         ui->label_telephoneControl2->setPixmap(PixFalseIcon);
     }

     else
     {
         ui->label_telephoneControl2->setPixmap(PixTrueIcon);
     }
     if (ui->label_20pass2->text().contains(QRegExp("[^0-9]") ) || ui->label_20pass2->text().isEmpty())
     {
         ui->label_202->setPixmap(PixFalseIcon);
     }

     else
     {
         ui->label_202->setPixmap(PixTrueIcon);
     }
    int matricule = ui->le_matricule_2->text().toInt();
    QString nom = ui->le_nom_2->text();
    QString prenom = ui->le_prenom_2->text();
    int numero_de_cin = ui->le_numero_de_cin_2->text().toInt();

   QDate date_de_naissance= ui->le_date_de_naissance->date();

     QString adresse_email = ui->le_adresse_email_2->text();
      QString sexe = ui->le_sexe_2->text();
     int numero_de_telephone = ui->le_numero_de_telephone_2->text().toInt();
 int pass = ui->lineEditpass2->text().toInt();
 QDate date= ui->dateEdit->date();

employe  E (matricule ,nom ,prenom ,numero_de_cin ,date_de_naissance ,adresse_email,sexe ,numero_de_telephone,pass,date);
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
    // Get the selected search criteria based on checkboxes
    bool searchByNom = ui->checkBox->isChecked();
    bool searchByMatricule = ui->checkBox_2->isChecked();

    // Call the rechercher function with the selected criteria
    ui->tab_employe->setModel(E.rechercher(arg1, searchByNom, searchByMatricule));

    // Clear selection
    ui->tab_employe->clearSelection();
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




void interface1::on_comboBox_currentIndexChanged(int index)
{if (index >= 0 && index < ui->comboBox->count())
    {
        QString selectedMatricule = ui->comboBox->itemText(index);
        ui->le_matricule_2->setText(selectedMatricule);
        ui->le_matricule_2->setReadOnly(false);

    }
    QString matricule=ui->comboBox->currentText();
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE MATRICULE=:matricule");
    query.bindValue(":matricule", matricule);
    if (query.exec() && query.next()) {

    ui->le_matricule_2->setText(query.value(0).toString());
   ui->le_nom_2->setText(query.value(1).toString());
    ui->le_prenom_2->setText(query.value(2).toString());
    ui->le_numero_de_cin_2->setText(query.value(3).toString());
   // ui->le_date_de_naissance_2->setText(query.value(4).toString());
    QDate date = query.value(4).toDate();
    QString formattedDate = date.toString("yyyy-MM-dd");  // Adjust the format as needed

    ui->le_adresse_email_2->setText(query.value(5).toString());
    ui->le_sexe_2->setText(query.value(6).toString());
    ui->le_numero_de_telephone_2->setText(query.value(7).toString());
     ui->lineEditpass2->setText(query.value(8).toString());

        // Adjust the format as need
    } else {
                qDebug() << "Error retrieving data for matricule: " << matricule;
            }
}

void interface1::on_checkBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
            ui->lineEdit_rechercher->setPlaceholderText("Enter nom...");
        }
}

void interface1::on_checkBox_2_stateChanged(int state)
{
    if (state == Qt::Checked) {
           ui->lineEdit_rechercher->setPlaceholderText("Enter matricule...");
       }
}



void interface1::on_pushButton_3_clicked()
{
    QString strStream;
                     QTextStream out(&strStream);

                     const int rowCount = ui->tab_employe->model()->rowCount();
                     const int columnCount = ui->tab_employe->model()->columnCount();

                     out <<  "<html>\n"
                         "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg("strTitle")
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"

                        //     "<align='right'> " << datefich << "</align>"
                         "<center> <H1>Liste des employes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                     // headers
                     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->tab_employe->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->tab_employe->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tab_employe->isColumnHidden(column)) {
                                 QString data = ui->tab_employe->model()->data(ui->tab_employe->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table> </center>\n"
                         "</body>\n"
                         "</html>\n";

               QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                 if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

             // QPrinter printer (QPrinter::PrinterResolution);
               //printer.setOutputFormat(QPrinter::PdfFormat);
              // printer.setPaperSize(QPrinter::A4);
               //printer.setOutputFileName(fileName);

                QTextDocument doc;
                 doc.setHtml(strStream);
               //  doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                // doc.print(&printer);
}



void interface1::on_pushButton_5_clicked()
{
    QString matricule = ui -> lineEdit_username->text();
    QString Password= ui-> lineEdit_password -> text();

    QSqlQuery query;

        query.prepare("SELECT * FROM EMPLOYE WHERE MATRICULE = :matricule AND PASS = :password");
        query.bindValue(":matricule", matricule);
        query.bindValue(":password", Password);
 //ui->stackedWidget->setCurrentIndex(4);
        if (query.exec() && query.next()) {
            QMessageBox::information(this, "CONNECTED", "Connecté");

             ui->stackedWidget->setCurrentIndex(4);


        } else {
            QMessageBox::warning(this, "INVALID", "Nom d'utilisateur ou mot de passe incorrect.");
        }
    }
void interface1::on_pushButton_6_clicked()
{
    QMessageBox::StandardButton reply;

    reply= QMessageBox::question(this,"close?","are you sure to close the app?");
    if(reply==QMessageBox::Yes)
    {
QApplication::quit();
    }
}

void interface1::on_pushButton_7_clicked()
{
    QPixmap pixmap(ui->tab_employe->size());
    ui->tab_employe->render(&pixmap, QPoint(), QRegion());
    pixmap.save("tab1.png");
}

void interface1::on_pushButton_8_clicked()
{

        QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                                   tr("Fichiers d'extension Excel (*.xls)"));
                   if (fileName.isEmpty())
                       return;

                    EXCEL obj(fileName, "invite", ui->tab_employe);

                   // you can change the column order and
                   // choose which colum to export
                   obj.addField(0, "matricule", "number");
                   obj.addField(1, "nom", "char(20)");
                   obj.addField(2, "prenom", "char(20)");
                   obj.addField(3, "numero_de_cin", "number");
                   obj.addField(4, "date_de_naissance", "date");
     obj.addField(5, "adresse_email", "char(20)");
      obj.addField(6, "sexe", "char(20)");
       obj.addField(7, "numero_de_telephone", "number");
         obj.addField(8, "pass", "number");
         obj.addField(9, "date", "date");

                   int retVal = obj.export2Excel();

                   if( retVal > 0)
                   {
                       QMessageBox::information(this, tr("DONE"),
                                                QString(tr("%1 export successful")).arg(retVal)
                                                );
                   }
    }

void interface1::on_pushButton_4_clicked()
{

    ui->stackedWidget->setCurrentIndex(0);

}



/*oussema*/








void interface1::on_pushButton_10_clicked()
{
    QString nom=ui->lineEdit_NOM->text();
    QString prenom=ui->lineEdit_PRENOM->text();
    int numpermis=ui->lineEdit_NUMPERMIS->text().toInt();
     QDate naissance=ui->lineEdit_NAISSANCE->date();
    QString adresse=ui->lineEdit_ADRESSE->text();
    QString adresseemail=ui->lineEdit_ADRESSEEMAIL->text();
    int numtel=ui->lineEdit_NUMTEL->text().toInt();
    int numcin=ui->lineEdit_NUMCIN->text().toInt();
    if (!isValidEmail(adresseemail)) {
               QMessageBox::critical(nullptr, QObject::tr("Invalid Input"),
                                     QObject::tr("Please enter a valid email address."),
                                     QMessageBox::Cancel);
               return;
           }
    client x(nom,prenom,numpermis,naissance,adresse,adresseemail,numtel,numcin);
    bool test=x.ajouter();
     if(test){
        ui->tableView->setModel(etmp.afficher());
        QPieSeries *series = new QPieSeries();

            QSqlQuery query("SELECT NAISSANCE FROM CLIENTS");

            // Define age ranges
            int ageRanges[] = {18, 30, 50, 70};
            int numRanges = sizeof(ageRanges) / sizeof(ageRanges[0]);

            // Initialize counts for each age range
            QVector<int> ageRangeCounts(numRanges, 0);

            while (query.next()) {
                QDateTime naissance = query.value(0).toDateTime();

                // Calculate age
                int age = QDate::currentDate().year() - naissance.date().year();

                // Categorize into age ranges
                for (int i = 0; i < numRanges; ++i) {
                    if (age >= ageRanges[i] && age < ageRanges[i + 1]) {
                        ageRangeCounts[i]++;
                        break;
                    }
                }
            }

            // Add data to the pie series
            for (int i = 0; i < numRanges; ++i) {
                QString label;
                if (i == numRanges - 1) {
                    // Last range, no upper limit
                    label = QString("%1+").arg(ageRanges[i]);
                } else {
                    label = QString("%1-%2").arg(ageRanges[i]).arg(ageRanges[i + 1] - 1);
                }
                series->append(label, ageRangeCounts[i]);
            }

            QChart *chart = new QChart();
            chart->addSeries(series);
            // Set the theme of the chart
            chart->setTheme(QChart::ChartThemeLight);  // You can choose a different theme

            chart->setTitle("statistique des ages des clients");

            QChartView *chartview = new QChartView(chart);
            chartview->setParent(ui->frame);


         QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué\n"
                            "click cancel to exit"),QMessageBox::Cancel);

    }
    else
    {QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué\n"
                                          "click cancel to exit"),QMessageBox::Cancel);
}
}

void interface1::on_pushButton_14_clicked()
{
    int numcin=ui->lineEdit_2->text().toInt();
    bool test=etmp.supprimer(numcin);
    if(test){
        ui->tableView->setModel(etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("suppression effectué\n"
                            "click cancel to exit"),QMessageBox::Cancel);
    }
    else
    {QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("suppression non effectué\n"
                                          "click cancel to exit"),QMessageBox::Cancel);
}
}

void interface1::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void interface1::on_pushButton_qu_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}




void interface1::on_pushButton_15_clicked()
{
    QString newNom =ui->lineEdit_nom->text();
        QString newPrenom =ui->lineEdit_prenom->text();
        int newNumPermis = ui->lineEdit_numpermis->text().toInt();
        QDate newNaissance = ui->lineEdit_naissance->date();
        QString newAdresse = ui->lineEdit_adresse->text();
        QString newAdresseEmail = ui->lineEdit_email->text();
        int newNumTel = ui->lineEdit_numtel->text().toInt();
        int cinToModify = ui->cinToModifyLineEdit->text().toInt();

        client clientToModify(newNom, newPrenom, newNumPermis, newNaissance, newAdresse, newAdresseEmail, newNumTel, cinToModify);


        bool test = clientToModify.modifier();

        if (test)
        {
            ui->tableView->setModel(etmp.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("modification effectué\n"
                                "click cancel to exit"),QMessageBox::Cancel);
        }
        else
        {QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("modification non effectué.vérifier que le cin est correcte"
                                              "click cancel to exit"),QMessageBox::Cancel);
    }
}

void interface1::on_pushButton_11_clicked()
{
    client x;
    int nbe = ui->rechercher->text().toInt();


       QSqlQueryModel *resultModel = x.rechercher(nbe);


       if (resultModel && resultModel->rowCount() > 0) {

           ui->tableView_2->setModel(resultModel);
       } else {

           QMessageBox::critical(this, "Erreur", "Aucune donnée trouvée pour cet numcin.", QMessageBox::Cancel);
       }
}


void interface1::on_pushButton_12_clicked()
{
    ui->tableView->setModel(etmp.afficher(true));

}

void interface1::on_pushButton_13_clicked()
{
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", QString(), "*.pdf");
        if (!fileName.isEmpty()) {
            if (QFileInfo(fileName).suffix().isEmpty()) {
                fileName.append(".pdf");
            }

            QPdfWriter writer(fileName);
            QPainter painter(&writer);

            int rowCount = ui->tableView->model()->rowCount();
            int columnCount = ui->tableView->model()->columnCount();

            // Décalage vers le bas
            int verticalOffset = 200;

            QString strStream;
            QTextStream out(&strStream);

            out <<  "<html>\n"
                "<head>\n"
                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                <<  QString("<title>%1</title>\n").arg("TITLE")
                <<  "</head>\n"
                "<body bgcolor=#ffffff link=#5000A0>\n"
                // Décalage du titre
                "<h1 style='color:#341763; font-family:Montserrat SemiBold; font-size:25px; position:absolute; top:" + QString::number(verticalOffset) + "px; left:50%; transform: translateX(-50%);'>Liste des clients</h1>\n"

                "<table border=1 cellspacing=0 cellpadding=2 width='100%'>\n";

            // headers
            out << "<thead><tr bgcolor=#f0f0f0>";
            for (int column = 0; column < columnCount; column++)
                if (!ui->tableView->isColumnHidden(column))
                    out << QString("<th width='%1%'>%2</th>").arg(100/columnCount).arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

            // data table
            for (int row = 0; row < rowCount; row++) {
                out << "<tr>";
                for (int column = 0; column < columnCount; column++) {
                    if (!ui->tableView->isColumnHidden(column)) {
                        QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                        out << QString("<td bkcolor=0 width='%1%'>%2</td>").arg(100/columnCount).arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                    }
                }
                out << "</tr>\n";
            }
            out <<  "</table>\n"
                "</body>\n"
                "</html>\n";

            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);

            // Scale the painter
            double scale = 15.0;  // Adjust the scale factor here
            painter.scale(scale, scale);

            document->drawContents(&painter);

            delete document;
        }


    }

}

void interface1::on_pushButton_16_clicked()
{QPixmap pixmap(ui->horizontalFrame->size());
    ui->horizontalFrame->render(&pixmap, QPoint(), QRegion());
    pixmap.save("tab2.png");


}

void interface1::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}

void interface1::on_pushButton_18_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void interface1::on_calendarWidget_selectionChanged()
{
    static QDate firstDate;

        if (firstDate.isNull()) {
            // C'est la première date sélectionnée
            firstDate = ui->calendarWidget->selectedDate();
        } else {
            // C'est la deuxième date sélectionnée
            QDate secondDate = ui->calendarWidget->selectedDate();

            // Calculez la différence entre les deux dates
            int daysDifference = firstDate.daysTo(secondDate);

            // Vérifiez si la différence est inférieure ou égale à 21
            if (daysDifference <= 21) {
                QMessageBox::information(this, "Congé", "Congé disponible");
            } else {
                QMessageBox::information(this, "Congé", "Congé pas possible");
            }

            // Réinitialisez firstDate pour la prochaine paire de sélections
            firstDate = QDate();

            // Désactivez le QCalendarWidget
            ui->calendarWidget->setEnabled(false);
        }
}
void interface1::sendMail()
{
    qDebug() << "Sending email...";

        // Get the user input from the line edits
        QString clientEmail = ui->lineEdit_ADRESSEEMAIL->text();
        QString message = ui->lineEdit_3->text();


        // Validate the email address
        if (!isValidEmail(clientEmail)) {
            qDebug() << "Invalid email address";
            QMessageBox::critical(this, "Error", "Invalid email address");
            return;
        }

        // Create an instance of the smtp class with your email credentials
        smtpClient = new smtp("chams.nasr@esprit.tn", "221JMT8002", "smtp.esprit.tn", 578);

        qDebug() << "Email content:";
        qDebug() << "To: " << clientEmail;
        qDebug() << "Subject: Subject";
        qDebug() << "Body: " << message;

        // Send the email
        smtpClient->sendMail("chams.nasr@esprit.tn", clientEmail, "Subject", message);

        // Check for successful email sending
        if (smtpClient->getSocketState() == QAbstractSocket::ConnectedState) {
            qDebug() << "le message est envoyé!";

            // Additional debugging information
            qDebug() << "Socket state:" << smtpClient->getSocketState();
            qDebug() << "Socket error string:" << smtpClient->getSocketErrorString();
            qDebug() << "SMTP server response:" << smtpClient->getServerResponse();

            QMessageBox::information(this, "Email Sent", "le message est envoyé!");
        } else {
            qDebug() << "Error sending email:" << smtpClient->getSocketErrorString();

            // Additional debugging information
            qDebug() << "Socket state:" << smtpClient->getSocketState();
            qDebug() << "Socket error string:" << smtpClient->getSocketErrorString();
            qDebug() << "SMTP server response:" << smtpClient->getServerResponse();

            QMessageBox::warning(this, "Error", "Error sending email. Check the console for details.");
        }

        // Cleanup
        delete smtpClient;
}

void interface1::on_pushButton_19_clicked()
{
    QString message = ui->lineEdit_3->text();
            int numcin = ui->lineEditcl->text().toInt();

            // Retrieve the client's email address using the numcin
            client x;
            QSqlQueryModel *resultModel = x.rechercher(numcin);

            if (resultModel && resultModel->rowCount() > 0) {
                QString clientEmail = resultModel->record(0).value("ADRESSEEMAIL").toString();

                // Validate the email address
                if (isValidEmail(clientEmail)) {
                    // Send the email
                    smtp *smtpClient = new smtp("chams.nasr@esprit.tn", "221JMT8002", "smtp.esprit.tn", 578);
                    smtpClient->sendMail("chams.nasr@esprit.tn", clientEmail, "Subject", message);

                    QMessageBox::information(this, "Email Sent", "The email has been sent successfully!");

                    // Cleanup
                    delete smtpClient;
                } else {
                    QMessageBox::critical(this, "Error", "Invalid email address");
                }
            } else {
                QMessageBox::warning(this, "Error", "Client not found or email address not available.");
            }
}
bool interface1::isValidEmail(const QString &email)
{
    // Simple email validation using a regular expression
        QRegExp emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
        return emailRegex.exactMatch(email);
}

/*void interface1::readDataFromArduino()
{
    QByteArray data = myArduino.read_from_arduino();

}*/
/*void interface1::readDataFromArduino()
{
    QByteArray data = myArduino.read_from_arduino();

    // Convertir les données reçues en int (matricule)
    int matricule = data.toInt();

    // Exécuter la requête SQL pour obtenir le nom correspondant au matricule
    QSqlQuery query;
    query.prepare("SELECT NOM FROM EMPLOYE WHERE MATRICULE = :matricule");
    query.bindValue(":matricule", matricule);

    if (query.exec() && query.next()) {
        // La requête a réussi, et nous avons une correspondance
        QString nom = query.value(1).toString();

        // Envoyer le nom à l'Arduino
        QByteArray response = nom.toUtf8();
        int writeResult = myArduino.write_to_arduino(response);

        if (writeResult == 1) {
            qDebug() << "Nom envoyé à l'Arduino avec succès : " << nom;
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                              QObject::tr("Nom envoyé à l'Arduino avec succès"
                                                          "click cancel to exit"),QMessageBox::Cancel);
        } else {
            qDebug() << "Échec de l'envoi du nom à l'Arduino.";
        }
    } else {
        // Aucune correspondance trouvée, envoyer une réponse vide à l'Arduino
        QByteArray emptyResponse;
        int writeResult = myArduino.write_to_arduino(emptyResponse);

        if (writeResult == 1) {
            qDebug() << "Aucune correspondance trouvée, réponse vide envoyée à l'Arduino.";
        } else {
            qDebug() << "Échec de l'envoi de la réponse vide à l'Arduino.";
        }
    }
}*/


/*void interface1::on_pushButton_arduino_clicked()
{
    QByteArray data = myArduino.read_from_arduino();
    // Convertir les données reçues en int (matricule)
    int matricule = data.toInt();

    // Exécuter la requête SQL pour obtenir le nom correspondant au matricule
    QSqlQuery query;
    query.prepare("SELECT NOM FROM EMPLOYE WHERE MATRICULE = :matricule");
    query.bindValue(":matricule", matricule);

    if (query.exec() && query.next()) {
        // La requête a réussi, et nous avons une correspondance
        QString nom = query.value(1).toString();

        // Envoyer le nom à l'Arduino
        QByteArray response = nom.toUtf8();
        int writeResult = myArduino.write_to_arduino(response);

        if (writeResult == 1) {
            qDebug() << "Nom envoyé à l'Arduino avec succès : " << nom;
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                              QObject::tr("Nom envoyé à l'Arduino avec succès"
                                                          "click cancel to exit"),QMessageBox::Cancel);
        } else {
            qDebug() << "Échec de l'envoi du nom à l'Arduino.";
        }
    } else {
        // Aucune correspondance trouvée, envoyer une réponse vide à l'Arduino
        QByteArray emptyResponse;
        int writeResult = myArduino.write_to_arduino(emptyResponse);

        if (writeResult == 1) {
            qDebug() << "Aucune correspondance trouvée, réponse vide envoyée à l'Arduino.";
        } else {
            qDebug() << "Échec de l'envoi de la réponse vide à l'Arduino.";
        }
    }

}*/
void interface1::loop() {
    QByteArray data = myArduino.read_from_arduino();

    // Nettoyer les caractères spéciaux "\r\n" de la chaîne
    data = data.trimmed();

    // Convertir les données nettoyées en int (matricule)
    bool conversionOk;
    int UID = data.toInt(&conversionOk);

    if (conversionOk) {
        qDebug() << "Matricule Arduino converti avec succès : " << UID;

        // Exécuter la requête SQL pour vérifier si le matricule existe dans la table EMPLOYE
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT NOM FROM EMPLOYE WHERE MATRICULE = :UID");
        checkQuery.bindValue(":UID", UID);

        if (checkQuery.exec() && checkQuery.next()) {
            // La correspondance a été trouvée, récupérer le nom correspondant
            QString nom = checkQuery.value(0).toString();

            // Envoyer le nom à l'Arduino
            QByteArray response = nom.toUtf8();
            int writeResult = myArduino.write_to_arduino(response);

            if (writeResult == 1) {
                qDebug() << "Matricule trouvé, nom envoyé à l'Arduino : " << nom;

                QMessageBox::information(nullptr, QObject::tr("OK"),
                                         QObject::tr("Matricule trouvé, nom envoyé à l'Arduino."
                                                     "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            } else {
                qDebug() << "Échec de l'envoi du nom à l'Arduino.";
            }
        } else {
            // Aucune correspondance trouvée, envoyer une réponse vide à l'Arduino
            QByteArray emptyResponse = "0";
            int writeResult = myArduino.write_to_arduino(emptyResponse);

            if (writeResult == 1) {
                qDebug() << "Aucune correspondance trouvée, réponse vide envoyée à l'Arduino.";
            } else {
                qDebug() << "Échec de l'envoi de la réponse vide à l'Arduino.";
            }
        }
    } else {
        // La conversion en int a échoué
        qDebug() << "Échec de la conversion du matricule Arduino en entier.";
        // Traitez ce cas en conséquence (par exemple, affichez un message d'erreur)
    }
}

void interface1::on_pushButton_21_clicked()
{
       ui->stackedWidget->setCurrentIndex(1);
       ui->pushButton_22->show();
}
//sarah

void interface1::on_ajouter_vo_clicked()
{
    QString marque=ui->le_marque->text();
    QString modele=ui->le_modele->text();
    int afb=ui->le_afb->text().toInt();
    QString plaque_dimmat=ui->le_plaque_dimmat->text();
    int kilometrage=ui->le_kilometrage->text().toInt();
    QString etat=ui->le_etat->text();
    int tarifsloca=ui->le_tarifs->text().toInt();




    voitures v(marque,modele,afb,plaque_dimmat,kilometrage,etat,tarifsloca);
    bool test=v.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ajouter"),
                    QObject::tr("ajouter successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("ajouter"),
                    QObject::tr("ajouter failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
      ui->affichertab->setModel(etmp.afficher());
}

void interface1::on_supp_sara_clicked()
{
    voitures v;
    QString plaque_dimmat=ui->lineEdit_8->text();
    bool test=etm.supprimer(plaque_dimmat);
             if(test)
             {
               QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                             QObject::tr(" supprimé.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);

             }
             else
             {QMessageBox::critical(nullptr, QObject::tr("supprimer"),
                             QObject::tr("Erreur !.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);}
             ui->affichertab->setModel(etm.afficher());

}

void interface1::on_modifier_2_clicked()
{
    QString marque=ui->le_marque->text();
      QString modele=ui->le_modele->text();
      int afb=ui->le_afb->text().toInt();
      QString plaque_dimmat=ui->le_plaque_dimmat->text();
      int kilometrage=ui->le_kilometrage->text().toInt();
      QString etat=ui->le_etat->text();
      int tarifsloca=ui->le_tarifs->text().toInt();




      voitures v (marque,modele,afb,plaque_dimmat,kilometrage,etat,tarifsloca);
      bool test=v.modifier(marque,modele,afb,plaque_dimmat,kilometrage,etat,tarifsloca);
      if(test)
      {
          QMessageBox::information(nullptr, QObject::tr("modifier"),
                      QObject::tr("modifier successful.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

      }
      else
         { QMessageBox::critical(nullptr, QObject::tr("modifier"),
                      QObject::tr("modifier failed.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);}
        ui->affichertab->setModel(etm.afficher());
}

void interface1::on_pushButton_trianne_clicked()
{

   ui->tab_tri->setModel(etm.tri_annee());
}



void interface1::on_chercher_clicked()
{
    ui->affichertab->setModel(etm.recherche(ui->cherche->text(),ui->cherche->text()));
}





void interface1::on_stat_clicked()
{


}

void interface1::on_chercher_sara_clicked()
{
    ui->affichertab->setModel(etm.recherche(ui->cherche->text(),ui->cherche->text()));
}

void interface1::on_stat_sarah_clicked()
{
    QSqlQueryModel*model=new QSqlQueryModel();
        model->setQuery("SELECT etat FROM VOITURES ");

    int countdispo = 0;
    int countindispo = 0;

    for (int i = 0; i < model->rowCount(); i++) {
        QString status_a = model->record(i).value("etat").toString();

        if (status_a == "dispo") {
            countdispo++;
        } else if (status_a == "indispo") {
            countindispo++;
        }
}
    int total = countdispo + countindispo ;

       QPieSeries *series = new QPieSeries();
       series->append("dispo", countdispo);
       series->append("indispo", countindispo);

       if (countdispo != 0) {
           QPieSlice *slice = series->slices().at(0);
           slice->setLabel("dispo" + QString("%1%").arg(100*slice->percentage(),3,'f',1));
           slice->setLabelVisible();
           slice->setPen(QPen(Qt::cyan));
       }

       if (countindispo != 0) {
           QPieSlice *slice1 = series->slices().at(1);
           slice1->setLabel("indispo" + QString("%1%").arg(100*slice1->percentage(),3,'f',1));
           slice1->setLabelVisible();
           slice1->setBrush(QColor(Qt::red));
       }

       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Total " + QString::number(total));

       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->resize(1000, 500);

       chart->legend()->hide();
       chartView->show();
}

void interface1::on_tarifs_clicked()
{
    ui->affichertab->setModel(etm.tri_tarifs());
}

void interface1::on_pushButton_trianne_2_clicked()
{

    ui->affichertab->setModel(etm.tri_annee());
}

void interface1::on_pdf_sara_clicked()
{
    QPdfWriter pdf("C:/projet_pdf/pdf");
    int i = 4000;
    QPainter painter(&pdf);
    QString strStream;

    QTextStream out(&strStream);
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000,1400,"Liste Des Voitures");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 7));
    painter.setPen(Qt::darkCyan);
    painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3000,9400,500);
    painter.setPen(Qt::black);
    painter.drawText(300,3300," marque");
    painter.drawText(1300,3300,"modele");
    painter.drawText(2300,3300,"afb");
    painter.drawText(3300,3300,"plaque_dimmat");
    painter.drawText(4300,3300,"kilometrage");
    painter.drawText(5300,3300,"etat");
    painter.drawText(6300,3300,"tarifsloca");
    painter.setPen(Qt::darkCyan);
    painter.drawRect(100,3000,9400,9000);
    painter.setPen(Qt::black);
    QSqlQuery query;
    query.prepare("select * from VOITURES");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1300,i,query.value(1).toString());
        painter.drawText(2300,i,query.value(2).toString());
        painter.drawText(3300,i,query.value(3).toString());
        painter.drawText(4300,i,query.value(4).toString());
        painter.drawText(5300,i,query.value(5).toString());
        painter.drawText(6300,i,query.value(6).toString());
        i +=350;
    }
        QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
        QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);


}


void interface1::on_kilometrage_clicked()
{
    voitures v;    //ardu
    int kilometrage;

    QString plaque_dimmat=ui->lineEditPlaqueImmatriculation->text();
    kilometrage=v.ardu(plaque_dimmat);
     QString stringValue = QString::number(kilometrage);
     ui->aff->setText("kilometrage : " + stringValue);
     if(kilometrage<=50000)
     {

         myArduino.write_to_arduino("1");
     }
     else
     {

         myArduino.write_to_arduino("2");
     }

}

void interface1::on_pushButton_22_clicked()
{
ui->stackedWidget->setCurrentIndex(4);
ui->pushButton_22->hide();
}

void interface1::on_pushButton_23_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
ui->pushButton_23->hide();
}
// integration contrat

void interface1::on_ajouter_clicked(){
    QString CONTRATID_string = ui->CONTRATID->text();
      bool ok;
      int CONTRATID = CONTRATID_string.toInt(&ok);

      if (!ok) {

          QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer ID.");
          return;
      }
      QString DATEDEBUT = ui->DATEDEBUT->text();

      QString DATEFIN = ui->DATEFIN->text();

      QString MONTANT = ui->MONTANT->text();


      contrat tr(CONTRATID,DATEDEBUT,DATEFIN,MONTANT);
      bool test = tr.ajouter();

      QMessageBox msgBox;
      if (test) {
          msgBox.setText("ajout avec succes");
          msgBox.exec();
          ui->CONTRATID->clear();
          ui->DATEDEBUT->clear();
          ui->DATEFIN->clear();
          ui->MONTANT->clear();


      } else {
          msgBox.setText("echec");
          msgBox.exec();
      }

      ui->affiche_tab->setModel(tr.afficher());
      QSqlQuery qry;
      QDateTime dateTime=QDateTime::currentDateTime();


      QString date=dateTime.toString();

      qry.prepare("insert into HISTORIQUE (ACTIVITE,DATEE) values ('ajout contrat',:dateTime)");
      qry.bindValue(":dateTime",dateTime);

      qry.exec();



};
void interface1::on_supprimer_clicked() {
    contrat f;
    int CONTRATID= ui->CONTRATID->text().toInt();
    bool test = f.supprimer(CONTRATID);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Suppression effectuée.\n"
                                             "Click Ok to exit."), QMessageBox::Ok);
        QSqlQuery qry;
        QDateTime dateTime=QDateTime::currentDateTime();

        QString date=dateTime.toString();

        qry.prepare("insert into HISTORIQUE (ACTIVITE,DATEE) values ('supression contrat',:dateTime)");
        qry.bindValue(":dateTime",dateTime);

        qry.exec();



    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                              QObject::tr("Échec de la suppression.\n"
                                          "Le fournisseur n'existe pas dans la base de données."),
                              QMessageBox::Cancel);
    }
    ui->affiche_tab->setModel(f.afficher());


}


void interface1::on_modifier_clicked()
{

        int CONTRATID=ui->CONTRATID->text().toInt();
           QString DATEDEBUT = ui->DATEDEBUT->text();
           QString DATEFIN = ui->DATEFIN->text();
           QString MONTANT = ui->MONTANT->text();






              contrat f(CONTRATID,DATEDEBUT,DATEFIN,MONTANT);

                 bool test=f.modifier(CONTRATID,DATEDEBUT,DATEFIN,MONTANT);

                 if(test)

               {ui->affiche_tab->setModel(f.afficher());

               QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                                 QObject::tr("invite modifiée.\n"

                                             "Click ok to exit."), QMessageBox::Ok);



               }

                 else

                     QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                                 QObject::tr("echec d'ajout !.\n"

                                             "Click Cancel to exit."), QMessageBox::Cancel);


}


void interface1::on_afficher_clicked()
{
    contrat f;
    ui->affiche_tab->setModel(f.afficher());
}


void interface1::on_affiche_tab_activated(const QModelIndex &index)
{
    QString val=ui->affiche_tab->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from GESTIONCONTRAT where CONTRATID='"+val+"'");
    if(qry.exec())

    {
     while(qry.next())
     {ui->CONTRATID->setText(qry.value(0).toString());
         QString startDateString = qry.value(1).toString();
         QString endDateString = qry.value(2).toString();
         QDate startDate = QDate::fromString(startDateString, "yyyy-MM-dd");  // Adjust the format based on your database
         QDate endDate = QDate::fromString(endDateString, "yyyy-MM-dd");      // Adjust the format based on your database
         // Setting the QDate objects as text in the UI
         ui->DATEDEBUT->setDate(startDate);
         ui->DATEFIN->setDate(endDate);
      ui->MONTANT->setText(qry.value(3).toString());


     }
    }
    else
    {
     QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}


void interface1::on_tri_clicked()
{
    contrat f;
    ui->affiche_tab->setModel(f.trier());
}

void interface1::on_pdf_clicked()
{
    contrat f;
    f.telechargerPDF();

    QMessageBox::information(nullptr,QObject::tr("OK"),
               QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);
}

void interface1::on_chercher_textChanged(const QString &arg1)
{
    contrat f;
    int CONTRATID= ui->chercher->text().toInt();

  f.recherche(ui->affiche_tab,CONTRATID);
    if (ui->chercher->text().isEmpty())
    {
        ui->affiche_tab->setModel(f.afficher());
    }
}

void interface1::on_stattt_clicked()
{
    statistic = new class Statistic(this);
    statistic->setWindowTitle("smart garden | Statistiques");
    statistic->show();
}

void interface1::on_historique_clicked()
{
    contrat p;
    ui->tableViewHistorique->setModel(p.afficherHistorique());
}

void interface1::on_tableViewHistorique_activated(const QModelIndex &index)
{
    QString val = ui->tableViewHistorique->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT montant FROM GESTIONCONTRAT WHERE CONTRATID='" + val + "'");

    if (qry.exec()) {
        if (qry.next()) {
            // Retrieve the montant value from the query result
            double montantValue = qry.value(0).toDouble(); // Assuming montant is a numeric field

            // Compare the montant value with 5000
            if (montantValue > 5000) {
                // Do something if montant is over 5000
                qDebug() << "Montant is over 5000!";
            } else {
                // Do something if montant is 5000 or less
                qDebug() << "Montant is 5000 or less.";
            }
        } else {
            // Handle the case where the query returned no results for the given CONTRATID
            qDebug() << "No data found for CONTRATID: " << val;
        }
    } else {
        // Handle the case where the query execution failed
        qDebug() << "Query execution failed:" << qry.lastError().text();
    }
}



void interface1::on_MONTANT_2_selectionChanged()
{

}

void interface1::on_tri_2_clicked()
{
    int CONTRATID=ui->id_ca->text().toInt();

       contrat c;

   if(c.doesCINExist(CONTRATID)&&i==0)
    {

       i=1 ;

     double CONTRATIDD = c.getid(CONTRATID);

       QString CONTRATIDString = QString::number(CONTRATIDD);


       QByteArray dataToSendd = CONTRATIDString.toUtf8();
         myArduino.write_to_arduino(dataToSendd);
      //   qDebug() << dataToSendd;
}
}

void interface1::on_tri_3_clicked()
{
    int CONTRATID=ui->id_ca->text().toInt();

       contrat c;

    if(c.doesCINExist(CONTRATID)&&j==0)
    {
        j=1;


     double MONTANT = c.getmontant_b(CONTRATID);

      QString MONTANTString = QString::number(MONTANT);

         QByteArray dataToSend = MONTANTString.toUtf8();
          myArduino.write_to_arduino(dataToSend);
    //          qDebug() << dataToSend;

}

}