#include "interface1.h"
#include "ui_interface1.h"
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
#include <QPrinter>
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

#include <QTabWidget>




interface1::interface1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interface1)
{
    ui->setupUi(this);
    ui->le_matricule->setValidator(new QIntValidator(0,999999,this));
    ui->tab_employe->setModel(E.afficher());
    ui->stackedWidget->setCurrentIndex(1);
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
           on_lineEdit_rechercher_textChanged(QString::number(state));
       });



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
/* if (ui->label_pass->text().contains(QRegExp("[^0-9]") ) || ui->label_pass->text().isEmpty())
 {
     ui->label_21->setPixmap(PixFalseIcon);
 }

 else
 {
     ui->label_21->setPixmap(PixTrueIcon);
 }*/
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

                QPrinter printer (QPrinter::PrinterResolution);
                 printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
               printer.setOutputFileName(fileName);

                QTextDocument doc;
                 doc.setHtml(strStream);
                 doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                 doc.print(&printer);
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
            ui->stackedWidget->setCurrentIndex(0);
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
    QString queryStr = "SELECT EXTRACT(MONTH FROM EMPLOYE) AS Mois, COUNT(DISTINCT MATRICULE) AS NombreDeEmploye FROM EMPLOYE GROUP BY EXTRACT(MONTH FROM DATE)";
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryStr);

    // Afficher les données de la requête pour débogage
    for (int i = 0; i < model->rowCount(); ++i) {
        int mois = model->index(i, 0).data().toInt();
        int nombreDeEmploye = model->index(i, 1).data().toInt();
        qDebug() << "Mois : " << mois << ", Nombre de matricule : " << nombreDeEmploye;
    }

    //
    if (model->rowCount() == 0) {
        qDebug() << "Aucune donnée dans le modèle. Erreur : " << model->lastError().text();
    }


    QBarSeries *barSeries = new QBarSeries();


    for (int i = 0; i < model->rowCount(); ++i) {
        int mois = model->index(i, 0).data().toInt();
        int nombreDeEmploye = model->index(i, 1).data().toInt();

        // Ajouter une barre au diagramme avec la couleur bleue
        QBarSet *barSet = new QBarSet(QString::number(mois));
        barSet->append(nombreDeEmploye);

        // Définir la couleur de la barre à bleu
        barSet->setColor(Qt::blue);

        barSeries->append(barSet);
    }

    // Si le nombre de séries est de zéro, vérifions s'il y a des erreurs
    if (barSeries->barSets().size() == 0) {
        qDebug() << "Aucune série de barres dans le diagramme. Vérifiez les données ou les erreurs.";
    }

    // Créer le diagramme
    QChart *barChart = new QChart();

    // Ajouter la série au diagramme
    barChart->addSeries(barSeries);

    // Définir l'axe des abscisses pour le diagramme
    QBarCategoryAxis *axisX = new QBarCategoryAxis();

    // Specify the order of the months explicitly
    axisX->setCategories(QStringList() << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec");

    barChart->setAxisX(axisX, barSeries);

    // Définir l'axe des ordonnées pour le diagramme
    QValueAxis *axisY = new QValueAxis();
    barChart->setAxisY(axisY, barSeries);

    // Configurer le titre du diagramme
    barChart->setTitle("Nombre de Employe par Mois");
    barChart->legend()->hide();

    // Utilisé pour afficher le diagramme
    QChartView *barChartView = new QChartView(barChart);
    barChartView->setRenderHint(QPainter::Antialiasing);
    barChartView->resize(1000, 500);
    barChartView->show();

    ui->tabWidget->addTab(barChartView, "Stat"); // Replace "yourTabWidgetName" with the actual name of your QTabWidget
        ui->tabWidget->setCurrentWidget(barChartView);
}












/*



void MainWindow::load(){
    QFile file(log);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while(!in.atEnd()){
            QStringList dati;
            QString riga = in.readLine();
            if(riga.length()>0){
                dati = riga.split('\t');
                activities.push_back(attivita(dati));
            }
        }
    }
    file.close();
}

void MainWindow::showActivities(){
    QStringList headers = {"Tipo Attività", "Titolo", "Ora Inizio", "Ora Fine", "Ripeti", "Azioni"};
    QDate data = ui->calendarWidget->selectedDate();
    std::vector<int> pos;
    for(unsigned int i=0; i<activities.size(); i++){
        if(activities.at(i).finish.date() >= data){
            QString rep = activities.at(i).repeats;
            int r = -1;
            if(rep == "Mai")
                r = 0;
            if(rep == "Ogni giorno")
                r = 1;
            if(rep == "Ogni mese")
                r = 2;
            if(rep == "Ogni anno")
                r = 3;
            if(rep == "Ogni settimana")
                r = 4;
            switch(r){
            case 0:
                if(activities.at(i).data==data){
                    pos.push_back(i);
                }
                break;
            case 1:
                if(activities.at(i).data <= data){
                    pos.push_back(i);
                }
                break;
            case 2:
                if(activities.at(i).data.day()==data.day() && activities.at(i).data <= data){
                    pos.push_back(i);
                }
                break;
            case 3:
                if(activities.at(i).data.day()==data.day() && activities.at(i).data.month()==data.month() && activities.at(i).data <= data){
                    pos.push_back(i);
                }
                break;
            case 4:
                if(activities.at(i).data.dayOfWeek() == data.dayOfWeek() && activities.at(i).data <= data){
                    pos.push_back(i);
                }
                break;
            default: break;
            }
        }
    }
    ui->Attivita->setColumnCount(6);
    ui->Attivita->setColumnWidth(0, 130);
    ui->Attivita->setColumnWidth(1, 250);
    ui->Attivita->setColumnWidth(2, 75);
    ui->Attivita->setColumnWidth(3, 75);
    ui->Attivita->setColumnWidth(4, 120);
    ui->Attivita->setColumnWidth(5, 80);
    ui->Attivita->setRowCount(pos.size());
    ui->Attivita->setFont(QFont ("Times", 10, QFont::Bold));
    ui->Attivita->setHorizontalHeaderLabels(headers.last(6));
    ui->Attivita->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->Attivita->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->Attivita->setStyleSheet("QTableWidget::item { padding: 0px }");
    ui->Attivita->setSortingEnabled(false);
    for(unsigned int i=0; i<pos.size(); i++){
        ui->Attivita->setRowHeight(i, 40);
        QStringList ActInfo = activities.at(pos.at(i)).getInfo();
        for(int j=0; j<5; j++){
            QTableWidgetItem *el = new QTableWidgetItem();
            el->setData(Qt::EditRole, ActInfo.at(j));
            ui->Attivita->setItem(i, j, el);
            ui->Attivita->item(i, j)->setFlags((ui->Attivita->item(i,j)->flags() ^ Qt::ItemIsEditable));
        }
        QToolButton *del = new QToolButton(this);
        QToolButton *edit = new QToolButton(this);
        del->setToolButtonStyle(Qt::ToolButtonIconOnly);
        edit->setToolButtonStyle(Qt::ToolButtonIconOnly);
        del->setIcon(QIcon::fromTheme("list-add", QIcon("delete.png")));
        edit->setIcon(QIcon::fromTheme("list-add", QIcon("edit.png")));
        del->setText(QString::number(pos.at(i)));
        edit->setText(QString::number(pos.at(i)));
        QGroupBox *box = new QGroupBox();
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(del);
        layout->addWidget(edit);
        box->setLayout(layout);
        connect(del, &QToolButton::clicked , this, &MainWindow::removeActivity);
        connect(edit, &QToolButton::clicked , this, &MainWindow::editActivity);
        ui->Attivita->setCellWidget(i, 5, box);
    }
    ui->Attivita->setSortingEnabled(true);
    ui->Attivita->sortByColumn(2, Qt::AscendingOrder);
}


void interface1::on_AddActivity_clicked()
{
    QDate selectedDate = ui->calendarWidget->selectedDate();
    ActivityDialog *act = new ActivityDialog(this, selectedDate, &activities);
    if(act->exec()){
        showActivities();
    }
}

void interface1::addActivity(attivita a){
    activities.push_back(a);
}

void interface1::removeActivity(){
    QToolButton *sender = qobject_cast<QToolButton*>(QObject::sender());
    int pos = std::stoi(sender->text().toStdString());
    activities.erase(activities.begin()+pos);
    QFile file(log);
    int i=0;
    QStringList testo;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while(!in.atEnd()){
            QString riga = in.readLine();
            if(i != pos){
                testo.append(riga);
            }
            i++;
        }
    }
    file.close();
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream in(&file);
        for(int i=0; i<testo.size(); i++){
            in << testo.at(i) << '\n';
        }
    }
    file.close();
    showActivities();
}

void interface1::editActivity(){
    QToolButton *sender = qobject_cast<QToolButton*>(QObject::sender());
    int pos = std::stoi(sender->text().toStdString());
    QFile file(log);
    int i=0;
    QStringList testo;
    int result = -1;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while(!in.atEnd()){
            QString riga = in.readLine();
            if(i != pos){
                testo.append(riga);
            }else{
                QDate selectedDate = activities.at(i).getData();
                ActivityDialog *act = new ActivityDialog(this, selectedDate, &activities, true, pos);
                result = act->exec();
                if(result == QDialog::Accepted){
                    activities.at(pos) = act->edited_activity;
                    int y = selectedDate.year();
                    int m = selectedDate.month();
                    int d = selectedDate.day();
                    QString dt = QString::number(y)+":"+QString::number(m)+":"+QString::number(d);
                    QStringList info = act->edited_activity.getInfo();
                    QString fin = info.at(5);;
                    if(info.at(3).length() == 0)
                        fin += " 23:59:59";
                    else
                        fin += " " + info.at(3);
                    testo.append(info.at(0)+'\t'+info.at(1)+'\t'+info.at(2)+'\t'+fin+'\t'+info.at(4)+'\t'+dt);
                    riga = "";
                }
            }
            i++;
        }
    }
    file.close();
    if(result == QDialog::Accepted){
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream in(&file);
            for(int i=0; i<testo.size(); i++){
                in << testo.at(i) << '\n';
            }
        }
        file.close();
    }
    showActivities();
}

void MainWindow::on_calendarWidget_selectionChanged()
{
    showActivities();
}


void MainWindow::on_calendarWidget_activated(const QDate &date)
{
    showActivities();
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    showActivities();
}











*/



