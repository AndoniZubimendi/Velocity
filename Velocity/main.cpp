#include <QtGui/QApplication>
#include <QStringList>
#include "mainwindow.h"
#include "botan/botan.h"

#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("i18n/Velocity_" + QLocale::system().name());
    a.installTranslator(&qtTranslator);

    QList<QUrl> args;
    for (int i = 1; i < argc; i++)
        args.append(QUrl("file:///" + QString::fromAscii(argv[i]).replace("\\", "/")));

    Botan::LibraryInitializer init;

    MainWindow w(args);
    w.show();
    
    return a.exec();
}
