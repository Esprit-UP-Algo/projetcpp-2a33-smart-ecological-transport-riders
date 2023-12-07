#include "mainwindow.h"
#include<QTextStream>
#include"client.h"
#include<QIntValidator>
#include <QMainWindow>
#include <QMessageBox>
#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextStream>
#include <QDataStream>
#include <QTextDocument>
#include <QFile>
#include <QFileDialog>
#include "smtp.h"

#include <QFileDialog>
#include <QDebug>
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include <QtCharts>
#include <QtCharts/QBarSet>

#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <qmessagebox.h>
#include "reservation.h"


// ...

QSerialPort serial;
QTimer timer;

using namespace qrcodegen;




MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{

     ui->setupUi(this);


 //ui->ID_C->setValidator(new QIntValidator(1000, 9999999, this));
 reservation C ;




 int ret=A.connect_arduino(); // lancer la connexion à arduino
 switch(ret){
 case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
     break;
 case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
    break;
 case(-1):qDebug() << "arduino is not available";
 }
  QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
  //le slot update_label suite à la reception du signal readyRead (reception des données).









 //controle saisie


  ui->le_nbpermis->setValidator(new QIntValidator(10000000,99999999, this));
  ui->le_ROLE->setValidator(new QIntValidator(10000000,99999999, this));
    ui->le_MAIL->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}"), this));
     ui->le_MailN->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}"), this));
 ui->le_PISTE->setValidator(new QIntValidator(0, 9999999, this));
 ui->le_PISTE_modifier->setValidator(new QIntValidator(0, 9999999, this));

 ui->le_ID_C->setValidator(new QIntValidator(0, 9999999, this));
 ui->le_ID_C_modifier->setValidator(new QIntValidator(0, 9999999, this));
 ui->le_ID_C_supprimer->setValidator(new QIntValidator(0, 9999999, this));





ui->tab_client->setModel(C.afficher());
ui->tab_client_2->setModel(C.afficher1());
ui->tab_client_3->setModel(C.afficher2());
}

MainWindow::~MainWindow()
{
    delete ui;
}
////////////////////////////

void MainWindow::update_label()
{
    data=A.read_from_arduino() ;
    if (data =="1")
        ui->label_3->setText("ON") ;
    else if (data=="0")
            ui->label_3->setText("OFF") ;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int CIN=ui->le_ID_C->text().toInt();
    QString NB_PERMIS=ui->le_ROLE->text();
    QString MONTANT_TOTAL=ui->le_PISTE->text();
    QString NOM=ui->le_nom->text();
    QString PRENOM=ui->le_prenom->text();
    QString MATRICULE=ui->le_TELEPHONE->text();
    QString DATEREN=ui->le_DATEREN->text();
    QString MAIL=ui->le_MAIL->text();




    reservation C(CIN,NOM,PRENOM,MATRICULE,DATEREN,MAIL,NB_PERMIS,MONTANT_TOTAL);


bool test=C.ajouter();
if(test)
 {    QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                               QObject::tr("ajout successful.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
  ui->tab_client->setModel(C.afficher());
ui->tab_client_2->setModel(C.afficher1());
           }
               else
{
                   QMessageBox::critical(nullptr, QObject::tr("Ajout errer"),
                               QObject::tr("ajout failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
}
     ui->tab_client->setModel(C.afficher());
ui->tab_client_2->setModel(C.afficher1());
//historique
     QFile file("C:/Users/asus/Desktop/crudfinal (1)/crudfinal/historique.txt");
     if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
         return;
     QTextStream cout(&file);
     QString d_info = QDateTime::currentDateTime().toString();
     QString message2=d_info+" - Un client a été ajouté avec la id   "+QString::number(CIN)+"par    "+NB_PERMIS+"\n";
     cout << message2;


}
void MainWindow::on_pb_supprimer_clicked()
{
    reservation C ;

        int CIN = ui->le_ID_C_supprimer->text().toInt();
        QString NB_PERMIS=ui->le_ROLE_supprimer->text();
        bool test=C.supprimer(CIN);
        if (test)
        {
            QMessageBox::information(nullptr,QObject::tr("OK"),
                    QObject::tr("Suppression effectuée\n"
                                "Click Cancel non to exit.") , QMessageBox :: Cancel);
           ui->tab_client->setModel((C.afficher()));//refrersh
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                  QObject::tr("Suppression non effectuée.\n"
                                              "Click Cancel to exit."),QMessageBox::Cancel);

        }

            ui->tab_client->setModel((C.afficher()));
ui->tab_client_2->setModel(C.afficher1());
ui->tab_client_3->setModel(C.afficher2());
        QFile file("C:/Users/asus/Desktop/crudfinal (1)/crudfinal/historique.txt");
                if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                    return;
                QTextStream cout(&file);
                QString d_info = QDateTime::currentDateTime().toString();
                QString message2=d_info+" - Un client a été supprimée avec la id   "+QString::number(CIN)+"\n";
                cout << message2;
}
void MainWindow::on_pb_modifier_clicked()
{
    int CIN= ui ->le_ID_C_modifier->text().toInt();
    QString NOM=ui->le_nom_modifier->text();
    QString PRENOM=ui->le_prenom_modifier->text();
    QString MATRICULE=ui->le_TELEPHONE_modifier->text();
    QString DATEREN=ui->le_DATEREN_modifier->text();
     QString MAIL=ui->le_MailN->text();
     QString NB_PERMIS=ui->le_nbpermis->text();
     QString MONTANT_TOTAL=ui->le_PISTE_modifier->text();
      //ui->NOM->setMaxLength(20);
       //ui->PRENOM->setMaxLength(20);

                reservation C  (CIN,NOM,PRENOM,MATRICULE,DATEREN,MAIL,NB_PERMIS,MONTANT_TOTAL);
            bool test=C.modifier( CIN,NOM,PRENOM,MATRICULE,DATEREN,MAIL,NB_PERMIS,MONTANT_TOTAL);
            if (test)
        {
                QMessageBox::information(nullptr, QObject::tr("modifie un client"),
                                  QObject::tr("client modifie.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

                QFile file("C:/Users/asus/Desktop/crudfinal (1)/crudfinal/historique.txt");
                        if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                            return;
                        QTextStream cout(&file);
                        QString d_info = QDateTime::currentDateTime().toString();
                        QString message2=d_info+" - Un client a été modifié avec la id   "+QString::number(CIN)+" \n";
                        cout << message2;
            }

        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                  QObject::tr("Modification non effectuée.\n"
                                              "Click Cancel to exit."),QMessageBox::Cancel);
        ui->tab_client->setModel((C.afficher()));
}





void MainWindow::on_search_2_clicked()
{ QString R=ui->search->text() ;

     ui->tab_client->setModel(C.rechercher(R));
}
void MainWindow::on_trier_clicked()
{
      QString comboBoxValue = ui->tri->currentText();
       if (comboBoxValue == "tri ID"){
    if(C.trier())
    {
        ui->tab_client->setModel(C.trier());

    }
}

else if (comboBoxValue == "tri nom")
{
    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM RESERVER order by NOM"); //ASC pour ascendant, DESC pour descendant
           q->exec();
           model->setQuery(*q);

        ui->tab_client->setModel(model);

}

else if (comboBoxValue == "tri prenom")
{
    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM RESERVER order by PRENOM"); //ASC pour ascendant, DESC pour descendant
           q->exec();
           model->setQuery(*q);

        ui->tab_client->setModel(model);
}

}



void MainWindow::on_pdf_clicked()
{
    QString strStream;
                         QTextStream out(&strStream);

                         const int rowCount = ui->tab_client->model()->rowCount();
                         const int columnCount = ui->tab_client->model()->columnCount();

                         out <<  "<html>\n"
                             "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                             <<  QString("<title>%1</title>\n").arg("strTitle")
                             <<  "</head>\n"
                             "<body bgcolor=#ffffff link=#5000A0>\n"

                            //     "<align='right'> " << datefich << "</align>"
                             "<center> <H1>Liste des employees </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                         // headers
                         out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                         for (int column = 0; column < columnCount; column++)
                             if (!ui->tab_client->isColumnHidden(column))
                                 out << QString("<th>%1</th>").arg(ui->tab_client->model()->headerData(column, Qt::Horizontal).toString());
                         out << "</tr></thead>\n";

                         // data table
                         for (int row = 0; row < rowCount; row++) {
                             out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                             for (int column = 0; column < columnCount; column++) {
                                 if (!ui->tab_client->isColumnHidden(column)) {
                                     QString data = ui->tab_client->model()->data(ui->tab_client->model()->index(row, column)).toString().simplified();
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
                   printer.setOutputFileName(fileName);

                    QTextDocument doc;
                     doc.setHtml(strStream);

                     doc.print(&printer);
}
void MainWindow::readfile(){
    QString filename="C:/Users/asus/Desktop/crudfinal (1)/crudfinal/historique.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "NO exist "<<filename;
    }else{
        qDebug() << filename<<" ...";
    }
    QString line;
    ui->Histo->clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
            ui->Histo->setText(ui->Histo->toPlainText()+line+"\n");
            qDebug() << "linea: "<<line;
        }
    }
    file.close();
}

void MainWindow::on_tabWidget_currentChanged()
{
    readfile();

}



void MainWindow::on_sendMail_clicked()
{QString mail=ui->from->text();
QString password=ui->paswd->text();
QString recpt=ui->to->text();
QString objet=ui->subject->text();
QString description=ui->msg->toPlainText();
Smtp *smtp = new Smtp(mail,password,"smtp.gmail.com");
smtp->sendMail(mail,recpt ,objet,description);}


/*

void MainWindow::mailsent(QString status)
{if(status == "Message sent")
QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
ui->to->clear();
ui->subject->clear();
ui->msg->clear();
ui->paswd->clear();
ui->from->clear();}

*/
void MainWindow::on_calendarWidget_clicked(const QDate &date)
{

    ui->le_DATEREN->setDate(date);
}


void MainWindow::on_QRcode_clicked()
{
    int cin = ui->CIN_QR->text().toInt();

    QSqlQuery qry;
    qry.prepare("SELECT nom, prenom, matricule, DATEREN, MAIL, NB_PERMIS, MONTANT_TOTAL FROM RESERVER WHERE CIN = :cin");
    qry.bindValue(":cin", cin);

    QString nom, prenom, matricule, dateRen, mail, nbPermis, montantTotal;

    if (qry.exec() && qry.next()) {
        nom = qry.value(0).toString();
        prenom = qry.value(1).toString();
        matricule = qry.value(2).toString();
        dateRen = qry.value(3).toString();
        mail = qry.value(4).toString();
        nbPermis = qry.value(5).toString();
        montantTotal = qry.value(6).toString();
    } else {
        // Handle the case where the CIN is not found or the query fails
        qDebug() << "Failed to retrieve data for CIN: " << cin;
        return;  // Exit the function if there's an issue with the query
    }

    QString ids = "CIN: " + QString::number(cin) +
                  " Nom: " + nom +
                  " Prenom: " + prenom +
                  " Matricule: " + matricule +
                  " DateRen: " + dateRen +
                  " Mail: " + mail +
                  " NbPermis: " + nbPermis +
                  " MontantTotal: " + montantTotal;

    QrCode qr = QrCode::encodeText(ids.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(), qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if (color == 0)
                im.setPixel(x, y, qRgb(254, 254, 254));
            else
                im.setPixel(x, y, qRgb(0, 0, 0));
        }
    }

    im = im.scaled(200, 200);
    ui->qrlabel->setPixmap(QPixmap::fromImage(im));
}
