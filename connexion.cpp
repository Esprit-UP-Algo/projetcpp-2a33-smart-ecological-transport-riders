#include "connexion.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include<QString>
#include<QSqlError>


Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
///db.setDatabaseName("projet2a");
//db.setUserName("sarahh");//inserer nom de l'utilisateur
//db.setPassword("sarah");//inserer mot de passe de cet utilisateur
db.setDatabaseName("Source_Projet2A");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("Syrine123");//inserer mot de passe de cet utilisateur
if (db.open())
test=true;
    return  test;
}




/*bool Connection::checkLogin(const QString& username, const QString& password) {

    QString predefinedUsername = "user123";
       QString predefinedPassword = "pass456";

    return  test;
}
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE USERNAME = :username AND PASSWORD = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (username == predefinedUsername && password == predefinedPassword) {
        // Login successful

        return true;
    } else {
        // Login failed
        return false;
    }
}
*/

