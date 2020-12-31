#pragma once
#ifndef  RACE_CHART_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QMutex>
QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE




class RaceCharts : public QWidget
{
	Q_OBJECT
public:
	RaceCharts(const std::string& title, const std::string& yAxisTitle, qreal maxX, qreal maxY, QWidget* parent);
	void writeData(const QPointF& dataPoint);
	void setCursor(const QPointF& cursorPoint);
	~RaceCharts();
private:
	QChart* m_chart;
	QLineSeries* m_series;
	QLineSeries* trace_points;
	const qreal incVal;
	qreal lastXCoord;
	QMutex m_lock;
	qreal maxXVal;
	QValueAxis* m_xAxis;
};

#endif // ! RACE_CHART_H