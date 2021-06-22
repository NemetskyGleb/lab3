#include "BarChartAdapter.h"
#include "Charts.h"


BarChartAdapter::BarChartAdapter(QLayout* l)
{
    chart = std::make_unique<BarChart>();
    chart_view = new QChartView(chart->createChart(std::make_unique<QList<Data>>()));
    chart_view->setRenderHint(QPainter::Antialiasing);
    l->addWidget(chart_view);
}

void BarChartAdapter::UpdateDisplay(const std::unique_ptr<QList<Data> > &data) const
{
    QChart* prev_chart = chart_view->chart();
    chart_view->setChart(chart->createChart(data));
    delete prev_chart;
}


BarChartAdapter::~BarChartAdapter()
{
    delete chart_view;
}
