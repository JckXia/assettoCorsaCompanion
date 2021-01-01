#pragma once
#ifndef  RACE_CHART_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QScatterSeries>
#include <QMutex>
#include "RaceChartSubject.h"
QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE


class RaceChartSubject;

class RaceCharts : public QWidget
{
	Q_OBJECT
public:
	RaceCharts(const std::string& title, const std::string& yAxisTitle, qreal maxX, qreal maxY, QWidget* parent,unsigned short pid);
	void writeData(const QPointF& dataPoint);
	void setCursor(const QPointF& cursorPoint);
	void setCursorOnX(float xCoord);
	void attachRaceChartSubject(RaceChartSubject * rSubject);
	unsigned short getPid();
	~RaceCharts();
private:
	
	RaceChartSubject* m_subject;
	unsigned short m_pid;
	QChart* m_chart;
	QLineSeries* m_series;
	QScatterSeries* trace_points;
	const qreal incVal;
	qreal lastXCoord;
	QMutex m_lock;
	qreal maxXVal;
	QValueAxis* m_xAxis;
};

#endif // ! RACE_CHART_H