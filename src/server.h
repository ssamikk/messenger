#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "messenger.h"
#include <QVector>

class Server : public QObject
{
    Q_OBJECT
public:
    static Server *current();
    ~Server();
signals:
    void sendMessage(const QString &userName, const QString &mes);
public slots:
    Messenger::Status registration(const Messenger *messenger, const QString &userName);
    void inMessage(const QString &userName, const QString &mes);
    void delUser(const QString &userName);
private:
    explicit Server(QObject *parent = nullptr);
    QVector<QString> clientNames;
};

#endif // SERVER_H
