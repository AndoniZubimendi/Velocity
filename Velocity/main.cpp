#include <QApplication>
#include <QStringList>
#include "mainwindow.h"
#include "botan/botan.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList<QUrl> args;
    for (int i = 1; i < argc; i++)
        args.append(QUrl("file:///" + QString::fromLatin1(argv[i]).replace("\\", "/")));

    Botan::LibraryInitializer init;

    MainWindow w(args);
    w.show();
    
    return a.exec();
}
