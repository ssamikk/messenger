#include "server.h"
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent)
{

}

Server *Server::current()
{
    static Server cur;
    return &cur;
}

Server::~Server()
{
    qDebug()<<"server shutdown";
}

Messenger::Status Server::registration(const Messenger *messenger, const QString &userName)
{
    if(!messenger){
        return Messenger::Disconected;
    }
    if(clientNames.contains(userName)){
        return Messenger::DublicateName;
    }
    clientNames.append(userName);
    connect(this, SIGNAL(sendMessage(const Message&)),
            messenger, SIGNAL(incomingMessage(const Message &)));

    return Messenger::Connected;
}

void Server::inMessage(const Message &mes)
{
    emit sendMessage(mes);
}

void Server::delUser(const QString &userName)
{
    clientNames.removeOne(userName);
}
