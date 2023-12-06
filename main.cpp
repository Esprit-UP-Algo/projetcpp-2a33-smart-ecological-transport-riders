#include <QMainWindow>
#include "mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include "connexion.h"
#include "interface1.h"
#include "employe.h"
#include "client.h"


#include <QGuiApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    employe E;
    Connection c;
//mainwindow w;


    bool test=c.createconnect();

    interface1 i;

    if(test)
    {i.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
