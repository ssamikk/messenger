#ifndef CLIENT_H
#define CLIENT_H

#include "message.h"

#include <QMainWindow>

class Messenger;

#ifndef utr
# define utr QString::fromUtf8
#endif

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(bool isAdm = false, QWidget *parent = nullptr);
    ~Client();
    const QString ADMIN_NAME= utr("Администратор");
    const QString DEFAULT_NAME= utr("Пользователь");
signals:
    void needDestroy();
public slots:
    bool registration(const QString &userName);
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_actionAddUser_triggered();
    void on_pushButtonSend_clicked();
    void incomingMessage(const Message &messag);
    void updateState();
    void destroyClient();
private:
    Ui::Client *ui;
    QString userName;
    Messenger *messenger;
    QString lastSender;
};

#endif // CLIENT_H
