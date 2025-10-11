#include <QApplication>
#include "ui/windows/MainWindow.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(360, 520);
    w.show();
    return QApplication::exec();
}
