#include <QtGui/QApplication>
#include "mouse2j.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mouse2J w;
    w.show();

    return a.exec();
}
