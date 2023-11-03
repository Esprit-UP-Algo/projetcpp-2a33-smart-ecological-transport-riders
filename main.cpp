#include "interface1.h"
#include "employe.h"
#include "mainwindow.h"
#include "menu.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    employe E;
    Connection c;


    bool test=c.createconnect();
    interface1 i;
     MainWindow w;
    if(test)
    {w.show();
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
