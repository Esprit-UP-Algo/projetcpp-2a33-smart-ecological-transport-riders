#ifndef SMTP_H
#define SMTP_H
#include <QObject>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>

class smtp : public QObject
{
    Q_OBJECT

public:
    smtp(const QString &user, const QString &pass, const QString &host, int port = 578, int timeout = 30000);
    ~smtp();

    void sendMail(const QString &from, const QString &to, const QString &subject, const QString &body);
    QAbstractSocket::SocketState getSocketState() const;
        QString getSocketErrorString() const;
         QString getServerResponse() const;

signals:
    void status(const QString &);

private slots:
    void stateChanged(QAbstractSocket::SocketState socketState);
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void connected();
    void readyRead();
    void sslErrors(const QList<QSslError> &errors);

private:

    QSsl::SslProtocol tlsVersion;
    int timeout;
    QString message;
    QTextStream *t;
    QSslSocket *socket;
    QString from;
    QString rcpt;
    QString response;
    QString user;
    QString pass;
    QString host;
    int port;
    enum states { Tls, HandShake, Auth, User, Pass, Rcpt, Mail, Data, Init, Body, Quit, Close };
    int state;
};
#endif // SMTP_H
