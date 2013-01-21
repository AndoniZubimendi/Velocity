#include "singleprogressdialog.h"
#include "ui_singleprogressdialog.h"

SingleProgressDialog::SingleProgressDialog(FileSystem system, void *device, Operation op, QString internalPath, QString externalPath, void *outEntry, QWidget *parent) :
    QDialog(parent), ui(new Ui::SingleProgressDialog), system(system), device(device), op(op), internalPath(internalPath), externalPath(externalPath), outEntry(outEntry)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);

    if (op == OpInject)
    {
        setWindowTitle("Injecting File");
        ui->lblIcon->setPixmap(QPixmap(":/Images/add.png"));
    }
    else if (op == OpReplace)
    {
        setWindowTitle("Replacing File");
        ui->lblIcon->setPixmap(QPixmap(":/Images/replace.png"));
    }
}

void SingleProgressDialog::startJob()
{
    try
    {
        switch (system)
        {
            case FileSystemSTFS:
            {
                StfsPackage *package = reinterpret_cast<StfsPackage*>(device);
                if (op == OpReplace)
                    package->ReplaceFile(externalPath, internalPath, UpdateProgress, this);
                else if (op == OpInject)
                {
                    FileEntry *entry = reinterpret_cast<FileEntry*>(outEntry);
                    *entry = package->InjectFile(externalPath, internalPath, UpdateProgress, this);
                }
                break;
            }
            case FileSystemSVOD:
            {
                if (op != OpReplace)
                    throw std::string("Invalid SVOD operation.\n");
                else
                {
                    SVOD *svod = reinterpret_cast<SVOD*>(device);
                    SvodIO io = svod->GetSvodIO(internalPath.toStdString());

                    io.OverwriteFile(externalPath.toStdString(), UpdateProgress, this);
                }
                break;
            }
        }
    }
    catch (string error)
    {
        QMessageBox::critical(this, "Error", "An error occured during the operation.\n\n" + QString::fromStdString(error));
        close();
    }
}

SingleProgressDialog::~SingleProgressDialog()
{
    delete ui;
}

void UpdateProgress(void *arg, DWORD cur, DWORD total)
{
    SingleProgressDialog *dialog = reinterpret_cast<SingleProgressDialog*>(arg);
    dialog->ui->progressBar->setMaximum(total);
    dialog->ui->progressBar->setValue(cur);

    if (cur == total)
        dialog->close();

    QApplication::processEvents();
}
