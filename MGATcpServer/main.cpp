#include <QCoreApplication>
#include "mgatcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MGATcpServer mTest;

    return a.exec();
}
