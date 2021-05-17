#include "GroupByFolders.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QTextStream>
#include <cmath>
#include <iostream>
#include <iomanip>


qint64 getTotalSize(const QString& path) 
{
    qint64 totalSize = 0;
    QDir dir(path);
    for (const auto& it : dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type))
			if (it.isDir() && !it.isSymLink()) {
                 totalSize += getTotalSize(it.absoluteFilePath());
            } else totalSize += it.size();
    return totalSize;
}
qint64 getCurDirSize(const QString& path)
{
    qint64 totalSize = 0;
    QDir dir(path);
    for (const auto& it : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot , QDir::Name | QDir::Type))
        totalSize += it.size();
    return totalSize;
}

QMap<QString, double> GroupByFolders::getFoldersPercentOfTotal(qint64& totalSize, QMap<QString, qint64>& FoldersList) const
{
	QMap<QString, double> foldersListPercentage;
	for (auto it = FoldersList.begin(); it != FoldersList.end(); ++it) {
		auto percent = double(it.value() * 100) / totalSize;
		foldersListPercentage.insert(it.key(), percent);
	}
	return foldersListPercentage;
}
QMap<QString, qint64> GroupByFolders::getFoldersSizes(const QString& path) const 
{
    QFileInfo folder(path);
    // Создаем QMap содержащий полный путь папки и её размер
    QMap<QString, qint64> FoldersList;
    // Вычисляем размер текущей папки
    auto absoluteCurDirPath = folder.absoluteFilePath();
	FoldersList.insert(absoluteCurDirPath, getCurDirSize(absoluteCurDirPath));
    // Вычисляем размеры вложенных папок
    for (auto& x : QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type))
	{
		auto absolutePath = x.absoluteFilePath();
		FoldersList.insert(absolutePath, getTotalSize(absolutePath));
	}
    return FoldersList;
}


void GroupByFolders::explore(const QString& path)
{
    QFileInfo folder(path);
    if (!folder.exists() && !folder.isReadable()){
        qDebug() << "Error! Folder doesn't exist or it's symlink" << Qt::endl;
        return;
    }
    auto FoldersList = getFoldersSizes(path);
    auto totalSize = getTotalSize(path);
    auto FoldersPercentage = getFoldersPercentOfTotal(totalSize, FoldersList);
    QTextStream out(stdout);
    foreach (QString file, FoldersList.keys()) {
        qint64 value = FoldersList.value(file);
        foreach (QString file2, FoldersPercentage.keys()) {
            if (file == file2) {
                double percent = FoldersPercentage.value(file2);
                std::cout << std::left << std::setw(45) << file.toStdString() << std::setw(10)  << QString::number(value).toStdString()
                          << std::setw(10)<< "bytes"
                          << std::setw(6)<< QString::number(percent, 'f', 2).append(" %").toStdString()
                          << std::endl;
            }
        }
    }
}

