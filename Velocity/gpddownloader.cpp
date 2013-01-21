#include "gpddownloader.h"

#include <QNetworkRequest>
#include <QNetworkReply>


GPDDownloader::GPDDownloader(TitleEntry entry, int index, bool hasAwards, QObject * /* parent */ ) : entry(entry), hasAwards(hasAwards), indexIn(index)
{
    gpdDirectory = "/gameadder/";
    gpdWritten = false;

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(done(bool)), this, SLOT(onDone(bool)));
    connect(manager, SIGNAL(requestFinished(QNetworkReply *)), this, SLOT(onRequestFinished(int, bool)));
}

void GPDDownloader::BeginDownload()
{
    QString url = gpdDirectory + "game/" + QString::number(entry.titleID, 16).toUpper() + ".gpd";
    manager->get(QNetworkRequest(QUrl(url)));
}

int GPDDownloader::index()
{
    return indexIn;
}

void GPDDownloader::onRequestFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
        qDebug() << reply->errorString();
    else if (reply->bytesAvailable() < 1)
        return;

    QString tempPath = QDir::tempPath() + "/" + QUuid::createUuid().toString().replace("{", "").replace("}", "").replace("-", "");

    if (!gpdWritten)
    {
        gameGPD = tempPath;

        // create a new temporary file
        QFile v1File(tempPath);
        v1File.open(QFile::Truncate | QFile::WriteOnly);

        // write the gpd to disk
        v1File.write(reply->readAll());

        // clean up
        v1File.flush();
        v1File.close();

        gpdWritten = true;
    }
    else
    {
        awardGPD = tempPath;

        // create a new temporary file
        QFile v1File(tempPath);
        v1File.open(QFile::Truncate | QFile::WriteOnly);

        // write the gpd to disk
        v1File.write(reply->readAll());

        // clean up
        v1File.flush();
        v1File.close();
    }

    if (hasAwards)
    {
        hasAwards = false;
        manager->get(QNetworkRequest(QUrl(gpdDirectory + "award/" + QString::number(entry.titleID, 16).toUpper() + ".gpd")));
    }
}

void GPDDownloader::onDone(bool error)
{
    emit FinishedDownloading(gameGPD, awardGPD, entry, error);
}
