#ifndef ISOVIEWER_H
#define ISOVIEWER_H

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
#include "progressdialog.h"
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
#include "Iso/Iso.h"

// other
#include <stdio.h>

Q_DECLARE_METATYPE( IsoFileEntry* )

namespace Ui {
class IsoViewer;
}

class IsoViewer : public QDialog
{
    Q_OBJECT
    
public:
    explicit IsoViewer(QStatusBar *statusBar, Iso *iso, QWidget *parent = NULL);
    ~IsoViewer();
    
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
    Ui::IsoViewer *ui;
    void PopulateTreeWidget(const IsoFileListing *entry, QTreeWidgetItem *parent = NULL);
    void GetPackagePath(QTreeWidgetItem *item, QString *out, bool folderOnly = false);
    void SetIcon(const QString &name, QTreeWidgetItem *item);
    Iso *iso;

    IsoFileListing listing;
    QWidget *parent;
    QStatusBar *statusBar;
    QMenu *openInMenu;

    void showAllItems(QTreeWidgetItem *parent);
    void hideAllItems(QTreeWidgetItem *parent);

    void collapseAllChildren(QTreeWidgetItem *item);
};

#endif // IsoViewer_H
