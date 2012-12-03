#include "isoviewer.h"
#include "ui_isoviewer.h"

IsoViewer::IsoViewer(QStatusBar *statusBar, Iso *iso, QWidget *parent) :
    QDialog(parent),ui(new Ui::IsoViewer), iso(iso), parent (parent), statusBar(statusBar),  openInMenu(NULL)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    QtHelpers::GenAdjustWidgetAppearanceToOS(this);

    ui->treeWidget->header()->setDefaultSectionSize(75);
    ui->treeWidget->header()->resizeSection(0, 200);
    ui->treeWidget->header()->resizeSection(2, 100);


    listing = iso->getFileListing();
    PopulateTreeWidget(&listing);

    if (openInMenu != NULL && openInMenu->actions().size() > 0)
    {
        ui->btnOpenIn->setEnabled(true);
        ui->btnOpenIn->setMenu(openInMenu);
    }

    // setup the context menus
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRemoveContextMenu(QPoint)));

}

IsoViewer::~IsoViewer()
{
    delete ui;
}

void IsoViewer::PopulateTreeWidget(const IsoFileListing *entry, QTreeWidgetItem *parent)
{
    bool isRootEntry = entry->folder.name.toStdString() == "";

    for (int i = 0; i < entry->folderEntries.size(); i++)
    {
        QTreeWidgetItem *folder;
        if (!isRootEntry)
            folder = new QTreeWidgetItem(parent);
        else
            folder = new QTreeWidgetItem(ui->treeWidget);

        folder->setText(0, entry->folderEntries.at(i).folder.name);
        folder->setIcon(0, QIcon(":/Images/FolderFileIcon.png"));
        folder->setText(1, "Directory");
        folder->setText(2, "N/A");
        folder->setText(3, "N/A");

        PopulateTreeWidget(&entry->folderEntries.at(i), folder);
    }

    // add all files
    for (int i = 0; i < entry->fileEntries.size(); i++)
    {
        QTreeWidgetItem *fileEntry;
        if (!isRootEntry)
            fileEntry = new QTreeWidgetItem(parent);
        else
            fileEntry = new QTreeWidgetItem(ui->treeWidget);

        SetIcon(entry->fileEntries[i].name, fileEntry);

        QString name = entry->fileEntries.at(i).name;
        fileEntry->setText(0, name);
        fileEntry->setText(1, ByteSizeToString(entry->fileEntries.at(i).fileSize));

    }
}

void IsoViewer::GetPackagePath(QTreeWidgetItem *item, QString *out, bool folderOnly)
{
    bool hasParent = item->parent() != NULL;

    if (!hasParent && folderOnly)
        return;

    QString slash = "";
    if (hasParent)
        slash = "\\";

    out->push_front(slash + item->text(0));

    if (hasParent)
        GetPackagePath(item->parent(), out);
}

void IsoViewer::SetIcon(const QString &name, QTreeWidgetItem *item)
{
    int index = name.lastIndexOf(".");
    QString extension = "";
    if (index != -1)
        extension = name.mid(index);

    if (extension == ".gpd" || extension == ".fit")
        item->setIcon(0, QIcon(":/Images/GpdFileIcon.png"));
    else if (name == "Account")
        item->setIcon(0, QIcon(":/Images/AccountFileIcon.png"));
    else if (name == "PEC")
        item->setIcon(0, QIcon(":/Images/PecFileIcon.png"));
    else if (name == "Account")
        item->setIcon(0, QIcon(":/Images/AccountFileIcon.png"));
    else if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
        item->setIcon(0, QIcon(":/Images/ImageFileIcon.png"));
    else
        item->setIcon(0, QIcon(":/Images/DefaultFileIcon.png"));
}

void IsoViewer::on_btnFix_clicked()
{
    bool success = true, resigned = false;


\
    if (success)
    {
        QString resignedStr = (resigned ? " and resigned" : "");
        statusBar->showMessage("Rehashed" + resignedStr + " successfully", 3000);
        QMessageBox::information(this, "Success", "The package has successfully been rehashed" + resignedStr + ".");
    }
}

void IsoViewer::on_btnViewAll_clicked()
{
}

void IsoViewer::showSaveImageContextMenu(QPoint point)
{
}

void IsoViewer::on_txtSearch_textChanged(const QString &arg1)
{
    QList<QTreeWidgetItem*> itemsMatched = ui->treeWidget->findItems(ui->txtSearch->text(), Qt::MatchContains | Qt::MatchRecursive);

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
        hideAllItems(ui->treeWidget->topLevelItem(i));

    if (itemsMatched.count() == 0 || arg1 == "")
    {
        ui->txtSearch->setStyleSheet("color: rgb(255, 1, 1);");
        for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
        {
            showAllItems(ui->treeWidget->topLevelItem(i));
            collapseAllChildren(ui->treeWidget->topLevelItem(i));
        }
        return;
    }

    ui->txtSearch->setStyleSheet("");
    // add all the matched ones to the list
    for (int i = 0; i < itemsMatched.count(); i++)
    {
        // show all the item's parents
        QTreeWidgetItem *parent = itemsMatched.at(i)->parent();
        while (parent != NULL)
        {
            ui->treeWidget->setItemHidden(parent, false);
            parent->setExpanded(true);
            parent = parent->parent();
        }

        // show the item itself
        ui->treeWidget->setItemHidden(itemsMatched.at(i), false);
    }
}

void IsoViewer::hideAllItems(QTreeWidgetItem *parent)
{
    for (int i = 0; i < parent->childCount(); i++)
    {
        if (parent->child(i)->childCount() != 0)
            hideAllItems(parent->child(i));
        parent->child(i)->setHidden(true);
    }
    parent->setHidden(true);
}

void IsoViewer::onOpenInSelected(QAction *action)
{
}

void IsoViewer::aboutToShow()
{
}

void IsoViewer::showRemoveContextMenu(QPoint point)
{
    int amount = ui->treeWidget->selectedItems().length();

    QPoint globalPos = ui->treeWidget->mapToGlobal(point);
    QMenu contextMenu;

    bool isFolder = false;
    if (amount == 0)
    {
        contextMenu.addAction(QPixmap(":/Images/add.png"), "Inject Here");
    }
    else
    {
        isFolder = ui->treeWidget->selectedItems()[0]->text(3) == "N/A";

        if (!isFolder)
        {
            contextMenu.addAction(QPixmap(":/Images/extract.png"), "Extract Selected");
        }

        contextMenu.addSeparator();
        contextMenu.addAction(QPixmap(":/Images/properties.png"), "View Properties");
    }

    QAction *selectedItem = contextMenu.exec(globalPos);
    if(selectedItem == NULL)
        return;

    QList <QTreeWidgetItem*> items = ui->treeWidget->selectedItems();
    int totalCount = items.count(), successCount = 0;

    if (selectedItem->text() == "Extract Selected")
    {
        bool multiple = totalCount > 1;

        QString path;
        if (multiple)
            path = QFileDialog::getExistingDirectory(this, "Save Location", QtHelpers::DesktopLocation());
        else
            path = QFileDialog::getSaveFileName(this, "Save Location", QtHelpers::DesktopLocation() + "/" + ui->treeWidget->selectedItems()[0]->text(0));

        if (path.isEmpty())
            return;


        QList<QString> packagePaths;
        QList<QString> outPaths;
        for (int i = 0; i < totalCount; i++)
        {
            QString packagePath;
            GetPackagePath(items.at(i), &packagePath);
            packagePaths.append(packagePath);

            QString final = path;
            if (multiple)
                final += "\\" + items.at(i)->text(0);
            outPaths.append(final);
        }

        statusBar->showMessage("Selected files extracted successfully", 3000);

    }

}

void IsoViewer::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int /*column*/)
{
    // make sure that the item clicked isn't a folder
    if (item->text(2) == "N/A")
        return;

    // make sure the file double clicked on is a gpd
    int index = item->text(0).lastIndexOf(".");
    QString extension;
    if (index != -1)
        extension = item->text(0).mid(index).toLower();


}

void IsoViewer::on_btnStfsTools_clicked()
{
}

void IsoViewer::on_btnShowAll_clicked()
{
    ui->txtSearch->setText("");
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
        showAllItems(ui->treeWidget->topLevelItem(i));
}

void IsoViewer::showAllItems(QTreeWidgetItem *parent)
{
    for (int i = 0; i < parent->childCount(); i++)
    {
        if (parent->child(i)->childCount() != 0)
            hideAllItems(parent->child(i));
        parent->child(i)->setHidden(false);
    }
    parent->setHidden(false);
}

void IsoViewer::collapseAllChildren(QTreeWidgetItem *item)
{
    item->setExpanded(false);

    // collapse all children
    for (int i = 0; i < item->childCount(); i++)
        collapseAllChildren(item->child(i));
}
