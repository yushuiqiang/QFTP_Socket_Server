#include "mymainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/appicon"));
    MyMainWindow w;
    w.show();

    return a.exec();
}
