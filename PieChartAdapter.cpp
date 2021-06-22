#include "PieChartAdapter.h"
#include <QLayout>

PieChartAdapter::PieChartAdapter(QLayout* l)
{
    chart = std::make_unique<PieChart>();
    chart_view = new QChartView(chart->createChart(std::make_unique<QList<Data>>()));
    chart_view->setRenderHint(QPainter::Antialiasing);
    l->addWidget(chart_view);
}

void PieChartAdapter::UpdateDisplay(const std::unique_ptr<QList<Data> > &data) const
{
    QChart* prev_chart = chart_view->chart();
    chart_view->setChart(chart->createChart(data));
    delete prev_chart; // очищаем память из под предыдущего графика

}


PieChartAdapter::~PieChartAdapter()
{
    delete chart_view;
}
