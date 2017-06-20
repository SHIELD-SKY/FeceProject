#include "camaraget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    camaraGet w;
    w.show();

    return a.exec();
}
