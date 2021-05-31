#ifndef GROUPBYFOLDERS_H
#define GROUPBYFOLDERS_H
#include "Explorer.h"


class GroupByFolders final : public IExplore
{
public:
    explicit GroupByFolders() = default;
    virtual ~GroupByFolders() = default;
    QList<Data> explore(const QString& path) override;
private:
    QMap<QString, qint64> getFoldersSizes(const QString& path) const;
    QMap<QString, double> getFoldersPercentOfTotal(qint64& totalSize, QMap<QString, qint64>& FoldersList) const;
    void PrintFoldersSizesAndPercentage(const QMap<QString, qint64>& FoldersAndTypes, const QList<QPair<double, QString> >& FoldersAndPercentage) const;
    QList<Data> CombineData(const QMap<QString, qint64>& FoldersAndTypes, const QList<QPair<double, QString>>& FoldersAndPercentage) const;
};

#endif //GROUPBYFOLDERS_H
