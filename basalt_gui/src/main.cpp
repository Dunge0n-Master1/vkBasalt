#include "mainwindow.hpp"

#include <QApplication>
#include <QTranslator>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QTranslator  t;
    if (t.load(QLocale(), "vkBasaltGui", "_", ":/i18n"))
        a.installTranslator(&t);
    MainWindow w;
    w.show();
    return a.exec();
}
