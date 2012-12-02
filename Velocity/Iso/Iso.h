#pragma once

#include <QString>
#include <QByteArray>

#include "../winnames.h"
#include "../FileIO.h"


class Iso {

    enum DiscType {
        INVALID = -1,
        XSF = 0,
        GDFX = 0xFD90000 / 2048,
        XGD3 = 0x2080000 / 2048
    };

public:
    Iso(const QString &filename);
    ~Iso();

    QByteArray getRawBlocks(DWORD n, int size = 1);
    QByteArray getBlocks(DWORD n, int size = 1);

protected:

    int convertToLittleEndianInt(const QByteArray &a);
    DWORD convertSizeToBlockSize(INT64 size);
    int convertToLittleEndianWord(const QByteArray &a);

    bool parseRootDirectory();
    bool parseDirectory(const QString &dirPath, DWORD sector, DWORD size);
    bool parseDirectoryEntries(const QString &dirPath, const QByteArray &blockData, int offset);
    bool readVolumeDescriptor();
    bool verifyImage();

    FileIO * isoFile;

    DiscType type;
    const INT64 blockSize;
    DWORD rootSize;
    DWORD rootSector;
};
