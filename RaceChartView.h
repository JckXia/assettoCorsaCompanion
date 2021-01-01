#pragma once
#ifndef RACE_CHART_VIEW
#include <QtCharts/QChartView>
#include "RaceCharts.h"

QT_CHARTS_USE_NAMESPACE

class RaceChartView : public QChartView
{
	Q_OBJECT
public:
	RaceChartView(QChart * chart, QWidget* parent = nullptr);
	void setRaceChart(RaceCharts* raceChart);
protected:
	virtual void mouseMoveEvent(QMouseEvent * event) override;
	
private:
	RaceCharts* m_chart;
};

#endif