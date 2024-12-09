// Suppress non-critical compiler warnings if using Microsoft Visual Studio compiler
#ifdef VS_PRESENT
#pragma warning(disable : 4265 4625 4626 4688 4710 4711 4866 4820 5045 )
#endif

#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
