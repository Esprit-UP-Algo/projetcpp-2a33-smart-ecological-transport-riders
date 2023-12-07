#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>
#include<QTimer>
#include<QDialog>
mainwindow::mainwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    if (myArduino.connect_arduino() == 0)
        {
            qDebug() << "Arduino connected successfully.";
        }
        else
        {
            QMessageBox::critical(this, "Error", "Couldn't connect to Arduino.");
        }

        // Setup timer for reading data every 1000 ms (1 second)
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &mainwindow::readDataFromArduino);
        timer->start(1000);  // Read data every 1000 ms
}
void mainwindow::readDataFromArduino()
{
    QByteArray data = myArduino.read_from_arduino();
    qDebug() << "Data from Arduino: " << data;

    // Assuming the received data is the matricule
    int matricule = data.toInt();

    // Get the name from the database using the employe class
    QString name = myEmployee.getNomByMatricule(matricule);

    // Process the received data and name as needed
    qDebug() << "Name for Matricule " << matricule << ": " << name;
}
mainwindow::~mainwindow()
{
    delete ui;
}

