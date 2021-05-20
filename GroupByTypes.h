#ifndef GROUPBYTYPES_H
#define GROUPBYTYPES_H
#include "Explorer.h"

class GroupByTypes : public IExplore {
public:
    explicit GroupByTypes() = default;
    virtual ~GroupByTypes() = default;
    void explore(const QString& path) override;
private:
    void getFileTypesAndSizes(const QString& path, QMap<QString, qint64>& FileTypesList);
    QMap<double, QString> getFileTypesPercentOfTotal(qint64& totalSize, QMap<QString, qint64>& FileTypesList) const;
    void PrintFileTypesListAndPercents(const QMap<QString, qint64>& FileTypesList, const QMap<double, QString>& FileTypesPercantage) const;
};


#endif // GROUPBYTYPES_H
