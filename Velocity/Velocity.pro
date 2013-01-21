#-------------------------------------------------
#
# Project created by QtCreator 2012-08-14T18:07:11
#
#-------------------------------------------------

QT       += core gui network xml widgets

win32 {
    QT += phonon
}

TARGET = Velocity
TEMPLATE = app
VERSION = 0.0.1.1
DEFINES += VERSION=\\\"$$VERSION\\\"

win32 {
    RC_FILE = velocity.rc

    include(Stfs/Botan.pri)
    INCLUDEPATH += "C:/botan/include"
    LIBS += "C:/botan/libBotan.a"
}

mac {
    ICON = velocity.icns
    INCLUDEPATH += "/usr/local/include/botan-1.10"
    INCLUDEPATH += "/opt/local/include/botan-1.10"
    LIBS += "-lssl"
    LIBS += "-lcrypto"
    LIBS += "/opt/local/lib/libbotan-1.10.a"
}

unix:!mac {
    INCLUDEPATH += "/usr/local/include/botan-1.10"
    INCLUDEPATH += "/usr/include/botan-1.10"
    LIBS += "-lbotan-1.10"
}

UI_DIR = ../Velocity

SOURCES += main.cpp \
    mainwindow.cpp \
    packageviewer.cpp \
    profileeditor.cpp \
    about.cpp \
    FileIO.cpp \
    GPD/XDBF.cpp \
    GPD/GPDBase.cpp \
    GPD/GameGPD.cpp \
    GPD/AvatarAwardGPD.cpp \
    AvatarAsset/AvatarAsset.cpp \
    AvatarAsset/AssetHelpers.cpp \
    Stfs/StfsDefinitions.cpp \
    metadata.cpp \
    certificatedialog.cpp \
    qthelpers.cpp \
    licensingdatadialog.cpp \
    transferflagsdialog.cpp \
    xdbfdialog.cpp \
    strbdialog.cpp \
    imagedialog.cpp \
    Account/AccountHelpers.cpp \
    Account/Account.cpp \
    GPD/XDBFHelpers.cpp \
    GPD/DashboardGPD.cpp \
    Stfs/StfsPackage.cpp \
    renamedialog.cpp \
    creationwizard.cpp \
    achievementcreationwizard.cpp \
    propertiesdialog.cpp \
    addressconverterdialog.cpp \
    stfstoolsdialog.cpp \
    singleprogressdialog.cpp \
    profilecreatorwizard.cpp \
    themecreationwizard.cpp \
    gameadderdialog.cpp \
    avatarassetdownloader.cpp \
    gpddownloader.cpp \
    titleidfinder.cpp \
    titleidfinderdialog.cpp \
    gamerpicturepackdialog.cpp \
    preferencesdialog.cpp \
    json.cpp \
    githubcommitsdialog.cpp \
    gpduploader.cpp \
    fatxpathgendialog.cpp \
    MemoryStream.cpp \
    profilecleanerwizard.cpp \
    Stfs/XContentHeader.cpp \
    svoddialog.cpp \
    svodfileinfodialog.cpp \
    Disc/svod.cpp \
    Disc/gdfx.cpp \
    IO/BaseIO.cpp \
    IO/MultiFileIO.cpp \
    IO/SvodIO.cpp \
    stfsvolumedescriptordialog.cpp \
    svodtooldialog.cpp \
    svodvolumedescriptordialog.cpp \
    multiprogressdialog.cpp

HEADERS  += mainwindow.h \
    packageviewer.h \
    profileeditor.h \
    about.h \
    Stfs/StfsConstants.h \
    FileIO.h \
    FileIO.h \
    GPD/XDBFDefininitions.h \
    GPD/XDBF.h \
    GPD/GPDBase.h \
    GPD/GameGPD.h \
    GPD/AvatarAwardGPD.h \
    winnames.h \
    AvatarAsset/AvatarAssetDefinintions.h \
    AvatarAsset/AvatarAsset.h \
    AvatarAsset/AssetHelpers.h \
    Stfs/StfsDefinitions.h \
    metadata.h \
    certificatedialog.h \
    qthelpers.h \
    licensingdatadialog.h \
    transferflagsdialog.h \
    xdbfdialog.h \
    strbdialog.h \
    imagedialog.h \
    Account/AccountHelpers.h \
    Account/AccountDefinitions.h \
    Account/Account.h \
    GPD/XDBFHelpers.h \
    GPD/DashboardGPD.h \
    Stfs/StfsPackage.h \
    renamedialog.h \
    achievementcreationwizard.h \
    creationwizard.h \
    propertiesdialog.h \
    addressconverterdialog.h \
    stfstoolsdialog.h \
    singleprogressdialog.h \
    PluginInterfaces/igamemodder.h \
    profilecreatorwizard.h \
    themecreationwizard.h \
    gameadderdialog.h \
    avatarassetdownloader.h \
    gpddownloader.h \
    titleidfinder.h \
    titleidfinderdialog.h \
    gamerpicturepackdialog.h \
    PluginInterfaces/igamemodder.h \
    PluginInterfaces/igpdmodder.h \
    preferencesdialog.h \
    json.h \
    githubcommitsdialog.h \
    gpduploader.h \
    fatxpathgendialog.h \
    MemoryStream.h \
    profilecleanerwizard.h \
    Stfs/XContentHeader.h \
    svoddialog.h \
    svodfileinfodialog.h \
    Disc/svod.h \
    Disc/gdfx.h \
    IO/BaseIO.h \
    IO/MultiFileIO.h \
    IO/SvodIO.h \
    stfsvolumedescriptordialog.h \
    svodtooldialog.h \
    svodvolumedescriptordialog.h \
    multiprogressdialog.h

FORMS    += mainwindow.ui \
    packageviewer.ui \
    profileeditor.ui \
    about.ui \
    metadata.ui \
    certificatedialog.ui \
    licensingdatadialog.ui \
    transferflagsdialog.ui \
    xdbfdialog.ui \
    strbdialog.ui \
    imagedialog.ui \
    renamedialog.ui \
    creationwizard.ui \
    achievementcreationwizard.ui \
    propertiesdialog.ui \
    addressconverterdialog.ui \
    stfstoolsdialog.ui \
    singleprogressdialog.ui \
    profilecreatorwizard.ui \
    themecreationwizard.ui \
    gameadderdialog.ui \
    titleidfinderdialog.ui \
    gamerpicturepackdialog.ui \
    preferencesdialog.ui \
    githubcommitsdialog.ui \
    fatxpathgendialog.ui \
    profilecleanerwizard.ui \
    svoddialog.ui \
    svodfileinfodialog.ui \
    svodtooldialog.ui \
    svodvolumedescriptordialog.ui \
    stfsvolumedescriptordialog.ui \
    multiprogressdialog.ui

RESOURCES += \
    Resources.qrc
