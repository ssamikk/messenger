#include "messenger.h"
#include "server.h"

Messenger::Messenger(QObject *parent) : QObject(parent)
{
    status = Messenger::Disconected;
}

Messenger::~Messenger()
{
}

Messenger::Status Messenger::getStatus() const
{
    return status;
}

void Messenger::setStatus(const Status &value)
{
    status = value;
}

void Messenger::conectToSrv(const QString &userName)
{
    Server *srv = Server::current();
    status = srv->registration(this, userName);
}

void Messenger::sendMes(const Message &message)
{
    if(!message.getMes().isEmpty()){
        Server *srv = Server::current();
        srv->inMessage(message);
    }
}

void Messenger::disconnectFromSrv(const QString &userName)
{
    Server *srv = Server::current();
    srv->delUser(userName);
}
