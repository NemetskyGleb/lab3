#include "GroupByTypes.h"
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

void GroupByTypes::getFileTypesAndSizes(const QString& path, QMap<QString, qint64>& FileTypesList)
{
    QDir dir(path);
    for (const auto& it : dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type | QDir::Size)) {
            if (it.isDir() && !it.isSymLink()) {
                getFileTypesAndSizes(it.absoluteFilePath(), FileTypesList);
            } else  {
                if (FileTypesList.keys().contains(it.suffix().toLower())) {
                    FileTypesList[it.suffix()] += it.size();
                }
                else {
                    FileTypesList.insert(it.suffix().toLower(), it.size());
                }
            }
    }
}

QMap<double, QString> GroupByTypes::getFileTypesPercentOfTotal(qint64& totalSize, QMap<QString, qint64>& FileTypesList) const
{
    QMap<double, QString> FileTypesListPercentage;
    for (auto it = FileTypesList.begin(); it != FileTypesList.end(); ++it) {
        auto percent = double(it.value() * 100) / totalSize;
        FileTypesListPercentage.insert(percent, it.key());
    }
    return FileTypesListPercentage;
}

void GroupByTypes::PrintFileTypesListAndPercents(const QMap<QString, qint64>& FileTypesList, const QMap<double, QString>& FileTypesPercantage) const
{
    QTextStream out(stdout);
    // Обратная итерация, потому что в QMap с процентами, ключи сортируются по возрастанию
    if (FileTypesPercantage.isEmpty()) {
        return;
    }
    for (auto it = FileTypesPercantage.end() - 1; it != FileTypesPercantage.begin() - 1; it--) {
        out  << Qt::left << qSetFieldWidth(15) <<   "*." + it.value() <<
                    qSetFieldWidth(10) << FileTypesList.value(it.value()) / 1024 <<
                    qSetFieldWidth(3) << "KB" <<
                    qSetFieldWidth(7) << QString::number(it.key(), 'f', 2) + "%" << Qt::endl;
    }
    out.reset();
}


void GroupByTypes::explore(const QString& path)
{
    QDir folder(path);
    if (!folder.exists() && !folder.isReadable()) {
        qDebug() << "Error! Folder doesn't exist or it's symlink" << Qt::endl;
        return;
    }
    if (folder.isEmpty()) {
        qDebug() << "Folder is empty!" << Qt::endl;
        return;
    }
    QMap<QString, qint64> fileTypesList;
    getFileTypesAndSizes(path, fileTypesList);
    auto totalSize = Common::getTotalSize(path);
    auto fileTypesPercantage = getFileTypesPercentOfTotal(totalSize, fileTypesList);
    PrintFileTypesListAndPercents(fileTypesList, fileTypesPercantage);
}

