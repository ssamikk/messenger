#include "message.h"

Message::Message(const QString &user, const QString &mes)
{
    this->user = user;
    this->mes = mes;
}

QString Message::getMes() const
{
    return mes;
}

QString Message::getUser() const
{
    return user;
}
