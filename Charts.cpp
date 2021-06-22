#include "Charts.h"
#include <QBarSeries>
#include <QPieSeries>
#include <QBarSet>
#include <QGraphicsLayout>

/**
 * @brief шаблонный метод создающий диаграмму
 * @param data
 */
QChart* Charts::createChart(const std::unique_ptr<QList<Data> > &data) const
{
    QChart* chart = new QChart();
    // отображаем легенду справа
    chart->legend()->setAlignment(Qt::AlignRight);

    // подсчитываем общий размер папки
    qint64 total_size = 0;
    for (auto& x : *data) {
        total_size += x._size.toLongLong();
    }
    // в случае когда папка пуста выводим надпись
    if (total_size == 0 || data->isEmpty()) {
        chart->setTitle("Folder is empty");
        return chart;
    }
    // элементы идущие после 6 относим к маленьким
    // подсчитываем их общий размер и размещаем их в категорию others
    if (data->size() > 6) {
        qint64 others_size = 0;
        auto it = data->begin() + 5;
        while (it != data->end()) {
            others_size += it->_size.toLongLong();
            it = data->erase(it);
        }

        double percent = double(others_size * 100) / total_size;
        data->push_back(Data("Others", QString::number(others_size), QString::number(percent, 'f', 2).append(" %"), (qreal)others_size / total_size));
    }
    // набор данных устанавливаются в диаграмму
    addDataToChart(chart, data);

    return chart;
}

/**
 * @brief Заполнение вертикальной диаграммы данными
 * @param c - сама диграмма
 * @param data - данные для заполнения
 */

void BarChart::addDataToChart(QChart *c, const std::unique_ptr<QList<Data> > &data) const
{
    QBarSeries* series = new QBarSeries();
//    series->setBarWidth(1); // 100% масштаб диаграммы

    for (auto& item : *data) {
        QBarSet* set = new QBarSet(item._name + " (" + item._percent.toHtmlEscaped() + ")");
        set->append(item._ratio);
        series->append(set);
    }
    c->addSeries(series);
}



/**
 * @brief Заполнение круговой диаграммы данными
 * @param c - сама диграмма
 * @param data - данные для заполнения
 */

void PieChart::addDataToChart(QChart *c, const std::unique_ptr<QList<Data> > &data) const
{
    QPieSeries* series = new QPieSeries();
    series->setPieSize(1); // 100% масштаб диаграммы

    for (auto& item : *data) {
        series->append(item._name + " (" + item._percent.toHtmlEscaped() + ")", item._ratio);
    }
    c->addSeries(series);

}


