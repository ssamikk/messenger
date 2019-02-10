#include "client.h"
#include "ui_client.h"
#include "messenger.h"
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>

Client::Client(bool isAdm, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    messenger = new Messenger(this);
    connect(messenger, SIGNAL(incomingMessage(const QString &, const QString &)),
            this, SLOT(incomingMessage(const QString &, const QString &)));
    if(isAdm){
        userName = ADMIN_NAME;
        messenger->conectToSrv(userName);
        resize(550, 400);
    }else{
        ui->toolBar->hide();
        ui->menuBar->hide();
    }
    updateState();
}

Client::~Client()
{
    messenger->disconnectFromSrv(userName);
    qDebug()<<"destroy client"<<userName;
    delete ui;
}

bool Client::registration(const QString &userName)
{
    bool ok;
    QString text = QInputDialog::getText(this, utr("Введите имя пользователя"),
                                         utr("Имя пользователя:"), QLineEdit::Normal,
                                         userName, &ok);
    if (ok){
        if(text.isEmpty()){
            QMessageBox::information(this, utr("Регистрация"),
                                     utr("Имя пользователя не может быть пустым."),
                                     utr("Отмена"));
            ok = false;
        }else{
            messenger->conectToSrv(text);
            switch (messenger->getStatus()) {
            case Messenger::Connected:
                ok = true;
                this->userName = text;
                updateState();
                break;
            case Messenger::DublicateName:
                QMessageBox::information(this, utr("Регистрация"),
                                         utr("Пользователь с таким именем уже существует."),
                                         utr("Отмена"));
            default:
                ok = false;
                break;
            }
        }
        if(!ok){
            ok = registration(text);
        }
    }
    return ok;
}

void Client::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit needDestroy();
}

void Client::on_actionAddUser_triggered()
{
    Client * client = new Client(false, this);
    client->show();
    if(!client->registration(DEFAULT_NAME)){
        client->close();
        delete client;
    }
    connect(client, SIGNAL(needDestroy()), this, SLOT(destroyClient()));
}

void Client::on_pushButtonSend_clicked()
{
    if(messenger->getStatus()== Messenger::Connected){
        messenger->sendMes(userName, ui->textEditMessage->toPlainText());
        ui->textEditMessage->clear();
    }
}

void Client::incomingMessage(const QString &userName, const QString &mes)
{
    if(lastSender!=userName){
        lastSender = userName;
        if(!ui->textEditChat->toPlainText().isEmpty()){
            ui->textEditChat->append("<p/>");
        }
        ui->textEditChat->append("<p><b>"+userName+"</b></p><p>"+mes+"</p>");
    }else{
        ui->textEditChat->append("<p>"+mes+"</p>");
    }

}

void Client::updateState()
{
    bool flagVis = messenger->getStatus() == Messenger::Connected;
    ui->pushButtonSend->setEnabled(flagVis);
    setWindowTitle(userName);
}

void Client::destroyClient()
{

    delete sender();
}
