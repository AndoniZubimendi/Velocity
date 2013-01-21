#ifndef STFSDEFINITIONS_H
#define STFSDEFINITIONS_H

#include "winnames.h"
#include "StfsConstants.h"
#include <time.h>

#include <QString>

class FileIO;

enum LicenseType
{
    Unused = 0x0000,
    Unrestricted = 0xFFFF,
    ConsoleProfileLicense = 0x0009,
    WindowsProfileLicense = 0x0003,
    ConsoleLicense = 0xF000,
    MediaFlags = 0xE000,
    KeyVaultPrivileges = 0xD000,
    HyperVisorFlags = 0xC000,
    UserPrivileges = 0xB000
};

struct LicenseEntry
{
    LicenseType type;
    UINT64 data;
    DWORD bits;
    DWORD flags;
};

struct StfsVolumeDescriptor
{
    BYTE size;
    BYTE reserved;
    BYTE blockSeperation;
    WORD fileTableBlockCount;
    INT24 fileTableBlockNum;
    BYTE topHashTableHash[0x14];
    DWORD allocatedBlockCount;
    DWORD unallocatedBlockCount;
};

struct SvodVolumeDescriptor
{
    BYTE size;
    BYTE blockCacheElementCount;
    BYTE workerThreadProcessor;
    BYTE workerThreadPriority;
    BYTE rootHash[0x14];
    BYTE flags;
    INT24 dataBlockCount;
    INT24 dataBlockOffset;
    BYTE reserved[5];
};

struct Certificate
{
    WORD publicKeyCertificateSize;
    BYTE ownerConsoleID[5];
    QString ownerConsolePartNumber;
    ConsoleType ownerConsoleType;
    ConsoleTypeFlags consoleTypeFlags;
    QString dateGeneration;
    DWORD publicExponent;
    BYTE publicModulus[0x80];
    BYTE certificateSignature[0x100];
    BYTE signature[0x80];
};

struct MSTime
{
    WORD year;
    BYTE month;
    BYTE monthDay;

    BYTE hours;
    BYTE minutes;
    BYTE seconds;
};

void ReadStfsVolumeDescriptorEx(StfsVolumeDescriptor *descriptor, FileIO *io, DWORD address);

void ReadSvodVolumeDescriptorEx(SvodVolumeDescriptor *descriptor, FileIO *io);

void WriteStfsVolumeDescriptorEx(StfsVolumeDescriptor *descriptor, FileIO *io, DWORD address);

void WriteSvodVolumeDescriptorEx(SvodVolumeDescriptor *descriptor, FileIO *io);

void ReadCertificateEx(Certificate *cert, FileIO *io, DWORD address);

void WriteCertificateEx(Certificate *cert, FileIO *io, DWORD address);

QString MagicToString(Magic magic);

QString ContentTypeToString(ContentType type);

QString ConsoleTypeToString(ConsoleType type);

QString ByteSizeToString(DWORD bytes);

QString LicenseTypeToString(LicenseType type);

MSTime DWORDToMSTime(DWORD winTime);

DWORD MSTimeToDWORD(MSTime time);

MSTime TimetToMSTime(time_t time);

#endif // STFSDEFINITIONS_H
