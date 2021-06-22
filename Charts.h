#ifndef CHARTSWIDGET_H
#define CHARTSWIDGET_H
#include "Data.h"
#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <memory>

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

// базовый класс использующий паттерн шаблонный метод
class Charts
{
public:
    virtual ~Charts() {}

    QChart* createChart(const std::unique_ptr<QList<Data>>& data) const;

    // отрисовка диаграммы
    virtual void addDataToChart(QChart* c, const std::unique_ptr<QList<Data>>& data) const = 0;

};

// создание круговой диаграммы
class PieChart : public Charts
{
public:
    void addDataToChart(QChart *c, const std::unique_ptr<QList<Data> > &data) const override;
};

//создание вертикальной диаграммы
class BarChart : public Charts
{
public:
    void addDataToChart(QChart *c, const std::unique_ptr<QList<Data> > &data) const override;
};

#endif // CHARTSWIDGET_H
