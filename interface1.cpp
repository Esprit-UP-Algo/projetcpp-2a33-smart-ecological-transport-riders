
#include "interface1.h"
#include "ui_interface1.h"
#include <QMainWindow>
#include "mainwindow.h"
#include "client.h"

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


interface1::interface1(QWidget *parent):
     QMainWindow(parent),
     ui(new Ui::interface1)
{
    ui->setupUi(this);
    ui->le_matricule->setValidator(new QIntValidator(0,999999,this));
    ui->tab_employe->setModel(E.afficher());
    ui->stackedWidget->setCurrentIndex(2);
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
 if (ui->label_pass->text().contains(QRegExp("[^0-9]") ) || ui->label_pass->text().isEmpty())
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
int pass = ui->label_pass->text().toInt();
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

        if (query.exec() && query.next()) {
            QMessageBox::information(this, "CONNECTED", "Connecté");
           // ui->stackedWidget->setCurrentIndex(0);
             ui->stackedWidget->setCurrentIndex(3);


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
    ui->stackedWidget->setCurrentIndex(1);
}

void interface1::on_pushButton_qu_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

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
