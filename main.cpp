#include "platform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Platform platform;

    return a.exec();
}
