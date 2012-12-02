#include "Iso.h"

#include <iostream>

#define BLOCK_SIZE_BITS     11

Iso::Iso(const QString &path) : isoFile(0), type(INVALID), blockSize(1 << BLOCK_SIZE_BITS) {
    isoFile = new FileIO(path.toStdString(), false, true);
    if (!isoFile)
        return;

    if (verifyImage())
        parseRootDirectory();
}

Iso::~Iso()
{
    if (isoFile) {
        delete isoFile;
    }
}

QByteArray Iso::getRawBlocks(DWORD n, int size) {
    BYTE buffer[blockSize * size];
    isoFile->setPosition(n * blockSize);
    isoFile->readBytes(buffer, blockSize * size);
    return QByteArray((char *)buffer, blockSize * size);
}

QByteArray Iso::getBlocks(DWORD n, int size)  {
    return getRawBlocks(n + type, size);
}

int Iso::convertToLittleEndianWord(const QByteArray &a) {
    unsigned char a0 = a[0];
    unsigned char a1 = a[1];

    return a0 + a1*256;
}

int Iso::convertToLittleEndianInt(const QByteArray &a) {
    unsigned char a0 = a[0];
    unsigned char a1 = a[1];
    unsigned char a2 = a[2];
    unsigned char a3 = a[3];

    return a0 + a1*256 + a2 * 256 * 256 + a3 * 256 * 256 * 256;
}

DWORD Iso::convertSizeToBlockSize(INT64 size) {
    return ((size -1) >> BLOCK_SIZE_BITS) + 1;
}

bool Iso::parseRootDirectory() {
    return parseDirectory("", rootSector, rootSize);
}

bool Iso::parseDirectory(const QString &dirPath, DWORD block, DWORD size) {
    if (size == 0)
        return true;

    DWORD totalBlocks = convertSizeToBlockSize(size);

    //std::cout << "New directory - Size is " << size << " - Total blocks: " << totalBlocks << std::endl;
    QByteArray blockData = getBlocks(block, totalBlocks);

    return parseDirectoryEntries(dirPath, blockData, 0);
}

// 0 -> left word
// 2 -> right word
// 4 -> sector int
// 8 -> size int
// c -> attribs (dir) byte
// d -> entry name size - byte
// e -> entry name
// PADDING = 4 - (14 + name length) % 4

bool Iso::parseDirectoryEntries(const QString &dirPath, const QByteArray &blockData, int offset) {

    if (offset > blockData.size())
        return false;

    int leftTree = convertToLittleEndianWord(blockData.mid(offset,2));
    int rightTree = convertToLittleEndianWord(blockData.mid(offset + 2,2));

    if (leftTree == 65535)
        return true;

    if (leftTree) {
        parseDirectoryEntries(dirPath, blockData, leftTree * 4);
    }

    int entrySector = convertToLittleEndianInt(blockData.mid(offset + 4, 4));
    int entryContentSize = convertToLittleEndianInt(blockData.mid(offset + 8, 4));
    int entryNameSize = (unsigned char) blockData[offset + 13];
    int entryAttribs = blockData[offset + 12];
    /*
    int entryPadding = (4 - (14 + entryNameSize) % 4) % 4;
    int entrySize = entryPadding + 14 + entryNameSize;
    std::cout << "Offset: " <<  offset;
    std::cout << " / Size: " << entrySize << " ";
    std::cout << " / Size: " << entryNameSize << " ";
    std::cout << " - Left: " << leftTree * 4 << " / Right: " << rightTree * 4;
    std::cout << " - padding: " << entryPadding;
*/
    QString entryName = QString(blockData.mid(offset + 14, entryNameSize));

    if (entryAttribs & 0x10) {
        //std::cout << " - Directorio: " << entryName.toStdString() << std::endl;
        if (entryContentSize) {
            parseDirectory(dirPath + "/" + entryName, entrySector, entryContentSize);
        }
    } else {
        std::cout << (dirPath + "/" + entryName).toStdString() << " (" <<  entryContentSize << " bytes)" << std::endl;
    }

    if (rightTree)
        parseDirectoryEntries(dirPath, blockData, rightTree * 4);

    return true;
}

bool Iso::readVolumeDescriptor() {
    QByteArray volumeDescriptorBlock = getBlocks(32, 1);

    QString magic = QString::fromAscii(volumeDescriptorBlock.mid(0, 0x14).constData(), 0x14);
    if (magic != "MICROSOFT*XBOX*MEDIA")
        return false;

    rootSector = convertToLittleEndianInt(volumeDescriptorBlock.mid(0x14, 4));
    rootSize = convertToLittleEndianInt(volumeDescriptorBlock.mid(0x18, 4));

    std::cout << "sector " << rootSector << std::endl;
    std::cout << "size " << rootSize << std::endl;

    return true;
}

bool Iso::verifyImage() {
    type = XSF;
    if (readVolumeDescriptor())
        return true;

    type = GDFX;
    if (readVolumeDescriptor())
        return true;

    type = XGD3;
    if (readVolumeDescriptor())
        return true;

    return false;
}
