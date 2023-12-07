#include "gestion_contrat.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include "contrat_ar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
contrat_ar ca;
    Connection c;
          bool test=c.createconnect();
           gestion_contrat w;
          if(test){
          ca.show();
          w.show();

    QMessageBox::information(nullptr, QObject::tr("database is open"),
                          QObject::tr("connection successful.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

      }
          else
              QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                          QObject::tr("connection failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);



          return a.exec();
          w.show();

    return a.exec();
}
