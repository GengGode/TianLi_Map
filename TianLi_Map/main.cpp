#include "TianLi_Map.h"
#include <QTranslator>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QTranslator translator;
	translator.load(":/tr/TianLi_Map_ZH.qm");
	a.installTranslator(&translator);

    TianLi_Map w;
    w.show();

    return a.exec();
}
