#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <stdio.h>

typedef struct _NvRamHeader
{
    unsigned int map_size;
    unsigned int dat_size;
    unsigned int ________;
    unsigned int checksum;

    //unsigned char map_file[4/*map_size*/];

} NvRamHeader;

typedef struct _NvImei {
    unsigned int imei;
}imei;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const char *bin_file = "nvram.bin";
    FILE *stream = fopen(bin_file, "rb");

    quint64 byte_postion = 0x21000;
    NvRamHeader header;
    memset(&header, 0, sizeof(NvRamHeader));
    fseek(stream, 0, SEEK_SET);
    fread(&header, 1, sizeof(header), stream);

    qInfo() << "Header Map size: " << header.dat_size;

    fclose(stream);

    QFile file("nvram_1.bin");
    file.open(QIODevice::ReadWrite);
    file.seek(byte_postion);

    QByteArray buffer =  file.read(12);

    QByteArray hex_to;
    hex_to.fromHex(buffer);
    hex_to.mid(0x2).left(2);


    qInfo() << buffer;

    qInfo() << hex_to;

    file.close();

    return a.exec();
}
