#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr, "/home/windspring/c++Pro/opencvExamples/ReadVideo/Snow.mp4");
    w.show();
    return a.exec();
}
