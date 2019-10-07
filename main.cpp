#include <QApplication>
#include "startup.h"
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartUp start_up;
    QObject::connect(&a,&QApplication::lastWindowClosed,
                     &a,&QApplication::quit); 
    start_up.show();
    return a.exec();
}

