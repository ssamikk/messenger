#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

class Message
{
public:
    Message(const QString &user, const QString &mes);

    QString getUser() const;
    QString getMes() const;

private:
    QString user;
    QString mes;
};

#endif // MESSAGE_H
