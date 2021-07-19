#include "TianLi_Map.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TianLi_Map w;
    w.show();
    return a.exec();
}
