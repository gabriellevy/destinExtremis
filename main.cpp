#include "extremis.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Extremis w;
    w.LancerHistoire(Extremis::VIE_HUMAIN, nullptr, "", "", true );
    w.show();

    return a.exec();
}
