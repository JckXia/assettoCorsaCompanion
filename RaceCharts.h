#pragma once
#ifndef  RACE_CHART_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE




class RaceCharts : public QWidget
{
	Q_OBJECT
public:
	explicit RaceCharts(qreal maxX, qreal maxY, QWidget* parent);
	void writeData(const QPointF& dataPoint);
	~RaceCharts();
private:
	QChart* m_chart;
	QLineSeries* m_series;
};

#endif // ! RACE_CHART_H