#ifndef MESSENGER_H
#define MESSENGER_H

#include <QObject>
#include "message.h"

class Messenger : public QObject
{
    Q_OBJECT
public:
    explicit Messenger(QObject *parent = nullptr);
    ~Messenger();
    enum Status{
        Connected,
        DublicateName,
        Disconected,
        Destroyed
    };

    Status getStatus() const;
    void setStatus(const Status &value);
    void conectToSrv(const QString &userName);
    void sendMes(const Message &message);
signals:
    void incomingMessage(const Message &message);
public slots:
    void disconnectFromSrv(const QString &userName);
private:
    Status status;
};

#endif // MESSENGER_H
