#ifndef GROUPBYFOLDERS_H
#define GROUPBYFOLDERS_H
#include "Explorer.h"


class GroupByFolders final : public IExplore
{
public:
    explicit GroupByFolders() = default;
    virtual ~GroupByFolders() = default;
    void explore(const QString& path) override;
private:
    QMap<QString, qint64> getFoldersSizes(const QString& path) const;
    QMap<QString, double> getFoldersPercentOfTotal(qint64& totalSize, QMap<QString, qint64>& FoldersList) const;
};

#endif //GROUPBYFOLDERS_H
