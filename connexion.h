#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
public:
    Connection();
    bool createconnect();
   // bool checkLogin(const QString& username, const QString& password);




};

#endif // CONNEXION_H
