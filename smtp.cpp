

#include "smtp.h"

smtp::smtp(const QString &user, const QString &pass, const QString &host, int port, int timeout)
{
    socket = new QSslSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    this->user = user;
    this->pass = pass;
    this->host = host;
    this->port = port;
    this->timeout = timeout;
}

void smtp::sendMail(const QString &from, const QString &to, const QString &subject, const QString &body)
{
    qDebug() << "Sending mail...";
    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");
    message.append("MIME-Version: 1.0\n");
    message.append("Content-Type: text/plain\n\n");
    message.append(body);

    this->from = from;
    rcpt = to;
    state = Init;
    socket->setProtocol(QSsl::TlsV1_2);

    socket->connectToHostEncrypted(host, port);

    if (!socket->waitForConnected(timeout)) {
        qDebug() << "sendMail " << socket->errorString();
    }

    t = new QTextStream(socket);
}

smtp::~smtp()
{
    delete t;
    delete socket;
}

void smtp::stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "stateChanged " << socketState;
}

void smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "error " << socketError;
}

void smtp::disconnected()
{
    qDebug() << "disconnected";
    qDebug() << "error " << socket->errorString();
}

void smtp::connected()
{
    qDebug() << "Connected ";
}

void smtp::readyRead()
{
    qDebug() << "readyRead";

    QString responseLine;
    do {
        responseLine = socket->readLine();
        response += responseLine;
    } while (socket->canReadLine() && responseLine[3] != ' ');

    responseLine.truncate(3);

    qDebug() << "Server response code:" << responseLine;
    qDebug() << "Server response: " << response;

    if (state == Init && responseLine == "220") {
        *t << "EHLO localhost" << "\r\n";
        t->flush();
        state = HandShake;
    }
    // Add the rest of the code as before
    // ...
}

QAbstractSocket::SocketState smtp::getSocketState() const
{
    return socket->state();
}

QString smtp::getSocketErrorString() const
{
    return socket->errorString();
}
QString smtp::getServerResponse() const
{
    return response;
}
