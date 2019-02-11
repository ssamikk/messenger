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
    connect(messenger, SIGNAL(incomingMessage(const Message &)),
            this, SLOT(incomingMessage(const Message &)));
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
    }else{
        connect(client, SIGNAL(needDestroy()), this, SLOT(destroyClient()));
    }
}

void Client::on_pushButtonSend_clicked()
{
    if(messenger->getStatus()== Messenger::Connected){
        Message message(userName, ui->textEditMessage->toPlainText());
        messenger->sendMes(message);
        ui->textEditMessage->clear();
    }
    ui->textEditMessage->setFocus();
}

void Client::incomingMessage(const Message &messag)
{
    if(lastSender!=messag.getUser()){
        lastSender = messag.getUser();
        if(!ui->textEditChat->toPlainText().isEmpty()){
            ui->textEditChat->append("<p/>");
        }
        ui->textEditChat->append("<p><b>"+messag.getUser()+"</b></p><p>"+messag.getMes()+"</p>");
    }else{
        ui->textEditChat->append("<p>"+messag.getMes()+"</p>");
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
