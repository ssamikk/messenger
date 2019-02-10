#include "client.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client admin(true);
    admin.show();

    return a.exec();
}
