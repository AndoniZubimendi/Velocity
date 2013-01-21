#ifndef PACKAGEVIEWER_H
#define PACKAGEVIEWER_H

// forms
#include "mainwindow.h"
#include "metadata.h"
#include "xdbfdialog.h"
#include "strbdialog.h"
#include "profileeditor.h"
#include "renamedialog.h"
#include "certificatedialog.h"
#include "imagedialog.h"
#include "propertiesdialog.h"
#include "stfstoolsdialog.h"
#include "singleprogressdialog.h"

// qt
#include <QDialog>
#include <QTreeWidgetItem>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QUuid>
#include <QWidgetAction>
#include <QDebug>

// xbox libs
#include "Stfs/StfsPackage.h"
#include "GPD/GPDBase.h"
#include "AvatarAsset/AvatarAsset.h"

// other
#include <stdio.h>
#include "FileIO.h"

Q_DECLARE_METATYPE( FileEntry* )

namespace Ui {
class PackageViewer;
}

class PackageViewer : public QDialog
{
    Q_OBJECT
    
public:
    explicit PackageViewer(QStatusBar *statusBar, StfsPackage *package, QList<QAction*> gpdActions, QList<QAction*> gameActions, QWidget *parent = NULL, bool disposePackage = true);
    ~PackageViewer();
    
private slots:
    void on_btnFix_clicked();

    void on_btnViewAll_clicked();

    void showRemoveContextMenu(QPoint point);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_btnStfsTools_clicked();

    void on_btnShowAll_clicked();

    void showSaveImageContextMenu(QPoint point);

    void on_txtSearch_textChanged(const QString &);

    void onOpenInSelected(QAction *action);

    void aboutToShow();

private:
    Ui::PackageViewer *ui;
    void PopulateTreeWidget(const FileListing *entry, QTreeWidgetItem *parent = NULL);
    void GetPackagePath(QTreeWidgetItem *item, QString *out, bool folderOnly = false);
    void SetIcon(const QString &name, const FileEntry *entry, QTreeWidgetItem *item);

    StfsPackage *package;
    bool disposePackage;
    FileListing listing;
    QWidget *parent;
    QStatusBar *statusBar;
    QMenu *openInMenu;
    QList <QAction*> gpdActions, gameActions;
    QAction *profileEditor, *gameAdder;
};

#endif // PACKAGEVIEWER_H
