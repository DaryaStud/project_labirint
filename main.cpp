#include "labirint.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Labirint w;
    w.show();
    return a.exec();
}
