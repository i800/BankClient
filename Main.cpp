#include "App.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication system(argc, argv);
    App app;
    return system.exec();
}
