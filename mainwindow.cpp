#include "mainwindow.h"
#include<mainwindow.h>
#include "QString"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QGroupBox>
#include<QSqlQueryModel>
#include<QApplication>
#include"connection.h"
#include<QDate>
#include<QTextStream>
#include<QPainter>
#include<QPdfWriter>
#include<QFileInfo>
#include<QFileDialog>
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
#include<QSqlRecord>
#include<QTextDocument>
#include "smtp.h"
#include <QRegExp>
#include <QStandardItemModel>
#include <QInputDialog>
#include<QSslSocket>


QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->rechercher->setValidator(new QIntValidator(0,999999999,this));
    ui->lineEdit_NUMPERMIS->setValidator(new QIntValidator(0,999999999,this));
    ui->lineEdit_NUMTEL->setValidator(new QIntValidator(0,999999999,this));
    ui->lineEdit_NUMCIN->setValidator(new QIntValidator(0,999999999,this));
    ui->lineEdit->setValidator(new QIntValidator(0,999999999,this));
    ui->lineEdit_numpermis->setValidator(new QIntValidator(0,999999999,this));
    ui->lineEdit_numtel->setValidator(new QIntValidator(0,999999999,this));
    ui->cinToModifyLineEdit->setValidator(new QIntValidator(0,999999999,this));
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
    chartview->setParent(ui->horizontalFrame);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_on_pushButton_ajouter_clicked_clicked()
{
    QString nom=ui->lineEdit_NOM->text();
    QString prenom=ui->lineEdit_PRENOM->text();
    QString adresse=ui->lineEdit_ADRESSE->text();
    QString adresseemail=ui->lineEdit_ADRESSEEMAIL->text();
    int numpermis=ui->lineEdit_NUMPERMIS->text().toInt();
    QDate naissance=ui->lineEdit_NAISSANCE->date();
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
        chartview->setParent(ui->horizontalFrame);


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

void MainWindow::on_pushButton_clicked()
{

    int numcin=ui->lineEdit->text().toInt();
    bool test=etmp.supprimer(numcin);
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
        chartview->setParent(ui->horizontalFrame);
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


void MainWindow::on_pushButton_2_clicked()
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
            chartview->setParent(ui->horizontalFrame);
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

void MainWindow::on_pushButton_3_clicked()
{

        client x;
        int nbe = ui->rechercher->text().toInt();


           QSqlQueryModel *resultModel = x.rechercher(nbe);


           if (resultModel && resultModel->rowCount() > 0) {


               ui->tableView_3->setModel(resultModel);

           } else {

               QMessageBox::critical(this, "Erreur", "Aucune donnée trouvée pour cet numcin.", QMessageBox::Cancel);
           }

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tableView->setModel(etmp.afficher(true));
}
void MainWindow::on_pushButton_5_clicked()
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



void MainWindow::on_pushButton_6_clicked()
{
    QString message = ui->lineEdit_4->text();
        int numcin = ui->lineEdit_2->text().toInt();

        // Retrieve the client's email address using the numcin
        client x;
        QSqlQueryModel *resultModel = x.rechercher(numcin);

        if (resultModel && resultModel->rowCount() > 0) {
            QString clientEmail = resultModel->record(0).value("ADRESSEEMAIL").toString();

            // Validate the email address
            if (isValidEmail(clientEmail)) {
                // Send the email
                smtp *smtpClient = new smtp("your_email@gmail.com", "your_password", "smtp.gmail.com", 465);
                smtpClient->sendMail("your_email@gmail.com", clientEmail, "Subject", message);

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
void MainWindow::sendMail()
{
    qDebug() << "Sending email...";

        // Get the user input from the line edits
        QString clientEmail = ui->lineEdit_ADRESSEEMAIL->text();
        QString message = ui->lineEdit_4->text();


        // Validate the email address
        if (!isValidEmail(clientEmail)) {
            qDebug() << "Invalid email address";
            QMessageBox::critical(this, "Error", "Invalid email address");
            return;
        }

        // Create an instance of the smtp class with your email credentials
        smtpClient = new smtp("your_email@gmail.com", "your_password", "smtp.gmail.com", 465);

        qDebug() << "Email content:";
        qDebug() << "To: " << clientEmail;
        qDebug() << "Subject: Subject";
        qDebug() << "Body: " << message;

        // Send the email
        smtpClient->sendMail("your_email@gmail.com", clientEmail, "Subject", message);

        // Check for successful email sending
        if (smtpClient->getSocketState() == QAbstractSocket::ConnectedState) {
            qDebug() << "Email sent successfully!";

            // Additional debugging information
            qDebug() << "Socket state:" << smtpClient->getSocketState();
            qDebug() << "Socket error string:" << smtpClient->getSocketErrorString();
            qDebug() << "SMTP server response:" << smtpClient->getServerResponse();

            QMessageBox::information(this, "Email Sent", "The email has been sent successfully!");
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

bool MainWindow::isValidEmail(const QString &email)
{
    // Simple email validation using a regular expression
        QRegExp emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
        return emailRegex.exactMatch(email);
}
