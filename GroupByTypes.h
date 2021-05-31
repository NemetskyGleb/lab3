#ifndef GROUPBYTYPES_H
#define GROUPBYTYPES_H
#include "Explorer.h"

class GroupByTypes : public IExplore {
public:
    explicit GroupByTypes() = default;
    virtual ~GroupByTypes() = default;
    QList<Data> explore(const QString& path) override;
private:
    void getFileTypesAndSizes(const QString& path, QMap<QString, qint64>& FileTypesList);
    QMap<QString, double> getFileTypesPercentOfTotal(qint64& totalSize, QMap<QString, qint64>& FileTypesList) const;
    void PrintFileTypesListAndPercents(const QMap<QString, qint64>& FileTypesList, const QList<QPair<double, QString>> FileTypesPercantage) const;
    QList<QPair<double, QString>> sortByPercent(const QMap<QString, double>& FileTypesPercantage);
    QList<Data> CombineData(const QMap<QString, qint64>& FileTypesList, const QList<QPair<double, QString>>& FileTypesPercantage);
};


#endif // GROUPBYTYPES_H
