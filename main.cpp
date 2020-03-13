#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QByteArray buffer_ = 0x00;
    QFile file("nvram.bin");
    if(!file.open(QIODevice::ReadOnly)) qInfo() << "File not found ";

    while(!file.atEnd()) {
        buffer_ = file.readAll();
        qInfo() << buffer_;
    }

    return a.exec();
}
