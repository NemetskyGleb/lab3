#ifndef PIECHARTADAPTER_H
#define PIECHARTADAPTER_H

#include "FileBrowserObserver.h"
#include <QChartView>
#include "Charts.h"

using namespace QtCharts;

class PieChartAdapter : public FileBrowserObserver
{
public:
    explicit PieChartAdapter(QLayout* l);
    void UpdateDisplay(const std::unique_ptr<QList<Data> > &data) const override;
    ~PieChartAdapter();
private:
    QChartView* chart_view;
    std::unique_ptr<Charts> chart;
};



#endif // PIECHARTADAPTER_H
