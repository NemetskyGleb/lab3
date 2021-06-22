#ifndef BARCHARTADAPTER_H
#define BARCHARTADAPTER_H
#include "FileBrowserObserver.h"
#include <QChartView>
#include <QLayout>
#include "Charts.h"

using namespace QtCharts;

class BarChartAdapter : public FileBrowserObserver
{
public:
    BarChartAdapter(QLayout* l);
    void UpdateDisplay(const std::unique_ptr<QList<Data> > &data) const override;
    ~BarChartAdapter();
private:
    QChartView* chart_view;
    std::unique_ptr<Charts> chart;
};


#endif // BARCHARTADAPTER_H
